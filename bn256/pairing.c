#include "curve.h"
#include "twist.h"
#include "gfp2.h"
#include "gfp.h"
#include "gfp6.h"
#include "gfp12.h"
#include "gfp_generic.h"
#include "constants.h"
#include "types.h"

void line_func_add(gfp2_t* a, gfp2_t* b, gfp2_t* c, twistpoint_t* rout, const twistpoint_t* r, const twistpoint_t* p, const curvepoint_t* q, const gfp2_t* r2) {
	gfp2_t B, D, H, I, E, J, L1, V, t, t2;
	twistpoint_t r0;

	gfp2_mul(&B, &p->x, &r->t);

	gfp2_add(&D, &p->y, &r->z);
	gfp2_square(&D, &D);
	gfp2_sub(&D, &D, &r2);
	gfp2_sub(&D, &D, &r->t);
	gfp2_mul(&D, &D, &r->t);

	gfp2_sub(&H, &B, &r->x);
	gfp2_square(&I, &H);

	gfp2_add(&E, &I, &I);
	gfp2_add(&E, &E, &E);

	gfp2_mul(&J, &H, &E);

	gfp2_sub(&L1, &D, &r->y);
	gfp2_sub(&L1, &L1, &r->y);

	gfp2_mul(&V, &r->x, &E);

	gfp2_square(&r0.x, &L1);
	gfp2_sub(&r0.x, &r0.x, &J);
	gfp2_sub(&r0.x, &r0.x, &V);
	gfp2_sub(&r0.x, &r0.x, &V);

	gfp2_add(&r0.z, &r->z, &H);
	gfp2_square(&r0.z, &r0.z);
	gfp2_sub(&r0.z, &r0.z, &r->t);
	gfp2_sub(&r0.z, &r0.z, &I);

	gfp2_sub(&t, &V, &r0.x);
	gfp2_mul(&t, &t, &L1);
	gfp2_mul(&t2, &r->y, &J);
	gfp2_add(&t2, &t2, &t2);
	gfp2_sub(&r0.y, &t, &t2);

	gfp2_square(&r0.t, &r0.z);

	gfp2_add(&t, &p->y, &r0.z);
	gfp2_square(&t, &t);
	gfp2_sub(&t, &t, &r2);
	gfp2_sub(&t, &t, &r0.t);

	gfp2_mul(&t2, &L1, &p->x);
	gfp2_add(&t2, &t2, &t2);

	gfp2_sub(&a, &t2, &t);

	gfp2_mulscalar(&c, &r0.z, q->y);
	gfp2_add(&c, &c, &c);
	
	gfp2_neg(&b, &L1);
	gfp2_mulscalar(&b, &b, q->x);
	gfp2_add(&b, &b, &b);

	twistpoint_set(rout, &r0);
}

void line_func_double(gfp2_t* a, gfp2_t* b, gfp2_t* c, twistpoint_t* rout, const twistpoint_t* r, const curvepoint_t* q) {
	gfp2_t A, B, C, D, E, G, t;
	twistpoint_t r0;

	gfp2_square(&A, &r->x);
	gfp2_square(&B, &r->y);
	gfp2_square(&C, &B);

	gfp2_add(&D, &r->x, &B);
	gfp2_square(&D, &D);
	gfp2_sub(&D, &D, &A);
	gfp2_sub(&D, &D, &C);
	gfp2_add(&D, &D, &D);

	gfp2_add(&E, &A, &A);
	gfp2_add(&E, &E, &A);

	gfp2_square(&G, &E);

	gfp2_sub(&r0.x, &G, &D);
	gfp2_sub(&r0.x, &r0.x, &D);

	gfp2_add(&r0.z, &r->y, &r->z);
	gfp2_square(&r0.z, &r0.z);
	gfp2_sub(&r0.z, &r0.z, &B);
	gfp2_sub(&r0.z, &r0.z, &r->t);

	gfp2_sub(&r0.y, &D, &r0.x);
	gfp2_mul(&r0.y, &r0.y, &E);
	gfp2_add(&t, &C, &C);
	gfp2_add(&t, &t, &t);
	gfp2_add(&t, &t, &t);
	gfp2_sub(&r0.y, &r0.y, &t);

	gfp2_square(&r0.t, &r0.z);

	gfp2_mul(&t, &E, &r->t);
	gfp2_add(&t, &t, &t);
	gfp2_neg(&b, &t);
	gfp2_mulscalar(&b, &b, q->x);
	
	gfp2_add(&a, &r->x, &E);
	gfp2_square(&a, &a);
	gfp2_sub(&a, &a, &A);
	gfp2_sub(&a, &a, &G);
	gfp2_add(&t, &B, &B);
	gfp2_add(&t, &t, &t);
	gfp2_sub(&a, &a, &t);

	gfp2_mul(&c, &r0.z, &r->t);
	gfp2_add(&c, &c, &c);
	gfp2_mulscalar(&c, &c, q->y);

	twistpoint_set(rout, &r0);
}

void mul_line(gfp12_t* ret, const gfp2_t* a, const gfp2_t* b, const gfp2_t* c) {
	gfp6_t a2, t2, t3;
	gfp2_t t;

	gfp2_setzero(&a2.x);
	gfp2_set(&a2.y, a);
	gfp2_set(&a2.z, b);
	gfp6_mul(&a2, &a2, &ret->x);
	gfp6_mulscalar(&t3, &ret->y, c);

	gfp2_add(&t, &b, &c);
	gfp2_setzero(&t2.x);
	gfp2_set(&t2.y, a);
	gfp2_set(&t2.z, &t);
	gfp6_add(&ret->x, &ret->x, &ret->y);

	gfp6_set(&ret->x, &t3);
	
	gfp6_mul(&ret->x, &ret->x, &t2);
	gfp6_sub(&ret->x, &ret->x, &a2);
	gfp6_sub(&ret->x, &ret->x, &ret->y);
	gfp6_multau(&a2, &a2);
	gfp6_add(&ret->y, &ret->y, &a2);
}

