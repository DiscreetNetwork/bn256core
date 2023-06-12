#if !defined(GFP_GENERIC_H)
#define GFP_GENERIC_H

// nongeneric check
#if defined(__GNUC__)
#if defined(__x86_64__)
#define NONGENERIC
#endif
#elif defined(_MSC_VER)
#if defined(_WIN64)
#define NONGENERIC
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

uint64_t hasbmi2();
extern uint64_t hasBMI2;

#if defined(NONGENERIC)

void __cpuidex(int res[4], int arg1, int arg2);
void gfpneg(gfp_t c, const gfp_t a);
void gfpadd(gfp_t c, const gfp_t a, const gfp_t b);
void gfpsub(gfp_t c, const gfp_t a, const gfp_t b);
void gfpfastmul(gfp_t c, const gfp_t a, const gfp_t b);

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