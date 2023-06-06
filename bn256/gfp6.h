#if !defined(GFP6_H)
#define GFP6_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

void gfp6_set(gfp6_t* c, const gfp6_t* a);
void gfp6_setzero(gfp6_t* c);
void gfp6_setone(gfp6_t* c);
int gfp6_iszero(const gfp6_t* c);
int gfp6_isone(const gfp6_t* c);
void gfp6_neg(gfp6_t* c, const gfp6_t* a);
void gfp6_frobenius(gfp6_t* c, const gfp6_t* a);
void gfp6_frobeniusp2(gfp6_t* c, const gfp6_t* a);
void gfp6_frobeniusp4(gfp6_t* c, const gfp6_t* a);
void gfp6_add(gfp6_t* c, const gfp6_t* a, const gfp6_t* b);
void gfp6_sub(gfp6_t* c, const gfp6_t* a, const gfp6_t* b);
void gfp6_mul(gfp6_t* c, const gfp6_t* a, const gfp6_t* b);
void gfp6_mulscalar(gfp6_t* c, const gfp6_t* a, const gfp2_t* b);
void gfp6_mulgfp(gfp6_t* c, const gfp6_t* a, const gfp_t b);
void gfp6_multau(gfp6_t* c, const gfp6_t* a);
void gfp6_square(gfp6_t* c, const gfp6_t* a);
void gfp6_invert(gfp6_t* c, const gfp6_t* a);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // GFP6_H