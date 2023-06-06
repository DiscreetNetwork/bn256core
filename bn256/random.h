#ifndef RANDOM_H
#define RANDOM_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
# ifdef __GNUC__
#  pragma GCC diagnostic ignored "-Wlong-long"
# endif
extern "C" {
#endif

	void generate_randombytes(size_t n, void* res);

#ifdef __cplusplus
}
#endif

#endif // RANDOM_H