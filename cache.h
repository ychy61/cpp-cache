#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <sstream>
#include <iostream>

#define CACHE_SIZE 10 //캐시 사이즈

class Cache {
private:
  // TODO: private inner struct/class 선언 가능
  // TODO: private 멤버 변수와 함수 추가 가능
    struct Node {
        std::string key;       // 노드의 키
        std::string type;      // 노드의 타입 ("int" 또는 "double")
        void* value;           // 노드의 값
        Node* nextValue;       // 동일한 키의 다음 노드
        Node* next;            // 다음 노드

        //int 타입 생성자
        Node(std::string k, int v)
            : key(k), type("int"), nextValue(nullptr), next(nullptr) {
            value = new int(v);
        }

        //double 타입 생성자
        Node(std::string k, double v)
            : key(k), type("double"), nextValue(nullptr), next(nullptr) {
            value = new double(v);
        }
    };

  Node* head; //head 노드(제일 최근에 추가된 노드)
  int size; //현재 캐시 사이즈

  //노드를 앞쪽으로 이동시킨다.
  void addHead(Node* node, Node* prev);

  //마지막 노드를 삭제한다.
  void removeTail();

public:
  Cache();
  ~Cache();
  // int를 cache에 추가한다
  void add(std::string key, int value);

  // double을 cache에 추가한다
  void add(std::string key, double value);

  // key에 해당하는 value를 cache에서 가져온다
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, int &value);

  // key에 해당하는 value를 cache에서 가져온다.
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, double &value);

  // 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
  // 다음과 같이 표현된 문자열을 반환한다
  // [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
  std::string toString();
};

#endif