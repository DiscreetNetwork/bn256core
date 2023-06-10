#if !defined(CONSTANTS_H)
#define CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"
#include "BigInt.h"

extern const gfp2_t xiToPMinus1Over6;
extern const gfp2_t xiToPMinus1Over3;
extern const gfp2_t xiToPMinus1Over2;
extern const gfp_t xiToPSquaredMinus1Over3;
extern const gfp_t xiTo2PSquaredMinus2Over3;
extern const gfp_t xiToPSquaredMinus1Over6;
extern const gfp2_t xiTo2PMinus2Over3;
extern const gfp_t p2;
extern const gfp_t np;
extern const gfp_t rN1;
extern const gfp_t r2;
extern const gfp_t r3;
extern const gfp_t pPlus1Over4;
extern const gfp_t pMinus2;
extern const gfp_t pMinus1Over2;
extern const gfp_t s;
extern const gfp_t sMinus1Over2;
extern const gfp_t one;

extern const gfp12_t gfp12gen;
extern const curvepoint_t g1gen;
extern const gfp_t curveg1b;
extern const twistpoint_t g2gen;
extern const gfp2_t curveg2b;

extern const struct bn u;
extern const struct bn p;
extern const struct bn order;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CONSTANTS_H