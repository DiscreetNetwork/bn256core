extern "C" {
#include "types.h"
#include "gfp2.h"
#include "gfp.h"
#include "gfp12.h"
#include "BigInt.h"
#include "random.h"
#include "constants.h"
#include "curve.h"
#include "twist.h"
#include "pairing.h"
#include "hash.h"
}

#include "export.h"
#include "bn256.h"
#include "exc.h"

static inline void random_scalar(struct bn* k) {
	struct bn tmp;
	bignum_init(&tmp);
	generate_randombytes(32, (void*)&tmp.array[0]);
	bignum_init(k);
	bignum_mod(&tmp, &order, k);
}

EXPORT void RandomG1(bn256::G1& g1, bn256::Scalar& k) {
	random_scalar(&k.n);
	curvepoint_zero(&g1.p);
	curvepoint_mul(&g1.p, &g1gen, &k.n);
}

EXPORT bn256::G1 RandomG1_1() {
	bn256::G1 g1;
	struct bn k;
	random_scalar(&k);
	curvepoint_zero(&g1.p);
	curvepoint_mul(&g1.p, &g1gen, &k);
	return g1;
}

EXPORT void ScalarBaseMultG1(bn256::G1& gk, bn256::Scalar& k) {
	curvepoint_zero(&gk.p);
	curvepoint_mul(&gk.p, &g1gen, &k.n);
}

EXPORT bn256::G1 ScalarBaseMultG1_1(bn256::Scalar& k) {
	bn256::G1 gk;
	curvepoint_zero(&gk.p);
	curvepoint_mul(&gk.p, &g1gen, &k.n);
	return gk;
}

EXPORT void ScalarMultG1(bn256::G1& ak, bn256::G1& a, bn256::Scalar& k) {
	curvepoint_zero(&ak.p);
	curvepoint_mul(&ak.p, &a.p, &k.n);
}

EXPORT bn256::G1 ScalarMultG1_1(bn256::G1& a, bn256::Scalar& k) {
	bn256::G1 ak;
	curvepoint_zero(&ak.p);
	curvepoint_mul(&ak.p, &a.p, &k.n);
	return ak;
}

EXPORT void AddG1(bn256::G1& ab, bn256::G1& a, bn256::G1& b) {
	curvepoint_zero(&ab.p);
	curvepoint_add(&ab.p, &a.p, &b.p);
}

EXPORT bn256::G1 AddG1_1(bn256::G1& a, bn256::G1& b) {
	bn256::G1 ab;
	curvepoint_zero(&ab.p);
	curvepoint_add(&ab.p, &a.p, &b.p);
	return ab;
}

EXPORT void NegG1(bn256::G1& na, bn256::G1& a) {
	curvepoint_zero(&na.p);
	curvepoint_neg(&na.p, &a.p);
}

EXPORT bn256::G1 NegG1_1(bn256::G1& a) {
	bn256::G1 na;
	curvepoint_zero(&na.p);
	curvepoint_neg(&na.p, &a.p);
	return na;
}

EXPORT void MarshalG1(bn256::G1enc& res, bn256::G1& a) {
	curvepoint_make_affine(&a.p);
	for (int i = 0; i < sizeof(res.bytes) / sizeof(res.bytes[0]); i++) {
		res.bytes[i] = 0;
	}
	if (curvepoint_is_infinity(&a.p)) {
		return;
	}

	gfp_t tmp;
	mont_decode(tmp, a.p.x);
	gfp_marshal(&res.bytes[0], tmp);
	mont_decode(tmp, a.p.y);
	gfp_marshal(&res.bytes[32], tmp);
}

EXPORT bn256::G1enc MarshalG1_1(bn256::G1& a) {
	bn256::G1enc res;
	curvepoint_make_affine(&a.p);
	for (int i = 0; i < sizeof(res.bytes) / sizeof(res.bytes[0]); i++) {
		res.bytes[i] = 0;
	}
	if (curvepoint_is_infinity(&a.p)) {
		return res;
	}

	gfp_t tmp;
	mont_decode(tmp, a.p.x);
	gfp_marshal(&res.bytes[0], tmp);
	mont_decode(tmp, a.p.y);
	gfp_marshal(&res.bytes[32], tmp);

	return res;
}

