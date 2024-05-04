#include "cache.h"

// Cache constructor implementation
Cache::Cache() {
      for (int i = 0; i < HASH_SIZE; ++i) {
            hashTable[i] = nullptr;
      }
      head = nullptr;
      size = 0;
}

// Cache destructor implementation
Cache::~Cache() {
      for (int i = 0; i < HASH_SIZE; ++i) {
            Node* current = hashTable[i];
            while (current != nullptr) {
                  Node* next = current->next;
                  delete current;
                  current = next;
            }
      }
}

void Cache::add(std::string key, int value) {
      int index = hashFunction(key);
      Node* current = hashTable[index];
      Node* previous = nullptr;

      while (current != nullptr && current->key != key) {
            previous = current;
            current = current->next;
      }

      if (current != nullptr) {
            if (current->type == "int") {
                  *static_cast<int*>(current->value) = value;
            } else {
                  delete static_cast<double*>(current->value);
                  current->value = new int(value);
                  current->type = "int";
            }
            addHead(current, previous, index);
      } else {
            Node* newNode = new Node(key, value);
            newNode->next = hashTable[index];
            hashTable[index] = newNode;
            addHead(newNode, nullptr, index);
            ++size;

            if (size > CACHE_SIZE) {
                  removeTail();
            }
      }
}

void Cache::add(std::string key, double value) {
      int index = hashFunction(key);
      Node* current = hashTable[index];
      Node* previous = nullptr;

      while (current != nullptr && current->key != key) {
            previous = current;
            current = current->next;
      }

      if (current != nullptr) {
            if (current->type == "double") {
                  *static_cast<double*>(current->value) = value;
            } else {
                  delete static_cast<int*>(current->value);
                  current->value = new double(value);
                  current->type = "double";
            }
            addHead(current, previous, index);
      } else {
            Node* newNode = new Node(key, value);
            newNode->next = hashTable[index];
            hashTable[index] = newNode;
            addHead(newNode, nullptr, index);
            ++size;

            if (size > CACHE_SIZE) {
                  removeTail();
            }
      }
}

bool Cache::get(std::string key, int& value) {
      int index = hashFunction(key);
      Node* current = hashTable[index];
      Node* previous = nullptr;

      while (current != nullptr) {
            if (current->key == key && current->type == "int") {
                  value = *static_cast<int*>(current->value);
                  addHead(current, previous, index);
                  return true;
            }
            previous = current;
            current = current->next;
      }
      return false;
}

bool Cache::get(std::string key, double& value) {
      int index = hashFunction(key);
      Node* current = hashTable[index];
      Node* previous = nullptr;

      while (current != nullptr) {
            if (current->key == key && current->type == "double") {
                  value = *static_cast<double*>(current->value);
                  addHead(current, previous, index);
                  return true;
            }
            previous = current;
            current = current->next;
      }
      return false;
}

void Cache::addHead(Node* node, Node* prev, int index) {
      if (prev != nullptr) {
            prev->next = node->next;
      } else {
            hashTable[index] = node->next;
      }
      node->next = head;
      head = node;
}

void Cache::removeTail() {
      if (head == nullptr) {
            return;
      }
      Node* current = head;
      Node* previous = nullptr;

      while (current->next != nullptr) {
            previous = current;
            current = current->next;
      }

      if (previous != nullptr) {
            previous->next = nullptr;
      } else {
            head = nullptr;
      }

      int index = hashFunction(current->key);
      Node* htCurrent = hashTable[index];
      Node* htPrevious = nullptr;
      while (htCurrent != nullptr && htCurrent != current) {
            htPrevious = htCurrent;
            htCurrent = htCurrent->next;
      }
      if (htPrevious != nullptr) {
            htPrevious->next = current->next;
      } else {
            hashTable[index] = current->next;
      }
      delete current;
      --size;
}

int Cache::hashFunction(const std::string& key) {
      int sum = 0;
      for (int i = 0; i <key.length(); i++){
            sum += key[i];
      }
      return sum % HASH_SIZE;
}

std::string Cache::toString() {
      std::ostringstream oss;
      Node* current = head;
      int taskNumber = 0;
      while (current != nullptr) {
            oss << "[TASK #" << taskNumber++ << "]\n";
            oss << current->key << " = ";
            if (current->type == "int") {
                  oss << *static_cast<int*>(current->value);
            } else if (current->type == "double") {
                  oss << std::scientific << *static_cast<double*>(current->value);
            }
            oss << "\n\n[CACHE]\n";
            Node* temp = head;
            while (temp != nullptr) {
                  oss << "[" << temp->key << ": ";
                  if (temp-> type == "int") {
                  oss << *static_cast<int*>(temp->value);
                  } else if (temp->type == "double") {
                  oss << std::scientific << *static_cast<double*>(temp->value);
                  }
                  oss << "]";
                  temp = temp->next;
                  if (temp != nullptr) {
                  oss << " -> ";
                  }
            }
            oss << "\n\n";
            current = current->next;
      }
      return oss.str();
}
