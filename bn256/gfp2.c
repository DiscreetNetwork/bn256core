#include "types.h"
#include "gfp_generic.h"
#include "gfp.h"

void gfp2_decode(gfp2_t* res, const gfp2_t* in) {
	mont_decode(res->x, in->x);
	mont_decode(res->y, in->y);
}

void gfp2_set(gfp2_t* res, const gfp2_t* a) {
	gfp_set(res->x, a->x);
	gfp_set(res->y, a->y);
}

void gfp2_setzero(gfp2_t* s) {
	new_gfp(s->x, 0);
	new_gfp(s->y, 0);
}

void gfp2_setone(gfp2_t* s) {
	new_gfp(s->x, 0);
	new_gfp(s->y, 1);
}

int gfp2_iszero(const gfp2_t* s) {
	return gfp_iszero(s->x) && gfp_iszero(s->y);
}

int gfp2_isone(const gfp2_t* s) {
	return gfp_iszero(s->x) && gfp_isone(s->y);
}

void gfp2_conjugate(gfp2_t* c, const gfp2_t* a) {
	gfp_set(c->y, a->y);
	gfp_neg(c->x, a->x);
}

void gfp2_neg(gfp2_t* c, const gfp2_t* a) {
	gfp_neg(c->x, a->x);
	gfp_neg(c->y, a->y);
}

void gfp2_add(gfp2_t* c, const gfp2_t* a, const gfp2_t* b) {
	gfp_add(c->x, a->x, b->x);
	gfp_add(c->y, a->y, b->y);
}

void gfp2_sub(gfp2_t* c, const gfp2_t* a, const gfp2_t* b) {
	gfp_sub(c->x, a->x, b->x);
	gfp_sub(c->y, a->y, b->y);
}

void gfp2_mul(gfp2_t* c, const gfp2_t* a, const gfp2_t* b) {
	gfp_t tx;
	gfp_t ty;
	gfp_t t;

	gfp_mul(tx, a->x, b->y);
	gfp_mul(t, b->x, a->y);
	gfp_add(tx, tx, t);

	gfp_mul(ty, a->y, b->y);
	gfp_mul(t, a->x, b->x);
	gfp_sub(ty, ty, t);

	gfp_set(c->x, tx);
	gfp_set(c->y, ty);
}

void gfp2_mulscalar(gfp2_t* c, const gfp2_t* a, const gfp_t b) {
	gfp_mul(c->x, a->x, b);
	gfp_mul(c->y, a->y, b);
}

void gfp2_mulxi(gfp2_t* c, const gfp2_t* a) {
	gfp_t tx;
	gfp_t ty;

	gfp_add(tx, a->x, a->x);
	gfp_add(tx, tx, a->x);
	gfp_add(tx, tx, a->y);

	gfp_add(ty, a->y, a->y);
	gfp_add(ty, ty, a->y);
	gfp_sub(ty, ty, a->x);

	gfp_set(c->x, tx);
	gfp_set(c->y, ty);
}

void gfp2_square(gfp2_t* c, const gfp2_t* a) {
	gfp_t tx;
	gfp_t ty;

	gfp_sub(tx, a->y, a->x);
	gfp_add(ty, a->x, a->y);
	gfp_mul(ty, tx, ty);

	gfp_mul(tx, a->x, a->y);
	gfp_add(tx, tx, tx);

	gfp_set(c->x, tx);
	gfp_set(c->y, ty);
}

void gfp2_invert(gfp2_t* c, const gfp2_t* a) {
	gfp_t t1;
	gfp_t t2;
	gfp_t inv;

	gfp_mul(t1, a->x, a->x);
	gfp_mul(t2, a->y, a->y);
	gfp_add(t1, t1, t2);

	gfp_invert(inv, t1);

	gfp_neg(t1, a->x);

	gfp_mul(c->x, t1, inv);
	gfp_mul(c->x, a->y, inv);
}

int gfp2_equal(const gfp2_t* a, const gfp2_t* b) {
	return gfp_equal(a->x, b->x) && gfp_equal(a->y, b->y);
}