EXPORT void UnmarshalG1(bn256::G1& a, bn256::G1enc& e) {
	curvepoint_zero(&a.p);

	gfp_unmarshal(a.p.x, &e.bytes[0]);
	gfp_unmarshal(a.p.y, &e.bytes[32]);
	mont_encode(a.p.x, a.p.x);
	mont_encode(a.p.y, a.p.y);

	if (gfp_iszero(a.p.x) && gfp_iszero(a.p.y)) {
		curvepoint_set_infinity(&a.p);
	}
	else {
		new_gfp(a.p.z, 1);
		new_gfp(a.p.t, 1);

		if (!curvepoint_is_on_curve(&a.p)) {
			curvepoint_zero(&a.p);
			ThrowException("bn256: point is malformed or invalid");
		}
	}
}

EXPORT bn256::G1 UnmarshalG1_1(bn256::G1enc& e) {
	bn256::G1 a;
	UnmarshalG1(a, e);
	return a;
}

// G2

EXPORT void RandomG2(bn256::G2& g2, bn256::Scalar& k) {
	random_scalar(&k.n);
	twistpoint_zero(&g2.p);
	twistpoint_mul(&g2.p, &g2gen, &k.n);
}

EXPORT bn256::G2 RandomG2_1() {
	struct bn k;
	bn256::G2 g2;
	random_scalar(&k);
	twistpoint_zero(&g2.p);
	twistpoint_mul(&g2.p, &g2gen, &k);
	return g2;
}

EXPORT void ScalarBaseMultG2(bn256::G2& gk, bn256::Scalar& k) {
	twistpoint_zero(&gk.p);
	twistpoint_mul(&gk.p, &g2gen, &k.n);
}

EXPORT bn256::G2 ScalarBaseMultG2_1(bn256::Scalar& k) {
	bn256::G2 gk;
	twistpoint_zero(&gk.p);
	twistpoint_mul(&gk.p, &g2gen, &k.n);
	return gk;
}

EXPORT void ScalarMultG2(bn256::G2& ak, bn256::G2& a, bn256::Scalar& k) {
	twistpoint_zero(&ak.p);
	twistpoint_mul(&ak.p, &a.p, &k.n);
}

EXPORT bn256::G2 ScalarMultG2_1(bn256::G2& a, bn256::Scalar& k) {
	bn256::G2 ak;
	twistpoint_zero(&ak.p);
	twistpoint_mul(&ak.p, &a.p, &k.n);
	return ak;
}

EXPORT void AddG2(bn256::G2& ab, bn256::G2& a, bn256::G2& b) {
	twistpoint_zero(&ab.p);
	twistpoint_add(&ab.p, &a.p, &b.p);
}

EXPORT bn256::G2 AddG2_1(bn256::G2& a, bn256::G2& b) {
	bn256::G2 ab;
	twistpoint_zero(&ab.p);
	twistpoint_add(&ab.p, &a.p, &b.p);
	return ab;
}

EXPORT void NegG2(bn256::G2& na, bn256::G2& a) {
	twistpoint_zero(&na.p);
	twistpoint_neg(&na.p, &a.p);
}

EXPORT bn256::G2 NegG2_1(bn256::G2& a) {
	bn256::G2 na;
	twistpoint_zero(&na.p);
	twistpoint_neg(&na.p, &a.p);
	return na;
}

EXPORT void MarshalG2(bn256::G2enc& res, bn256::G2& a) {
	twistpoint_make_affine(&a.p);
	for (int i = 0; i < sizeof(res.bytes) / sizeof(res.bytes[0]); i++) {
		res.bytes[i] = 0;
	}
	if (twistpoint_is_infinity(&a.p)) {
		return;
	}

	res.bytes[0] = 1;

	gfp_t tmp;
	mont_decode(tmp, a.p.x.x);
	gfp_marshal(&res.bytes[1], tmp);
	mont_decode(tmp, a.p.x.y);
	gfp_marshal(&res.bytes[33], tmp);
	mont_decode(tmp, a.p.y.x);
	gfp_marshal(&res.bytes[65], tmp);
	mont_decode(tmp, a.p.y.y);
	gfp_marshal(&res.bytes[97], tmp);
}

EXPORT bn256::G2enc MarshalG2_1(bn256::G2& a) {
	bn256::G2enc res;
	MarshalG2(res, a);
	return res;
}

