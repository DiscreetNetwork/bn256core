#if !defined(GFP12_H)
#define GFP12_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

void gfp12_set(gfp12_t* c, const gfp12_t* a);
void gfp12_setzero(gfp12_t* c);
void gfp12_setone(gfp12_t* c);
int gfp12_iszero(const gfp12_t* c);
int gfp12_isone(const gfp12_t* c);
void gfp12_conjugate(gfp12_t* c, const gfp12_t* a);
void gfp12_neg(gfp12_t* c, const gfp12_t* a);
void gfp12_frobenius(gfp12_t* c, const gfp12_t* a);
void gfp12_frobeniusp2(gfp12_t* c, const gfp12_t* a);
void gfp12_frobeniusp4(gfp12_t* c, const gfp12_t* a);
void gfp12_add(gfp12_t* c, const gfp12_t* a, const gfp12_t* b);
void gfp12_sub(gfp12_t* c, const gfp12_t* a, const gfp12_t* b);
void gfp12_mul(gfp12_t* c, const gfp12_t* a, const gfp12_t* b);
void gfp12_mulscalar(gfp12_t* c, const gfp12_t* a, const gfp6_t* b);
void gfp12_square(gfp12_t* c, const gfp12_t* a);
void gfp12_invert(gfp12_t* c, const gfp12_t* a);
void gfp12_exp(gfp12_t* c, const gfp12_t* a, const struct bn* power);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // GFP12_H