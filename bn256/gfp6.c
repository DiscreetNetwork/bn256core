#include "types.h"
#include "gfp_generic.h"
#include "gfp.h"
#include "gfp2.h"
#include "constants.h"

void gfp6_set(gfp6_t* c, const gfp6_t* a) {
	gfp2_set(&c->x, &a->x);
	gfp2_set(&c->y, &a->y);
	gfp2_set(&c->z, &a->z);
}

void gfp6_setzero(gfp6_t* c) {
	gfp2_setzero(&c->x);
	gfp2_setzero(&c->y);
	gfp2_setzero(&c->z);
}

void gfp6_setone(gfp6_t* c) {
	gfp2_setzero(&c->x);
	gfp2_setzero(&c->y);
	gfp2_setone(&c->z);
}

int gfp6_iszero(const gfp6_t* c) {
	return gfp2_iszero(&c->x) && gfp2_iszero(&c->y) && gfp2_iszero(&c->z);
}

int gfp6_isone(const gfp6_t* c) {
	return gfp2_iszero(&c->x) && gfp2_iszero(&c->y) && gfp2_isone(&c->z);
}

void gfp6_neg(gfp6_t* c, const gfp6_t* a) {
	gfp2_neg(&c->x, &a->x);
	gfp2_neg(&c->y, &a->y);
	gfp2_neg(&c->z, &a->z);
}

void gfp6_frobenius(gfp6_t* c, const gfp6_t* a) {
	gfp2_conjugate(&c->x, &a->x);
	gfp2_conjugate(&c->y, &a->y);
	gfp2_conjugate(&c->z, &a->z);

	gfp2_mul(&c->x, &c->x, &xiTo2PMinus2Over3);
	gfp2_mul(&c->y, &c->y, &xiToPMinus1Over3);
}

void gfp6_frobeniusp2(gfp6_t* c, const gfp6_t* a) {
	gfp2_mulscalar(&c->x, &a->x, xiTo2PSquaredMinus2Over3);
	gfp2_mulscalar(&c->y, &a->y, xiToPSquaredMinus1Over3);
	gfp2_set(&c->z, &a->z);
}

void gfp6_frobeniusp4(gfp6_t* c, const gfp6_t* a) {
	gfp2_mulscalar(&c->x, &a->x, xiToPSquaredMinus1Over3);
	gfp2_mulscalar(&c->y, &a->y, xiTo2PSquaredMinus2Over3);
	gfp2_set(&c->z, &a->z);
}

void gfp6_add(gfp6_t* c, const gfp6_t* a, const gfp6_t* b) {
	gfp2_add(&c->x, &a->x, &b->x);
	gfp2_add(&c->y, &a->y, &b->y);
	gfp2_add(&c->z, &a->z, &b->z);
}

void gfp6_sub(gfp6_t* c, const gfp6_t* a, const gfp6_t* b) {
	gfp2_sub(&c->x, &a->x, &b->x);
	gfp2_sub(&c->y, &a->y, &b->y);
	gfp2_sub(&c->z, &a->z, &b->z);
}

void gfp6_mul(gfp6_t* c, const gfp6_t* a, const gfp6_t* b) {
	gfp2_t v0, v1, v2;
	gfp2_t t0, t1;
	gfp2_t tx, ty, tz;

	gfp2_mul(&v0, &a->z, &b->z);
	gfp2_mul(&v1, &a->y, &b->y);
	gfp2_mul(&v2, &a->x, &b->x);

	gfp2_add(&t0, &a->x, &a->y);
	gfp2_add(&t1, &b->x, &b->y);
	gfp2_mul(&tz, &t0, &t1);

	gfp2_sub(&tz, &tz, &v1);
	gfp2_sub(&tz, &tz, &v2);
	gfp2_mulxi(&tz, &tz);
	gfp2_add(&tz, &tz, &v0);

	gfp2_add(&t0, &a->y, &a->z);
	gfp2_add(&t1, &b->y, &b->z);
	gfp2_mul(&ty, &t0, &t1);

	gfp2_mulxi(&t0, &v2);

	gfp2_sub(&ty, &ty, &v0);
	gfp2_sub(&ty, &ty, &v1);
	gfp2_add(&ty, &ty, &t0);

	gfp2_add(&t0, &a->x, &a->z);
	gfp2_add(&t1, &b->x, &b->z);
	gfp2_mul(&tx, &t0, &t1);

	gfp2_sub(&tx, &tx, &v0);
	gfp2_add(&tx, &tx, &v1);
	gfp2_sub(&tx, &tx, &v2);

	gfp2_set(&c->x, &tx);
	gfp2_set(&c->y, &ty);
	gfp2_set(&c->z, &tz);
}

