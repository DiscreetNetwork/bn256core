#include "types.h"
#include "constants.h"
#include "gfp2.h"

void twistpoint_set(twistpoint_t* c, const twistpoint_t* a) {
	gfp2_set(&c->x, &a->x);
	gfp2_set(&c->y, &a->y);
	gfp2_set(&c->z, &a->z);
	gfp2_set(&c->t, &a->t);
}

void twistpoint_zero(twistpoint_t* c) {
	gfp2_setzero(&c->x);
	gfp2_setzero(&c->y);
	gfp2_setzero(&c->z);
	gfp2_setzero(&c->t);
}

void twistpoint_make_affine(twistpoint_t* c) {
	if (gfp2_isone(&c->z)) {
		return;
	}
	else if (gfp2_iszero(&c->z)) {
		gfp2_setzero(&c->x);
		gfp2_setone(&c->y);
		gfp2_setzero(&c->t);
		return;
	}

	gfp2_t zInv, zInv2, t;

	gfp2_invert(&zInv, &c->z);
	gfp2_mul(&t, &c->y, &zInv);
	gfp2_square(&zInv2, &zInv);
	gfp2_mul(&c->y, &t, &zInv2);
	gfp2_mul(&t, &c->x, &zInv2);
	gfp2_set(&c->x, &t);
	gfp2_setone(&c->z);
	gfp2_setone(&c->t);
}

void twistpoint_set_infinity(twistpoint_t* c) {
	gfp2_setzero(&c->x);
	gfp2_setone(&c->y);
	gfp2_setzero(&c->z);
	gfp2_setzero(&c->t);
}

int twistpoint_is_infinity(const twistpoint_t* c) {
	return gfp2_iszero(&c->z);
}

int twistpoint_is_on_curve(const twistpoint_t* c) {
	twistpoint_make_affine(c);

	if (twistpoint_is_infinity(c)) {
		return 1;
	}

	gfp2_t y2, x3;
	gfp2_square(&y2, &c->y);
	gfp2_square(&x3, &c->x);
	gfp2_mul(&x3, &x3, &c->x);
	gfp2_add(&x3, &x3, &curveg2b);

	return gfp2_equal(&y2, &x3);
}

void twistpoint_double(twistpoint_t* c, const twistpoint_t* a) {
	gfp2_t A, B, C;
	gfp2_t t, t2;
	gfp2_t d, e, f;

	gfp2_square(&A, &a->x);
	gfp2_square(&B, &a->y);
	gfp2_square(&C, &B);

	gfp2_add(&t, &a->x, &B);
	gfp2_square(&t2, &t);

	gfp2_sub(&t, &t2, &A);
	gfp2_sub(&t2, &t, &C);

	gfp2_add(&d, &t2, &t2);
	gfp2_add(&t, &A, &A);
	gfp2_add(&e, &t, &A);
	gfp2_square(&f, &e);

	gfp2_add(&t, &d, &d);
	gfp2_sub(&c->x, &f, &t);

	gfp2_mul(&c->z, &a->y, &a->z);
	gfp2_add(&c->z, &c->z, &c->z);

	gfp2_add(&t, &C, &C);
	gfp2_add(&t2, &t, &t);
	gfp2_add(&t, &t2, &t2);
	gfp2_sub(&c->y, &d, &c->x);
	gfp2_mul(&t2, &e, &c->y);
	gfp2_sub(&c->y, &t2, &t);
}

void twistpoint_add(twistpoint_t* c, const twistpoint_t* a, const twistpoint_t* b) {
	if (twistpoint_is_infinity(a)) {
		twistpoint_set(c, b);
		return;
	}

	if (twistpoint_is_infinity(b)) {
		twistpoint_set(c, a);
		return;
	}

	gfp2_t z12, z22, u1, u2, t, s1, s2, h, i, j, r, v, t4, t6;
	int x_eq, y_eq;

	gfp2_square(&z12, &a->z);
	gfp2_square(&z22, &b->z);
	gfp2_mul(&u1, &a->x, &z22);
	gfp2_mul(&u2, &b->x, &z12);

	gfp2_mul(&t, &b->z, &z22);
	gfp2_mul(&s1, &a->y, &t);

	gfp2_mul(&t, &a->z, &z12);
	gfp2_mul(&s2, &b->y, &t);

	gfp2_sub(&h, &u2, &u1);
	x_eq = gfp2_iszero(&h);

	gfp2_add(&t, &h, &h);
	gfp2_square(&i, &t);
	gfp2_mul(&j, &h, &i);

	gfp2_sub(&t, &s2, &s1);
	y_eq = gfp2_iszero(&t);

	if (x_eq && y_eq) {
		twistpoint_double(c, a);
		return;
	}

	gfp2_add(&r, &t, &t);
	gfp2_mul(&v, &u1, &i);

	gfp2_square(&t4, &r);
	gfp2_add(&t, &v, &v);
	gfp2_sub(&t6, &t4, &j);
	gfp2_sub(&c->x, &t6, &t);

	gfp2_sub(&t, &v, &c->x);
	gfp2_mul(&t4, &s1, &j);
	gfp2_add(&t6, &t4, &t4);
	gfp2_mul(&t4, &r, &t);
	gfp2_sub(&c->y, &t4, &t6);

	gfp2_add(&t, &a->z, &b->z);
	gfp2_square(&t4, &t);
	gfp2_sub(&t, &t4, &z12);
	gfp2_sub(&t4, &t, &z22);
	gfp2_mul(&c->z, &t4, &h);
}

void twistpoint_mul(twistpoint_t* c, const twistpoint_t* a, const struct bn* scalar) {
	twistpoint_t sum, t;
	twistpoint_set_infinity(&sum);

	for (int i = bignum_bitlen(scalar); i >= 0; i--) {
		twistpoint_double(&t, &sum);
		if (bignum_bit(scalar, i) != 0) {
			twistpoint_add(&sum, &t, a);
		}
		else {
			twistpoint_set(&sum, &t);
		}
	}

	twistpoint_set(c, &sum);
}

void twistpoint_neg(twistpoint_t* c, const twistpoint_t* a) {
	gfp2_set(&c->x, &a->x);
	gfp2_neg(&c->y, &a->y);
	gfp2_set(&c->z, &a->z);
	gfp2_setzero(&c->t);
}