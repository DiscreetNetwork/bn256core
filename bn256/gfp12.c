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

int gfp12_iszero(const gfp12_t* c) {
	return gfp6_iszero(&c->x) && gfp6_iszero(&c->y);
}

int gfp12_isone(const gfp12_t* c) {
	return gfp6_iszero(&c->x) && gfp6_isone(&c->y);
}

void gfp12_conjugate(gfp12_t* c, const gfp12_t* a) {
	gfp6_neg(&c->x, &a->x);
	gfp6_set(&c->y, &a->y);
}

void gfp12_neg(gfp12_t* c, const gfp12_t* a) {
	gfp6_neg(&c->x, &a->x);
	gfp6_neg(&c->y, &a->y);
}

void gfp12_frobenius(gfp12_t* c, const gfp12_t* a) {
	gfp6_frobenius(&c->x, &a->x);
	gfp6_frobenius(&c->y, &a->y);
	gfp6_mulscalar(&c->x, &c->x, &xiToPMinus1Over6);
}

void gfp12_frobeniusp2(gfp12_t* c, const gfp12_t* a) {
	gfp6_frobeniusp2(&c->x, &a->x);
	gfp6_mulgfp(&c->x, &c->x, xiToPSquaredMinus1Over6);
	gfp6_frobeniusp2(&c->y, &a->y);
}

void gfp12_frobeniusp4(gfp12_t* c, const gfp12_t* a) {
	gfp6_frobeniusp4(&c->x, &a->x);
	gfp6_mulgfp(&c->x, &c->x, xiToPSquaredMinus1Over3);
	gfp6_frobeniusp4(&c->y, &a->y);
}

void gfp12_add(gfp12_t* c, const gfp12_t* a, const gfp12_t* b) {
	gfp6_add(&c->x, &a->x, &b->x);
	gfp6_add(&c->y, &a->y, &b->y);
}

void gfp12_sub(gfp12_t* c, const gfp12_t* a, const gfp12_t* b) {
	gfp6_sub(&c->x, &a->x, &b->x);
	gfp6_sub(&c->y, &a->y, &b->y);
}

void gfp12_mul(gfp12_t* c, const gfp12_t* a, const gfp12_t* b) {
	gfp6_t tx, ty, t;
	
	gfp6_mul(&tx, &a->x, &b->y);
	gfp6_mul(&t, &b->x, &a->y);
	gfp6_add(&tx, &tx, &t);

	gfp6_mul(&ty, &a->y, &b->y);
	gfp6_mul(&t, &a->x, &b->x);
	gfp6_multau(&t, &t);

	gfp6_set(&c->x, &tx);
	gfp6_add(&c->y, &ty, &t);
}

void gfp12_mulscalar(gfp12_t* c, const gfp12_t* a, const gfp6_t* b) {
	gfp6_mul(&c->x, &a->x, b);
	gfp6_mul(&c->y, &a->y, b);
}

void gfp12_square(gfp12_t* c, const gfp12_t* a) {
	gfp6_t v0, t, ty;

	gfp6_mul(&v0, &a->x, &a->y);
	
	gfp6_multau(&t, &a->x);
	gfp6_add(&t, &a->y, &t);
	
	gfp6_add(&ty, &a->x, &a->y);
	gfp6_mul(&ty, &ty, &t);
	gfp6_sub(&ty, &ty, &v0);
	gfp6_multau(&t, &v0);
	gfp6_sub(&ty, &ty, &t);

	gfp6_add(&c->x, &v0, &v0);
	gfp6_set(&c->y, &ty);
}

void gfp12_invert(gfp12_t* c, const gfp12_t* a) {
	gfp6_t t1, t2;

	gfp6_square(&t1, &a->x);
	gfp6_square(&t2, &a->y);
	gfp6_multau(&t1, &t1);
	gfp6_sub(&t1, &t2, &t1);
	gfp6_invert(&t2, &t1);

	gfp6_neg(&c->x, &a->x);
	gfp6_set(&c->y, &a->y);
	gfp12_mulscalar(c, c, &t2);
}

void gfp12_exp(gfp12_t* c, const gfp12_t* a, const struct bn* power) {
	gfp12_t sum;
	gfp12_t t;

	gfp12_setone(&sum);

	for (int i = bignum_bitlen(power) - 1; i >= 0; i--) {
		gfp12_square(&t, &sum);

		if (bignum_bit(power, i) != 0) {
			gfp12_mul(&sum, &t, a);
		}
		else {
			gfp12_set(&sum, &t);
		}
	}

	gfp12_set(c, &sum);
}


