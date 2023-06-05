#if !defined(TYPES_H)
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>

typedef uint64_t gfp_t[4];

typedef struct __gfp2 {
	gfp_t x;
	gfp_t y;
} gfp2_t;

typedef struct __gfp6 {
	struct __gfp2 x;
	struct __gfp2 y;
	struct __gfp2 z;
} gfp6_t;

typedef struct __gfp12 {
	struct __gfp6 x;
	struct __gfp6 y;
} gfp12_t;

typedef struct __curvepoint {
	gfp_t x;
	gfp_t y;
	gfp_t z;
	gfp_t t;
} curvepoint_t;

typedef struct __twitstpoint {
	gfp2_t x;
	gfp2_t y;
	gfp2_t z;
	gfp2_t t;
} twistpoint_t;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TYPES_H