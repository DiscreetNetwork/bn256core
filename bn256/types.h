#pragma once

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