EXPORT void UnmarshalG2(bn256::G2& a, bn256::G2enc& e) {
	if (e.bytes[0] == 0) {
		twistpoint_set_infinity(&a.p);
		return;
	}

	if (e.bytes[0] != 1) {
		twistpoint_zero(&a.p);
		ThrowException("bn256: malformed or invalid encoded twistpoint (G2)");
	}

	gfp_unmarshal(a.p.x.x, &e.bytes[1]);
	gfp_unmarshal(a.p.x.y, &e.bytes[33]);
	gfp_unmarshal(a.p.y.x, &e.bytes[65]);
	gfp_unmarshal(a.p.y.y, &e.bytes[97]);
	mont_encode(a.p.x.x, a.p.x.x);
	mont_encode(a.p.x.y, a.p.x.y);
	mont_encode(a.p.y.x, a.p.y.x);
	mont_encode(a.p.y.y, a.p.y.y);

	if (gfp2_iszero(&a.p.x) && gfp2_iszero(&a.p.y)) {
		twistpoint_set_infinity(&a.p);
	}
	else {
		gfp2_setone(&a.p.z);
		gfp2_setone(&a.p.t);

		if (!twistpoint_is_on_curve(&a.p)) {
			twistpoint_zero(&a.p);
			ThrowException("bn256: malformed or invalid point");
		}
	}
}

EXPORT bn256::G2 UnmarshalG2_1(bn256::G2enc& e) {
	bn256::G2 a;
	UnmarshalG2(a, e);
	return a;
}

// GT

EXPORT void RandomGT(bn256::GT& gt, bn256::Scalar& k) {
	random_scalar(&k.n);
	gfp12_setzero(&gt.p);
	gfp12_exp(&gt.p, &gfp12gen, &k.n);
}

EXPORT bn256::GT RandomGT_1() {
	struct bn k;
	bn256::GT gt;
	random_scalar(&k);
	gfp12_setzero(&gt.p);
	gfp12_exp(&gt.p, &gfp12gen, &k);
	return gt;
}

EXPORT void ScalarBaseMultGT(bn256::GT& gk, bn256::Scalar& k) {
	gfp12_setzero(&gk.p);
	gfp12_exp(&gk.p, &gfp12gen, &k.n);
}

EXPORT bn256::GT ScalarBaseMultGT_1(bn256::Scalar& k) {
	bn256::GT gk;
	gfp12_setzero(&gk.p);
	gfp12_exp(&gk.p, &gfp12gen, &k.n);
	return gk;
}

EXPORT void ScalarMultGT(bn256::GT& ak, bn256::GT& a, bn256::Scalar& k) {
	gfp12_setzero(&ak.p);
	gfp12_exp(&ak.p, &a.p, &k.n);
}

EXPORT bn256::GT ScalarMultGT_1(bn256::GT& a, bn256::Scalar& k) {
	bn256::GT ak;
	gfp12_setzero(&ak.p);
	gfp12_exp(&ak.p, &a.p, &k.n);
	return ak;
}

EXPORT void AddGT(bn256::GT& ab, bn256::GT& a, bn256::GT& b) {
	gfp12_setzero(&ab.p);
	gfp12_mul(&ab.p, &a.p, &b.p);
}

EXPORT bn256::GT AddGT_1(bn256::GT& a, bn256::GT& b) {
	bn256::GT ab;
	gfp12_setzero(&ab.p);
	gfp12_mul(&ab.p, &a.p, &b.p);
	return ab;
}

EXPORT void NegGT(bn256::GT& na, bn256::GT& a) {
	gfp12_setzero(&na.p);
	gfp12_neg(&na.p, &a.p);
}

EXPORT bn256::GT NegG2_1(bn256::GT& a) {
	bn256::GT na;
	gfp12_setzero(&na.p);
	gfp12_neg(&na.p, &a.p);
	return na;
}

EXPORT void MarshalGT(bn256::GTenc& res, bn256::GT& a) {
	for (int i = 0; i < sizeof(res.bytes) / sizeof(res.bytes[0]); i++) {
		res.bytes[i] = 0;
	}
	gfp_t tmp;

	mont_decode(tmp, a.p.x.x.x);
	gfp_marshal(&res.bytes[32 * 0], tmp);
	mont_decode(tmp, a.p.x.x.y);
	gfp_marshal(&res.bytes[32 * 1], tmp);
	mont_decode(tmp, a.p.x.y.x);
	gfp_marshal(&res.bytes[32 * 2], tmp);
	mont_decode(tmp, a.p.x.y.y);
	gfp_marshal(&res.bytes[32 * 3], tmp);
	mont_decode(tmp, a.p.x.z.x);
	gfp_marshal(&res.bytes[32 * 4], tmp);
	mont_decode(tmp, a.p.x.z.y);
	gfp_marshal(&res.bytes[32 * 5], tmp);

	mont_decode(tmp, a.p.y.x.x);
	gfp_marshal(&res.bytes[32 * 6], tmp);
	mont_decode(tmp, a.p.y.x.y);
	gfp_marshal(&res.bytes[32 * 7], tmp);
	mont_decode(tmp, a.p.y.y.x);
	gfp_marshal(&res.bytes[32 * 8], tmp);
	mont_decode(tmp, a.p.y.y.y);
	gfp_marshal(&res.bytes[32 * 9], tmp);
	mont_decode(tmp, a.p.y.z.x);
	gfp_marshal(&res.bytes[32 * 10], tmp);
	mont_decode(tmp, a.p.y.z.y);
	gfp_marshal(&res.bytes[32 * 11], tmp);
}

