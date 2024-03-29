#pragma once

#if !defined(BN256_H)
#define BN256_H

extern "C" {
#include "types.h"
#include "gfp2.h"
#include "gfp.h"
#include "BigInt.h"
}

#include "export.h"

namespace bn256 {
	struct Scalar {
		struct bn n;
	};

	struct G1 {
		curvepoint_t p;

		bool operator==(const G1& g1) const {
			return gfp_equal(p.x, g1.p.x) && gfp_equal(p.y, g1.p.y) && gfp_equal(p.z, g1.p.z) && gfp_equal(p.t, g1.p.t);
		}
	};

	struct G1enc {
		unsigned char bytes[64];
	};

	struct G2 {
		twistpoint_t p;

		bool operator==(const G2& g2) const {
			return gfp2_equal(&p.x, &g2.p.x) && gfp2_equal(&p.y, &g2.p.y) && gfp2_equal(&p.z, &g2.p.z) && gfp2_equal(&p.t, &g2.p.t);
		}
	};

	struct G2enc {
		unsigned char bytes[129]; // one extra byte to represent infinity
	};

	struct GT {
		gfp12_t p;

		bool operator==(const GT& gt) const {
			return gfp2_equal(&p.x.x, &gt.p.x.x) && gfp2_equal(&p.x.y, &gt.p.x.y) && gfp2_equal(&p.x.z, &gt.p.x.z)
				&& gfp2_equal(&p.y.x, &gt.p.y.x) && gfp2_equal(&p.y.y, &gt.p.y.y) && gfp2_equal(&p.y.z, &gt.p.y.z);
		}
	};

	struct GTenc {
		unsigned char bytes[384];
	};
}

