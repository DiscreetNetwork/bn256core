#include "types.h"
#include "gfp.h"
#include "gfp_generic.h"
#include "constants.h"

void map_to_curve(curvepoint_t* o, const gfp_t t) {
	gfp_t one, w, a, t2, st, w0, tw, x1, y, x2, x3;
	int e;
	curvepoint_t cp;

	new_gfp(one, 1);
	new_gfp(x2, 0);

	gfp_mul(t2, t, t);
	gfp_add(a, curveg1b, t2);
	gfp_add(a, a, one);

	gfp_mul(st, s, t);

	gfp_mul(w0, st, a);
	gfp_invert(w0, w0);

	gfp_mul(w, st, st);
	gfp_mul(w, w, w0);

	e = gfp_sign0(t);
	gfp_set(cp.x, x2);
	gfp_set(cp.y, x2);
	gfp_set(cp.z, one);
	gfp_set(cp.t, one);

	gfp_mul(tw, t, w);
	gfp_sub(x1, sMinus1Over2, tw);

	gfp_set(y, x1);
	gfp_mul(y, x1, x1);
	gfp_mul(y, y, x1);
	gfp_add(y, y, curveg1b);

	if (legendre(y) == 1) {
		gfp_set(cp.x, x1);
		gfp_sqrt(y, y);
		if (e != gfp_sign0(y)) {
			gfp_neg(y, y);
		}
		gfp_set(cp.y, y);
		
		curvepoint_set(o, &cp);
		return;
	}

	new_gfp(x2, -1);
	gfp_sub(x2, x2, x1);

	gfp_set(y, x2);
	gfp_mul(y, x2, x2);
	gfp_mul(y, y, x2);
	gfp_add(y, y, curveg1b);
	if (legendre(y) == 1) {
		gfp_set(cp.x, x2);
		gfp_sqrt(y, y);
		if (e != gfp_sign0(y)) {
			gfp_neg(y, y);
		}
		gfp_set(cp.y, y);

		curvepoint_set(o, &cp);
		return;
	}

	gfp_mul(x3, a, a);
	gfp_mul(x3, x3, x3);
	gfp_mul(x3, x3, w0);
	gfp_mul(x3, x3, w0);
	gfp_add(x3, x3, one);

	gfp_set(y, x3);
	gfp_mul(y, x3, x3);
	gfp_mul(y, y, x3);
	gfp_add(y, y, curveg1b);

	gfp_set(cp.x, x3);
	gfp_sqrt(y, y);
	if (e != gfp_sign0(y)) {
		gfp_neg(y, y);
	}
	gfp_set(cp.y, y);

	curvepoint_set(o, &cp);
}

void hash_g1(curvepoint_t* g1, const unsigned char* msg, unsigned long long msg_len, const unsigned char* dst, unsigned long long dst_len) {
	gfp_t t;
	hash_to_base(t, msg, msg_len, dst, dst_len);
	map_to_curve(g1, t);
}