void gfp6_mulscalar(gfp6_t* c, const gfp6_t* a, const gfp2_t* b) {
	gfp2_mul(&c->x, &a->x, b);
	gfp2_mul(&c->y, &a->y, b);
	gfp2_mul(&c->z, &a->z, b);
}

void gfp6_mulgfp(gfp6_t* c, const gfp6_t* a, const gfp_t b) {
	gfp2_mulscalar(&c->x, &a->x, b);
	gfp2_mulscalar(&c->y, &a->y, b);
	gfp2_mulscalar(&c->z, &a->z, b);
}

void gfp6_multau(gfp6_t* c, const gfp6_t* a) {
	gfp2_t tz, ty;

	gfp2_mulxi(&tz, &a->x);
	gfp2_set(&ty, &a->y);

	gfp2_set(&c->y, &a->z);
	gfp2_set(&c->x, &ty);
	gfp2_set(&c->z, &tz);
}

void gfp6_square(gfp6_t* c, const gfp6_t* a) {
	gfp2_t v0, v1, v2;
	gfp2_t c0, c1, c2;
	gfp2_t xiv2;

	gfp2_square(&v0, &a->z);
	gfp2_square(&v1, &a->y);
	gfp2_square(&v2, &a->x);

	gfp2_add(&c0, &a->x, &a->y);

	gfp2_square(&c0, &c0);
	gfp2_sub(&c0, &c0, &v1);
	gfp2_sub(&c0, &c0, &v2);
	gfp2_mulxi(&c0, &c0);
	gfp2_add(&c0, &c0, &v0);

	gfp2_add(&c1, &a->y, &a->z);
	gfp2_square(&c1, &c1);
	gfp2_sub(&c1, &c1, &v0);
	gfp2_sub(&c1, &c1, &v1);

	gfp2_mulxi(&xiv2, &v2);
	gfp2_add(&c1, &c1, &xiv2);

	gfp2_add(&c2, &a->x, &a->z);

	gfp2_square(&c2, &c2);
	gfp2_sub(&c2, &c2, &v0);
	gfp2_add(&c2, &c2, &v1);
	gfp2_sub(&c2, &c2, &v2);

	gfp2_set(&c->x, &c2);
	gfp2_set(&c->y, &c1);
	gfp2_set(&c->z, &c0);
}

void gfp6_invert(gfp6_t* c, const gfp6_t* a) {
	gfp2_t t1, A, B, C, F;

	gfp2_mul(&t1, &a->x, &a->y);
	gfp2_mulxi(&t1, &t1);

	gfp2_square(&A, &a->z);
	gfp2_sub(&A, &A, &t1);

	gfp2_square(&B, &a->x);
	gfp2_mulxi(&B, &B);
	gfp2_mul(&t1, &a->y, &a->z);
	gfp2_sub(&B, &B, &t1);

	gfp2_square(&C, &a->y);
	gfp2_mul(&t1, &a->x, &a->z);
	gfp2_sub(&C, &C, &t1);

	gfp2_mul(&F, &C, &a->y);
	gfp2_mulxi(&F, &F);
	gfp2_mul(&t1, &A, &a->z);
	gfp2_add(&F, &F, &t1);
	gfp2_mul(&t1, &B, &a->x);
	gfp2_mulxi(&t1, &t1);
	gfp2_add(&F, &F, &t1);

	gfp2_invert(&F, &F);

	gfp2_mul(&c->x, &C, &F);
	gfp2_mul(&c->y, &B, &F);
	gfp2_mul(&c->z, &A, &F);
}

