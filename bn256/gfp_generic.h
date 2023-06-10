#if !defined(GFP_GENERIC_H)
#define GFP_GENERIC_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

#define NONGENERIC
#if defined(NONGENERIC)

void __cpuidex(int res[4], int arg1, int arg2);
void gfpneg(gfp_t c, const gfp_t a);
void gfpadd(gfp_t c, const gfp_t a, const gfp_t b);
void gfpsub(gfp_t c, const gfp_t a, const gfp_t b);
void gfpfastmul(gfp_t c, const gfp_t a, const gfp_t b);

int hasbmi2();
extern int hasBMI2;

#define gfp_neg gfpneg
#define gfp_add gfpadd
#define gfp_sub gfpsub
#define gfp_mul gfpfastmul

#else
void gfp_carry(gfp_t a, const uint64_t head);
void gfp_neg(gfp_t c, const gfp_t a);
void gfp_add(gfp_t c, const gfp_t a, const gfp_t b);
void gfp_sub(gfp_t c, const gfp_t a, const gfp_t b);
void _mul(uint64_t res[8], const gfp_t a, const gfp_t b);
void _half_mul(gfp_t res, const gfp_t a, const gfp_t b);
void gfp_mul(gfp_t c, const gfp_t a, const gfp_t b);
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // GFP_GENERIC_H