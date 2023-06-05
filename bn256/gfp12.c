#include "types.h"
#include "gfp6.h"
#include "constants.h"

void gfp12_set(gfp12_t* c, const gfp12_t* a) {
	gfp6_set(&c->x, &a->x);
	gfp6_set(&c->y, &a->y);
}

void gfp12_setzero(gfp12_t* c) {
	gfp6_setzero(&c->x);
	gfp6_setzero(&c->y);
}

void gfp12_setone(gfp12_t* c) {
	gfp6_setzero(&c->x);
	gfp6_setone(&c->y);
}

void gfp12_iszero(const gfp12_t* c) {
	return gfp6_iszero(&c->x) && gfp6_iszero(&c->y);
}

void gfp12_isone(const gfp12_t* c) {
	return gfp6_iszero(&c->x) && gfp6_isone(&c->y);
}

// TODO: complete implementation. Zzzz
