#include <unimplemented.h>

extern int __wasilibc_dttoif(int);
extern int setjmp(void *);

int _Z17__wasilibc_dttoifi(int);
int _Z17__wasilibc_dttoifi(int a) { return __wasilibc_dttoif(a); }

int _Z6setjmpPv(void *);
int _Z6setjmpPv(void *addr) { return setjmp(addr); }

int posix_madvise(void *, int, int);
int posix_madvise(void *addr, int len, int advise) { return 0; }

int dup2(int, int);
int dup2(int a, int b) {
  (void)unimplemented(58);
  return -1;
}
