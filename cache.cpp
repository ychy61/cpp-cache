#include "cache.h"
#include <sstream>

// int 타입의 Node 생성자
Cache::Node::Node(std::string k, int v) : key(k), type("int"), prev(nullptr), next(nullptr), nextValue(nullptr)
{
      value = new int(v);
}

// double 타입의 Node 생성자
Cache::Node::Node(std::string k, double v) : key(k), type("double"), prev(nullptr), next(nullptr), nextValue(nullptr)
{
      value = new double(v);
}

// Cache 생성자
Cache::Cache() : head(nullptr), tail(nullptr), size(0)
{
      // hashTable을 초기화
      for (int i = 0; i < HASH_SIZE; ++i)
      {
            hashTable[i] = nullptr;
      }
}

// Cache 소멸자
Cache::~Cache()
{
      // 모든 Node를 순차적으로 해제
      Node *current = head;
      while (current != nullptr)
      {
            Node *next = current->next;
            delete current;
            current = next;
      }
}

// 문자열 키를 이용해 hash value를 계산
int Cache::hashFunction(const std::string &key)
{
      int sum = 0;
      for (int i = 0; i < key.length(); i++)
      {
            sum += key[i];
      }
      return sum % HASH_SIZE;
}

// Node를 캐시의 가장 앞에 추가
void Cache::addHead(Node *node)
{
      node->next = head;
      node->prev = nullptr;
      if (head != nullptr)
      {
            head->prev = node;
      }
      head = node;
      if (tail == nullptr)
      {
            tail = node;
      }
}

// Node를 제거
void Cache::removeNode(Node *node)
{
      // node의 이전과 다음 노드를 연결하여 제거
      if (node->prev != nullptr)
      {
            node->prev->next = node->next;
      }
      else
      {
            head = node->next;
      }

      if (node->next != nullptr)
      {
            node->next->prev = node->prev;
      }
      else
      {
            tail = node->prev;
      }
}

// Node를 캐시의 가장 앞에 이동
void Cache::moveToHead(Node *node)
{
      removeNode(node);
      addHead(node);
}

// 가장 마지막 Node를 제거
void Cache::removeTail()
{
      // tail이 nullptr인 경우, 리스트가 비어 있음을 의미하므로 함수 종료
      if (tail == nullptr)
      {
            return;
      }

      // tail에 해당하는 노드를 해시 테이블에서 제거
      int index = hashFunction(tail->key); // tail의 key를 기반으로 해시 테이블 인덱스 계산
      Node *current = hashTable[index];
      Node *prev = nullptr;
      // 해시 테이블에서 tail 노드 찾기
      while (current != nullptr && current != tail)
      {
            prev = current;
            current = current->nextValue;
      }

      // tail 노드를 발견한 경우에만 처리
      if (current != nullptr)
      {
            // 중간에 있는 노드면
            if (prev != nullptr)
            {
                  // 이전 노드의 nextValue를 current의 nextValue로 연결
                  prev->nextValue = current->nextValue;
            }
            else
            {
                  // current가 해시 테이블의 첫 번째 노드면
                  hashTable[index] = current->nextValue;
            }

            // current를 연결 리스트에서 제거하고 삭제
            removeNode(current);
            delete current;
            --size;
      }
}

// 새로운 int 타입의 키-값 쌍을 캐시에 추가
void Cache::add(std::string key, int value)
{
      int index = hashFunction(key);
      Node *current = hashTable[index];
      Node *prev = nullptr;

      // 해시 테이블에서 해당 키를 찾음
      while (current != nullptr && current->key != key)
      {
            prev = current;
            current = current->nextValue;
      }

      if (current != nullptr && current->type == "int")
      {
            // 이미 존재하는 int 타입 키이면 값을 갱신하고 가장 앞에 이동
            *(static_cast<int *>(current->value)) = value;
            moveToHead(current);
      }
      else
      {
            // 새로운 노드를 생성하고 캐시의 가장 앞에 추가
            Node *newNode = new Node(key, value);
            if (prev != nullptr)
            {
                  // 충돌이 나면(이전 노드가 존재하면), 연결 리스트로 추가한다.
                  prev->nextValue = newNode;
            }
            else
            {
                  // 첫 노드인 경우 해시 테이블에 직접 추가
                  hashTable[index] = newNode;
            }

            // 현재 노드가 있으면 그 노드 앞에 추가
            newNode->nextValue = current;
            addHead(newNode);
            ++size;

            // 캐시 크기를 초과하면 가장 오래된 노드 제거
            if (size > CACHE_SIZE)
            {
                  removeTail();
            }
      }
}

