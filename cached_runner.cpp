#include "cached_runner.h"

// TODO: 필요한 함수 구현
CachedRunner::CachedRunner(Cache &cache):currCache(cache){
      hit = 0;
      miss = 0;
}

double CachedRunner::multiply(std::string filename){
      std::string key = "multiply(" + filename + ")";
      double result;

      // 캐시에 있으면,
      if (currCache.get(key, result) == true) {
            hit++;
            return result;
      } else {
            //캐시에 없으면,
            miss++;
            result = TaskRunner::multiply(filename);
            //캐시에 추가
            currCache.add(key, result);
            return result;
      }
}

int CachedRunner::palindrome(std::string filename){
      std::string key = "palindrome(" + filename + ")";
      int result;

      // 캐시에 있으면,
      if (currCache.get(key, result)) {
            hit++;
            return result;
      } else {
            //캐시에 없으면,
            miss++;
            result = TaskRunner::palindrome(filename);
            //캐시에 추가
            currCache.add(key, result);
            return result;
      }
}

// 캐시에 히트한 횟수를 반환한다
int CachedRunner::hits(){
      return hit;
}

// 캐시에 미스한 횟수를 반환한다
int CachedRunner::misses(){
      return miss;
}