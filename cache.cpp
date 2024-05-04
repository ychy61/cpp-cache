#include "cache.h"

Cache::Cache() : head(nullptr), size(0) {}

Cache::~Cache() {
      Node* current = head;
      //노드들을 순차적으로 제거
      while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
      }
}

void Cache::add(std::string key, int value) {
      Node* current = head;
      Node* previous = nullptr;

      //캐시에 추가하려는 키 값이 이미 있는지 확인
      while (current != nullptr && current->key != key) {
            previous = current;
            current = current->next;
      }

      //같은 키를 가진 노드가 있으면,
      if (current != nullptr) {
            //기존 노드의 value가 void* 타입이므로 이를 int*로 캐스팅
            delete static_cast<int*>(current->value);
            //int인 value를 값을 new를 통해 동적으로 할당하여 void*에 저장할 수 있도록 함
            current->value = new int(value);
            //노드를 리스트의 앞쪽으로 이동
            addHead(current, previous);
      } else { //같은 키를 가진 노드가 없다면,
            //새로운 노드를 캐시에 추가한다.
            Node* newNode = new Node(key, value);
            newNode->next = head;
            head = newNode;
            ++size;

            // 현재 캐시의 사이즈가 캐시의 전체 사이보다 커지면
            if (size > CACHE_SIZE) {
                  //tail 노드를 삭제한다.
                  removeTail();
            }
      }
}

void Cache::add(std::string key, double value) {
      Node* current = head;
      Node* previous = nullptr;

      //캐시에 추가하려는 키 값이 이미 있는지 확인
      while (current != nullptr && current->key != key) {
            previous = current;
            current = current->next;
      }

      //같은 키를 가진 노드가 있으면,
      if (current != nullptr) {
            //노드를 리스트의 앞쪽으로 이동시킴
            delete static_cast<double*>(current->value);
            current->value = new double(value);
            addHead(current, previous);
      }  else {
            //같은 키를 가진 노드가 없다면,
            //새로운 노드를 캐시에 추가한다.
            Node* newNode = new Node(key, value);
            newNode->next = head;
            head = newNode;
            ++size;

            // 현재 캐시의 사이즈가 캐시의 전체 사이보다 커지면
            if (size > CACHE_SIZE) {
                  //tail 노드를 삭제한다.
                  removeTail();
            }
      }
}


bool Cache::get(std::string key, int& value) {
      Node* current = head;
      Node* previous = nullptr;

      while (current != nullptr && current->key != key) {
            previous = current;
            current = current->next;
      }

      // 캐시에 없으면
      if (current == nullptr) {
            return false;
      } else {
            // 캐시에 있으면
            // int*로 캐스팅하여 값을 얻음
            value = *static_cast<int*>(current->value);
            addHead(current, previous);
            return true;
      }
}


// double 타입의 값을 캐시에서 가져옴
bool Cache::get(std::string key, double& value) {
      Node* current = head;
      Node* previous = nullptr;

      while (current != nullptr && current->key != key) {
            previous = current;
            current = current->next;
      }

      // 캐시에 없으면
      if (current == nullptr) {
            return false;
      } else {
            // 캐시에 있으면
            // int*로 캐스팅하여 값을 얻음
            value = *static_cast<double*>(current->value);
            addHead(current, previous);

            return true;
      }
}

// 노드를 리스트의 앞쪽으로 이동
void Cache::addHead(Node* node, Node* prev) {
      if (prev == nullptr) {
            // 노드가 이미 리스트의 앞쪽에 있음
            return;
      }

      // 노드를 리스트의 앞쪽으로 이동
      prev->next = node->next;
      node->next = head;
      head = node;
}

// 리스트의 마지막 노드를 제거
void Cache::removeTail() {
      //캐시가 비어있을때,
      if (head == nullptr) {
            return;
      }

      //캐시에 노드가 1개일때,
      if (head->next == nullptr) {
            delete head;
            head = nullptr;
      } else {
            Node* current = head;
            Node* previous = nullptr;

            //마지막 노드를 찾고
            while (current->next != nullptr) {
                  previous = current;
                  current = current->next;
            }

            // 마지막 노드 삭제
            delete current;
            previous->next = nullptr;
            --size;
      }
}

// 캐시 내용을 문자열로 반환
std::string Cache::toString() {
      std::ostringstream oss;
      Node* current = head;
      while (current != nullptr) {
            oss << "[" << current->key << ": ";

            Node* temp = current;
            while (temp != nullptr) {
                  if (temp->type == "int") {
                        oss << *static_cast<int*>(temp->value);
                  } else if (temp->type == "double") {
                        oss << *static_cast<double*>(temp->value);
                  }

                  temp = temp->nextValue;
            }
            oss << "]";
            current = current->next;
            // 다음 노드가 있으면,
            if (current != nullptr) {
                  oss << " -> ";
            }
      }
      oss << "\n";
      return oss.str();
}