EXPORT bn256::GTenc MarshalGT_1(bn256::GT& a) {
	bn256::GTenc res;
	MarshalGT(res, a);
	return res;
}

EXPORT void UnmarshalGT(bn256::GT& a, bn256::GTenc& e) {
	gfp12_setzero(&a.p);

	gfp_unmarshal(a.p.x.x.x, &e.bytes[32 * 0]);
	gfp_unmarshal(a.p.x.x.y, &e.bytes[32 * 1]);
	gfp_unmarshal(a.p.x.y.x, &e.bytes[32 * 2]);
	gfp_unmarshal(a.p.x.y.y, &e.bytes[32 * 3]);
	gfp_unmarshal(a.p.x.z.x, &e.bytes[32 * 4]);
	gfp_unmarshal(a.p.x.z.y, &e.bytes[32 * 5]);
	gfp_unmarshal(a.p.y.x.x, &e.bytes[32 * 6]);
	gfp_unmarshal(a.p.y.x.y, &e.bytes[32 * 7]);
	gfp_unmarshal(a.p.y.y.x, &e.bytes[32 * 8]);
	gfp_unmarshal(a.p.y.y.y, &e.bytes[32 * 9]);
	gfp_unmarshal(a.p.y.z.x, &e.bytes[32 * 10]);
	gfp_unmarshal(a.p.y.z.y, &e.bytes[32 * 11]);

	mont_encode(a.p.x.x.x, a.p.x.x.x);
	mont_encode(a.p.x.x.y, a.p.x.x.y);
	mont_encode(a.p.x.y.x, a.p.x.y.x);
	mont_encode(a.p.x.y.y, a.p.x.y.y);
	mont_encode(a.p.x.z.x, a.p.x.z.x);
	mont_encode(a.p.x.z.y, a.p.x.z.y);
	mont_encode(a.p.y.x.x, a.p.y.x.x);
	mont_encode(a.p.y.x.y, a.p.y.x.y);
	mont_encode(a.p.y.y.x, a.p.y.y.x);
	mont_encode(a.p.y.y.y, a.p.y.y.y);
	mont_encode(a.p.y.z.x, a.p.y.z.x);
	mont_encode(a.p.y.z.y, a.p.y.z.y);
}

EXPORT bn256::GT UnmarshalGT_1(bn256::GTenc& e) {
	bn256::GT a;
	UnmarshalGT(a, e);
	return a;
}

// Pairing

EXPORT void Pair(bn256::GT& gt, bn256::G1& p, bn256::G2& q) {
	gfp12_setzero(&gt.p);
	optimal_ate(&gt.p, &q.p, &p.p);
}

EXPORT bn256::GT Pair_1(bn256::G1& p, bn256::G2& q) {
	bn256::GT gt;
	gfp12_setzero(&gt.p);
	optimal_ate(&gt.p, &q.p, &p.p);
	return gt;
}

EXPORT void Miller(bn256::GT& gt, bn256::G1& p, bn256::G2& q) {
	gfp12_setzero(&gt.p);
	miller(&gt.p, &q.p, &p.p);
}

EXPORT bn256::GT Miller_1(bn256::G1& p, bn256::G2& q) {
	bn256::GT gt;
	gfp12_setzero(&gt.p);
	miller(&gt.p, &q.p, &p.p);
	return gt;
}

EXPORT void Finalize(bn256::GT& gt) {
	gfp12_t f;
	final_exponentiation(&f, &gt.p);
	gfp12_set(&gt.p, &f);
}

// misc

EXPORT void HashG1(bn256::G1& res, const unsigned char* msg, unsigned long long msg_len, const unsigned char* dst, unsigned long long dst_len) {
	hash_g1(&res.p, msg, msg_len, dst, dst_len);
}