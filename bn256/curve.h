#if !defined(CURVE_H)
#define CURVE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void curvepoint_set(curvepoint_t* c, const curvepoint_t* a);
void curvepoint_zero(curvepoint_t* c);
int curvepoint_is_infinity(const curvepoint_t* c);
void curvepoint_set_infinity(curvepoint_t* c);
void curvepoint_make_affine(curvepoint_t* c);
int curvepoint_is_on_curve(const curvepoint_t* c);
void curvepoint_double(curvepoint_t* c, const curvepoint_t* a);
void curvepoint_add(curvepoint_t* c, const curvepoint_t* a, const curvepoint_t* b);
void curvepoint_mul(curvepoint_t* c, const curvepoint_t* a, const struct bn* scalar);
void curvepoint_neg(curvepoint_t* c, const curvepoint_t* a);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CURVE_H