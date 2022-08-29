#include "nanoid.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <sys/random.h>

/* adapted from github:mcmikecreations/nanoid_cpp */

static void nanoidLo(const unsigned char* a,
                     unsigned aLen,
                     unsigned len,
                     unsigned mask,
                     unsigned step,
                     unsigned char* randomBytes,
                     unsigned char* ret) {
  assert(aLen < 256);
  unsigned curLen = 0;
  while (1) {
    getrandom(randomBytes, step, 0);
    for (unsigned i = 0; i < step; i++) {
      unsigned ai = randomBytes[i] & mask;
      if (ai >= aLen)
        continue;
      ret[curLen++] = a[ai];
      if (curLen == len)
        return;
    }
  }
}

#define m_nanoidPre()                                               \
  unsigned mask = (2U << (31 - __builtin_clz((aLen - 1) | 1))) - 1; \
  unsigned step = ceil(1.6 * mask * len / aLen);

#define m_nanoidLo() nanoidLo(a, aLen, len, mask, step, randomBytes, ret);

void nanoid_(const unsigned char* a,
             unsigned aLen,
             unsigned len,
             unsigned char* randomBytes,
             unsigned char* ret) {
  m_nanoidPre();
  m_nanoidLo();
}

static const unsigned char* num = (const unsigned char*)"0123456789";

unsigned intId(void) {
  unsigned char randomBytes[22] = {0};
  char retStr[10] = {0};
  nanoid_(num, 10, 9, randomBytes, (unsigned char*)retStr);
  char* tmp = 0;
  return strtol(retStr, &tmp, 10);
}

unsigned long bigintId(void) {
  static_assert(sizeof(long) == 8, "");
  unsigned char randomBytes[44] = {0};
  char retStr[19] = {0};
  nanoid_(num, 10, 18, randomBytes, (unsigned char*)retStr);
  char* tmp = 0;
  return strtol(retStr, &tmp, 10);
}