#ifdef __cplusplus
extern "C" {
#endif

EXPORT uint64_t CheckBMI2();
EXPORT void TestIfWorks(int* a, int b);
EXPORT int ScalarBitlen(bn256::Scalar& k);
EXPORT int ScalarBit(bn256::Scalar& k, int i);
EXPORT void GFpMul(gfp_t c, const gfp_t a, const gfp_t b);
EXPORT void NewGFp(gfp_t a, int64_t x);
EXPORT void GFpNeg(gfp_t c, const gfp_t a);
EXPORT void GFpExp(gfp_t c, const gfp_t a, const uint64_t bits[4]);
EXPORT void GFpInvert(gfp_t c, const gfp_t a);
EXPORT void GFpSqrt(gfp_t c, const gfp_t a);
EXPORT void GFpAdd(gfp_t c, const gfp_t a, const gfp_t b);
EXPORT void GFpSub(gfp_t c, const gfp_t a, const gfp_t b);

EXPORT void GFp2Add(gfp2_t* c, const gfp2_t* a, const gfp2_t* b);
EXPORT void GFp2Sub(gfp2_t* c, const gfp2_t* a, const gfp2_t* b);
EXPORT void GFp2Mul(gfp2_t* c, const gfp2_t* a, const gfp2_t* b);
EXPORT void GFp2Square(gfp2_t* c, const gfp2_t* a);
EXPORT void GFp2Invert(gfp2_t* c, const gfp2_t* a);
EXPORT void GFp2MulXi(gfp2_t* c, const gfp2_t* a);

EXPORT void GFp6Frobenius(gfp6_t* c, const gfp6_t* a);
EXPORT void GFp6FrobeniusP2(gfp6_t* c, const gfp6_t* a);
EXPORT void GFp6FrobeniusP4(gfp6_t* c, const gfp6_t* a);
EXPORT void GFp6Add(gfp6_t* c, const gfp6_t* a, const gfp6_t* b);
EXPORT void GFp6Sub(gfp6_t* c, const gfp6_t* a, const gfp6_t* b);
EXPORT void GFp6Mul(gfp6_t* c, const gfp6_t* a, const gfp6_t* b);
EXPORT void GFp6MulScalar(gfp6_t* c, const gfp6_t* a, const gfp2_t* b);
EXPORT void GFp6MulGFp(gfp6_t* c, const gfp6_t* a, const gfp_t b);
EXPORT void GFp6MulTau(gfp6_t* c, const gfp6_t* a);
EXPORT void GFp6Square(gfp6_t* c, const gfp6_t* a);
EXPORT void GFp6Invert(gfp6_t* c, const gfp6_t* a);

EXPORT void GFp12Conjugate(gfp12_t* c, const gfp12_t* a);
EXPORT void GFp12Neg(gfp12_t* c, const gfp12_t* a);
EXPORT void GFp12Frobenius(gfp12_t* c, const gfp12_t* a);
EXPORT void GFp12FrobeniusP2(gfp12_t* c, const gfp12_t* a);
EXPORT void GFp12FrobeniusP4(gfp12_t* c, const gfp12_t* a);
EXPORT void GFp12Add(gfp12_t* c, const gfp12_t* a, const gfp12_t* b);
EXPORT void GFp12Sub(gfp12_t* c, const gfp12_t* a, const gfp12_t* b);
EXPORT void GFp12Mul(gfp12_t* c, const gfp12_t* a, const gfp12_t* b);
EXPORT void GFp12MulScalar(gfp12_t* c, const gfp12_t* a, const gfp6_t* b);
EXPORT void GFp12Square(gfp12_t* c, const gfp12_t* a);
EXPORT void GFp12Invert(gfp12_t* c, const gfp12_t* a);
EXPORT void GFp12Exp(gfp12_t* c, const gfp12_t* a, const bn256::Scalar& power);

EXPORT void LineFuncAdd(gfp2_t* a, gfp2_t* b, gfp2_t* c, twistpoint_t* rout, const twistpoint_t* r, const twistpoint_t* p, const curvepoint_t* q, const gfp2_t* rr2);
EXPORT void LineFuncDouble(gfp2_t* a, gfp2_t* b, gfp2_t* c, twistpoint_t* rout, const twistpoint_t* r, const curvepoint_t* q);
EXPORT void MulLine(gfp12_t* ret, const gfp2_t* a, const gfp2_t* b, const gfp2_t* c);

EXPORT void RandomG1(bn256::G1& g1, bn256::Scalar& k);
EXPORT bn256::G1 RandomG1_1();
EXPORT void ScalarBaseMultG1(bn256::G1&gk, bn256::Scalar& k);
EXPORT bn256::G1 ScalarBaseMultG1_1(bn256::Scalar& k);
EXPORT void ScalarMultG1(bn256::G1& ak, bn256::G1& a, bn256::Scalar& k);
EXPORT bn256::G1 ScalarMultG1_1(bn256::G1& a, bn256::Scalar& k);
EXPORT void AddG1(bn256::G1& ab, bn256::G1& a, bn256::G1& b);
EXPORT bn256::G1 AddG1_1(bn256::G1& a, bn256::G1& b);
EXPORT void NegG1(bn256::G1& na, bn256::G1& a);
EXPORT bn256::G1 NegG1_1(bn256::G1& a);
EXPORT void MarshalG1(bn256::G1enc& res, bn256::G1& a);
EXPORT bn256::G1enc MarshalG1_1(bn256::G1& a);
EXPORT int UnmarshalG1(bn256::G1& a, bn256::G1enc& e);
EXPORT bn256::G1 UnmarshalG1_1(bn256::G1enc& e);

EXPORT void RandomG2(bn256::G2& g2, bn256::Scalar& k);
EXPORT bn256::G2 RandomG2_1();
EXPORT void ScalarBaseMultG2(bn256::G2& gk, bn256::Scalar& k);
EXPORT bn256::G2 ScalarBaseMultG2_1(bn256::Scalar& k);
EXPORT void ScalarMultG2(bn256::G2& ak, bn256::G2& a, bn256::Scalar& k);
EXPORT bn256::G2 ScalarMultG2_1(bn256::G2& a, bn256::Scalar& k);
EXPORT void AddG2(bn256::G2& ab, bn256::G2& a, bn256::G2& b);
EXPORT bn256::G2 AddG2_1(bn256::G2& a, bn256::G2& b);
EXPORT void NegG2(bn256::G2& na, bn256::G2& a);
EXPORT bn256::G2 NegG2_1(bn256::G2& a);
EXPORT void MarshalG2(bn256::G2enc& res, bn256::G2& a);
EXPORT bn256::G2enc MarshalG2_1(bn256::G2& a);
EXPORT int UnmarshalG2(bn256::G2& a, bn256::G2enc& e);
EXPORT bn256::G2 UnmarshalG2_1(bn256::G2enc& e);

EXPORT void RandomGT(bn256::GT& gt, bn256::Scalar& k);
EXPORT bn256::GT RandomGT_1();
EXPORT void ScalarBaseMultGT(bn256::GT& gk, bn256::Scalar& k);
EXPORT bn256::GT ScalarBaseMultGT_1(bn256::Scalar& k);
EXPORT void ScalarMultGT(bn256::GT& ak, bn256::GT& a, bn256::Scalar& k);
EXPORT bn256::GT ScalarMultGT_1(bn256::GT& a, bn256::Scalar& k);
EXPORT void AddGT(bn256::GT& ab, bn256::GT& a, bn256::GT& b);
EXPORT bn256::GT AddGT_1(bn256::GT& a, bn256::GT& b);
EXPORT void NegGT(bn256::GT& na, bn256::GT& a);
EXPORT bn256::GT NegGT_1(bn256::GT& a);
EXPORT void MarshalGT(bn256::GTenc& res, bn256::GT& a);
EXPORT bn256::GTenc MarshalGT_1(bn256::GT& a);
EXPORT void UnmarshalGT(bn256::GT& a, bn256::GTenc& e);
EXPORT bn256::GT UnmarshalGT_1(bn256::GTenc& e);

EXPORT void Pair(bn256::GT& gt, bn256::G1& p, bn256::G2& q);
EXPORT bn256::GT Pair_1(bn256::G1& p, bn256::G2& q);
EXPORT void Miller(bn256::GT& gt, bn256::G1& p, bn256::G2& q);
EXPORT bn256::GT Miller_1(bn256::G1& p, bn256::G2& q);
EXPORT void FinalizeGT(bn256::GT& gt);

EXPORT void HashG1(bn256::G1& res, const unsigned char* msg, unsigned long long msg_len, const unsigned char* dst, unsigned long long dst_len);

EXPORT int TestThrowExc();

#ifdef __cplusplus
}
#endif

#endif // BN256_H