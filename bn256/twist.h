#if !defined(TWIST_H)
#define TWIST_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

void twistpoint_set(twistpoint_t* c, const twistpoint_t* a);
void twistpoint_zero(twistpoint_t* c);
void twistpoint_make_affine(twistpoint_t* c);
void twistpoint_set_infinity(twistpoint_t* c);
int twistpoint_is_infinity(const twistpoint_t* c);
int twistpoint_is_on_curve(const twistpoint_t* c);
void twistpoint_double(twistpoint_t* c, const twistpoint_t* a);
void twistpoint_add(twistpoint_t* c, const twistpoint_t* a, const twistpoint_t* b);
void twistpoint_mul(twistpoint_t* c, const twistpoint_t* a, const struct bn* scalar);
void twistpoint_neg(twistpoint_t* c, const twistpoint_t* a);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TWIST_H