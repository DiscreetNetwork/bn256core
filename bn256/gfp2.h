#if !defined(GFP2_H)
#define GFP2_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

void gfp2_decode(gfp2_t* res, const gfp2_t* in);
void gfp2_set(gfp2_t* res, const gfp2_t* a);
void gfp2_setzero(gfp2_t* s);
void gfp2_setone(gfp2_t* s);
int gfp2_iszero(const gfp2_t* s);
int gfp2_isone(const gfp2_t* s);
void gfp2_conjugate(gfp2_t* c, const gfp2_t* a);
void gfp2_neg(gfp2_t* c, const gfp2_t* a);
void gfp2_add(gfp2_t* c, const gfp2_t* a, const gfp2_t* b);
void gfp2_sub(gfp2_t* c, const gfp2_t* a, const gfp2_t* b);
void gfp2_mul(gfp2_t* c, const gfp2_t* a, const gfp2_t* b);
void gfp2_mulscalar(gfp2_t* c, const gfp2_t* a, const gfp_t b);
void gfp2_mulxi(gfp2_t* c, const gfp2_t* a);
void gfp2_square(gfp2_t* c, const gfp2_t* a);
void gfp2_invert(gfp2_t* c, const gfp2_t* a);
int gfp2_equal(const gfp2_t* a, const gfp2_t* b);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // GFP2_H