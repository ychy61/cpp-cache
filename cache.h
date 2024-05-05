#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#define CACHE_SIZE 10 // 캐시의 최대 크기

class Cache
{
private:
  class Node
  {
  public:
    std::string key;  // 키
    std::string type; // 타입
    void *value;      // 값
    Node *prev;       // 이전 노드
    Node *next;       // 다음 노드
    Node *nextValue;  // 다음 값

    Node(std::string k, int v);
    Node(std::string k, double v);
  };
  static const int HASH_SIZE = 10; // 해시 테이블의 크기
  Node *hashTable[HASH_SIZE];      // 해시 테이블
  Node *head;                      // 캐시의 첫 번째 노드
  Node *tail;                      // 캐시의 마지막 노드
  int size;                        // 현재 캐시의 크기

  int hashFunction(const std::string &key);
  void addHead(Node *node);
  void removeNode(Node *node);
  void moveToHead(Node *node);
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
