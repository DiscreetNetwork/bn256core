#include <assert.h>
#include <stddef.h>
#include <string.h>

static inline void* padd(void* p, size_t i) {
    return (char*)p + i;
}

static void generate_system_randombytes(size_t n, void* res);

#if defined(_WIN32)

#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>

static void generate_system_randombytes(size_t n, void* res) {
    HCRYPTPROV prov;
    CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
    CryptGenRandom(prov, (DWORD)n, res);
    CryptReleaseContext(prov, 0);
}

#else 

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void generate_system_randombytes(size_t n, void* result) {
    int fd;
    if ((fd = open("/dev/urandom", O_RDONLY | O_NOCTTY | O_CLOEXEC)) < 0) {
        err(EXIT_FAILURE, "open /dev/urandom");
    }
    for (;;) {
        ssize_t res = read(fd, result, n);
        if ((size_t)res == n) {
            break;
        }
        if (res < 0) {
            if (errno != EINTR) {
                err(EXIT_FAILURE, "read /dev/urandom");
            }
        }
        else if (res == 0) {
            errx(EXIT_FAILURE, "read /dev/urandom: end of file");
        }
        else {
            result = padd(result, (size_t)res);
            n -= (size_t)res;
        }
    }
    if (close(fd) < 0) {
        err(EXIT_FAILURE, "close /dev/urandom");
    }
}

#endif

void generate_randombytes(size_t n, void* res) {
    generate_system_randombytes(n, res);
}