// 새로운 double 타입의 키-값 쌍을 캐시에 추가
void Cache::add(std::string key, double value)
{
      int index = hashFunction(key);
      Node *current = hashTable[index];
      Node *prev = nullptr;

      // 해시 테이블에서 해당 키를 찾음
      while (current != nullptr && current->key != key)
      {
            prev = current;
            current = current->nextValue;
      }

      if (current != nullptr && current->type == "double")
      {
            // 이미 존재하는 int 타입 키이면 값을 갱신하고 가장 앞에 이동
            *(static_cast<double *>(current->value)) = value;
            moveToHead(current);
      }
      else
      {
            // 새로운 노드를 생성하고 캐시의 가장 앞에 추가
            Node *newNode = new Node(key, value);
            if (prev != nullptr)
            {
                  // 충돌이 나면(이전 노드가 존재하면), 연결 리스트로 추가한다.
                  prev->nextValue = newNode;
            }
            else
            {
                  // 첫 노드인 경우 해시 테이블에 직접 추가
                  hashTable[index] = newNode;
            }

            // 현재 노드가 있으면 그 노드 앞에 추가
            newNode->nextValue = current;
            addHead(newNode);
            ++size;

            // 캐시 크기를 초과하면 가장 오래된 노드 제거
            if (size > CACHE_SIZE)
            {
                  removeTail();
            }
      }
}

// int 타입의 값을 키로부터 가져옴
bool Cache::get(std::string key, int &value)
{
      int index = hashFunction(key);
      Node *current = hashTable[index];

      // 해시 테이블의 연결 리스트를 선형 탐색
      while (current != nullptr)
      {
            // 키가 같으면 타입도 같지만, 혹시 몰라서 타입을 확인함
            // 키와 타입이 일치하는 노드를 찾으면 값을 반환
            if (current->key == key && current->type == "int")
            {
                  value = *(static_cast<int *>(current->value));
                  moveToHead(current);
                  return true;
            }
            current = current->nextValue;
      }
      return false;
}

bool Cache::get(std::string key, double &value)
{
      int index = hashFunction(key);
      Node *current = hashTable[index];

      // 해시 테이블의 연결 리스트를 선형 탐색
      while (current != nullptr)
      {
            // 키가 같으면 타입도 같지만, 혹시 몰라서 타입을 확인함
            // 키와 타입이 일치하는 노드를 찾으면 값을 반환
            if (current->key == key && current->type == "double")
            {
                  value = *(static_cast<double *>(current->value));
                  moveToHead(current);
                  return true;
            }
            current = current->nextValue;
      }
      return false;
}

// 캐시의 모든 노드를 문자열로 표현
std::string Cache::toString()
{
      std::stringstream ss;
      Node *current = head;

      // 연결 리스트를 순회하여 문자열로 변환
      while (current != nullptr)
      {
            ss << "[" << current->key << ": ";
            // 노드의 타입에 따라 값을 문자열로 변환
            if (current->type == "int")
            {
                  ss << *(static_cast<int *>(current->value));
            }
            else if (current->type == "double")
            {
                  ss << (*(static_cast<double *>(current->value)));
            }
            ss << "]";
            current = current->next;
            // 다음 노드가 있으면 화살표로 연결
            if (current != nullptr)
            {
                  ss << " -> ";
            }
      }
      ss << "\n";
      return ss.str();
}
