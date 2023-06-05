#if !defined(PAIRING_H)
#define PAIRING_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

void line_func_add(gfp2_t* a, gfp2_t* b, gfp2_t* c, twistpoint_t* rout, const twistpoint_t* r, const twistpoint_t* p, const curvepoint_t* q, const gfp2_t* r2);
void line_func_double(gfp2_t* a, gfp2_t* b, gfp2_t* c, twistpoint_t* rout, const twistpoint_t* r, const curvepoint_t* q);
void mul_line(gfp12_t* ret, const gfp2_t* a, const gfp2_t* b, const gfp2_t* c);
void miller(gfp12_t* ret, const twistpoint_t* q, const curvepoint_t* p);
void final_exponentiation(gfp12_t* out, const gfp12_t* in);
void optimal_ate(gfp12_t* c, const twistpoint_t* a, const curvepoint_t* b);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // PAIRING_H