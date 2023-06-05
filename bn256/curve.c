#include "types.h"
#include "gfp.h"
#include "gfp_generic.h"
#include "constants.h"

void curvepoint_set(curvepoint_t* c, const curvepoint_t* a) {
	gfp_set(c->x, a->x);
	gfp_set(c->y, a->y);
	gfp_set(c->z, a->z);
	gfp_set(c->t, a->t);
}

int curvepoint_is_infinity(const curvepoint_t* c) {
	return gfp_iszero(c->z);
}

void curvepoint_set_infinity(curvepoint_t* c) {
	new_gfp(c->x, 0);
	new_gfp(c->y, 1);
	new_gfp(c->z, 0);
	new_gfp(c->t, 0);
}

void curvepoint_make_affine(curvepoint_t* c) {
	if (gfp_isone(c->z)) return;
	else if (gfp_iszero(c->z)) {
		new_gfp(c->x, 0);
		new_gfp(c->y, 1);
		new_gfp(c->t, 0);
		return;
	}

	gfp_t zInv, t, zInv2;
	
	gfp_invert(zInv, c->z);
	
	gfp_mul(t, c->y, zInv);
	gfp_mul(zInv2, zInv, zInv);

	gfp_mul(c->x, c->x, zInv2);
	gfp_mul(c->y, t, zInv2);

	new_gfp(c->z, 1);
	new_gfp(c->t, 1);
}

int curvepoint_is_on_curve(const curvepoint_t* c) {
	curvepoint_make_affine(c);
	
	if (curvepoint_is_infinity(c)) return 1;

	gfp_t y2, x3;

	gfp_mul(y2, c->y, c->y);
	gfp_mul(x3, c->x, c->x);
	gfp_mul(x3, x3, c->x);
	gfp_add(x3, x3, curveg1b);

	return gfp_equal(y2, x3);
}

void curvepoint_double(curvepoint_t* c, const curvepoint_t* a) {
	gfp_t A, B, C;
	gfp_t t, t2;
	gfp_t d, e, f;

	gfp_mul(A, a->x, a->x);
	gfp_mul(B, a->y, a->y);
	gfp_mul(C, B, B);

	gfp_add(t, a->x, B);
	gfp_mul(t2, t, t);
	gfp_sub(t, t2, A);
	gfp_sub(t2, t, C);

	gfp_add(d, t2, t2);
	gfp_add(t, A, A);
	gfp_add(e, t, A);
	gfp_mul(f, e, e);

	gfp_add(t, d, d);
	gfp_sub(c->x, f, t);

	gfp_mul(c->z, a->y, a->z);
	gfp_add(c->z, c->z, c->z);

	gfp_add(t, C, C);
	gfp_add(t2, t, t);
	gfp_add(t, t2, t2);
	gfp_sub(c->y, d, c->x);
	gfp_mul(t2, e, c->y);
	gfp_sub(c->y, t2, t);
}

void curvepoint_add(curvepoint_t* c, const curvepoint_t* a, const curvepoint_t* b) {
	if (curvepoint_is_infinity(a)) {
		curvepoint_set(c, b);
		return;
	}

	if (curvepoint_is_infinity(b)) {
		curvepoint_set(c, a);
		return;
	}

	gfp_t z12, z22, u1, u2, t, s1, s2;
	gfp_t h, i, j, r, v, t4, t6;
	int x_eq, y_eq;

	// compute z12, z22, u1, u2, s1, s2
	gfp_mul(z12, a->z, a->z);
	gfp_mul(z22, b->z, b->z);

	gfp_mul(u1, a->x, z22);
	gfp_mul(u2, b->x, z12);

	gfp_mul(t, b->z, z22);
	gfp_mul(s1, a->y, t);

	gfp_mul(t, a->z, z12);
	gfp_mul(s2, b->y, t);

	// h
	gfp_sub(h, u2, u1);
	x_eq = gfp_iszero(h);

	// i
	gfp_add(t, h, h);
	gfp_mul(i, t, t);

	// j
	gfp_mul(j, h, i);

	gfp_sub(t, s2, s1);
	y_eq = gfp_iszero(t);
	if (x_eq && y_eq) {
		curvepoint_double(c, a);
		return;
	}

	// r
	gfp_add(r, t, t);

	// v
	gfp_mul(v, u1, i);

	// t4 & t6
	gfp_mul(t4, r, r);
	gfp_add(t, v, v);
	gfp_sub(t6, t4, j);

	gfp_sub(c->x, t6, t);

	gfp_sub(t, v, c->x);
	gfp_mul(t4, s1, j);
	gfp_add(t6, t4, t4);
	gfp_mul(t4, r, t);
	gfp_sub(c->y, t4, t6);

	gfp_add(t, a->z, b->z);
	gfp_mul(t4, t, t);
	gfp_sub(t, t4, z12);
	gfp_sub(t4, t, z22);
	gfp_mul(c->z, t4, h);
}

void curvepoint_mul(curvepoint_t* c, const curvepoint_t* a, const struct bn* scalar) {
	curvepoint_t sum, t;
	curvepoint_set_infinity(&sum);

	for (int i = bignum_bitlen(scalar); i >= 0; i--) {
		curvepoint_double(&t, &sum);
		if (bignum_bit(scalar, i) != 0) {
			curvepoint_add(&sum, &t, a);
		}
		else {
			curvepoint_set(&sum, &t);
		}
	}

	curvepoint_set(c, &sum);
}

void curvepoint_neg(curvepoint_t* c, const curvepoint_t* a) {
	gfp_set(c->x, a->x);
	gfp_neg(c->y, a->y);
	gfp_set(c->z, a->z);
	new_gfp(c->t, 0);
}