static const int8_t sixPlus2NAF[] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, -1, 0, 1, 0, 0, 0, 1, 0, -1, 0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1 };

#ifdef dim
#undef dim
#endif
#define dim(x) (sizeof(x) / sizeof((x)[0]))

static const int dSixPlus2NAF = dim(sixPlus2NAF);

void miller(gfp12_t* ret, const twistpoint_t* q, const curvepoint_t* p) {
	twistpoint_t aAffine, minusA, r, newR;
	curvepoint_t bAffine;
	gfp2_t r2, a, b, c;
	twistpoint_t q1, minusQ2;

	gfp12_setone(ret);

	twistpoint_set(&aAffine, q);
	twistpoint_make_affine(&aAffine);

	curvepoint_set(&bAffine, p);
	curvepoint_make_affine(&bAffine);

	twistpoint_neg(&minusA, &aAffine);
	twistpoint_set(&r, &aAffine);

	gfp2_square(&r2, &aAffine.y);

	for (int i = dSixPlus2NAF - 1; i > 0; i--) {
		line_func_double(&a, &b, &c, &newR, &r, &bAffine);
		if (i != dSixPlus2NAF - 1) {
			gfp12_square(ret, ret);
		}

		mul_line(ret, &a, &b, &c);
		twistpoint_set(&r, &newR);

		switch (sixPlus2NAF[i]) {
		case 1:
			line_func_add(&a, &b, &c, &newR, &r, &aAffine, &bAffine, &r2);
			break;
		case -1:
			line_func_add(&a, &b, &c, &newR, &r, &minusA, &bAffine, &r2);
			break;
		default:
			continue;
		}

		mul_line(ret, &a, &b, &c);
		twistpoint_set(&r, &newR);
	}

	gfp2_conjugate(&q1.x, &aAffine.x);
	gfp2_mul(&q1.x, &q1.x, &xiToPMinus1Over3);
	gfp2_conjugate(&q1.y, &aAffine.y);
	gfp2_mul(&q1.y, &q1.y, &xiToPMinus1Over2);
	gfp2_setone(&q1.z);
	gfp2_setone(&q1.t);

	gfp2_mulscalar(&minusQ2.x, &aAffine.x, &xiToPSquaredMinus1Over3);
	gfp2_set(&minusQ2.y, &aAffine.y);
	gfp2_setone(&minusQ2.z);
	gfp2_setone(&minusQ2.t);

	gfp2_square(&r2, &q1.y);
	line_func_add(&a, &b, &c, &newR, &r, &q1, &bAffine, &r2);
	mul_line(ret, &a, &b, &c);
	twistpoint_set(&r, &newR);

	gfp2_square(&r2, &minusQ2.y);
	line_func_add(&a, &b, &c, &newR, &r, &minusQ2, &bAffine, &r2);
	mul_line(ret, &a, &b, &c);
}

void final_exponentiation(gfp12_t* out, const gfp12_t* in) {
	gfp12_t t1, inv, t2, fp, fp2, fp3, fu, fu2, fu3, y3, fu2p, fu3p, y2, y0, y1, y5, y4, y6, t0;

	gfp6_neg(&t1.x, &in->x);
	gfp6_set(&t1.y, &in->y);

	gfp12_invert(&inv, in);
	gfp12_mul(&t1, &t1, &inv);

	gfp12_frobeniusp2(&t2, &t1);
	gfp12_mul(&t1, &t1, &t2);

	gfp12_frobenius(&fp, &t1);
	gfp12_frobeniusp2(&fp2, &t1);
	gfp12_frobenius(&fp3, &fp2);

	gfp12_exp(&fu, &t1, &u);
	gfp12_exp(&fu2, &fu, &u);
	gfp12_exp(&fu3, &fu2, &u);

	gfp12_frobenius(&y3, &fu);
	gfp12_frobenius(&fu2p, &fu2);
	gfp12_frobenius(&fu3p, &fu3);
	gfp12_frobeniusp2(&y2, &fu2);

	gfp12_mul(&y0, &fp, &fp2);
	gfp12_mul(&y0, &y0, &fp3);

	gfp12_conjugate(&y1, &t1);
	gfp12_conjugate(&y5, &fu2);
	gfp12_conjugate(&y3, &y3);
	gfp12_mul(&y4, &fu, &fu2p);
	gfp12_conjugate(&y4, &y4);

	gfp12_mul(&y6, &fu3, &fu3p);
	gfp12_conjugate(&y6, &y6);

	gfp12_square(&t0, &y6);
	gfp12_mul(&t0, &t0, &y4);
	gfp12_mul(&t0, &t0, &y5);
	gfp12_mul(&t1, &y3, &y5);
	gfp12_mul(&t1, &t1, &t0);
	gfp12_mul(&t0, &t0, &y2);
	gfp12_square(&t1, &t1);
	gfp12_mul(&t1, &t1, &t0);
	gfp12_square(&t1, &t1);
	gfp12_mul(&t0, &t1, &y1);
	gfp12_mul(&t1, &t1, &y0);
	gfp12_square(&t0, &t0);
	gfp12_mul(&t0, &t0, &t1);

	gfp12_set(out, &t0);
}

void optimal_ate(gfp12_t* c, const twistpoint_t* a, const curvepoint_t* b) {
	gfp12_t e;

	if (twistpoint_is_infinity(a) || curvepoint_is_infinity(b)) {
		gfp12_setone(c);
		return;
	}

	miller(&e, a, b);
	final_exponentiation(c, &e);	
}
