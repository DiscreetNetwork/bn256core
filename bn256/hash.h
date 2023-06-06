#if !defined(HASH_H)
#define HASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

void map_to_curve(curvepoint_t* o, const gfp_t t);
void hash_g1(curvepoint_t* g1, const unsigned char* msg, unsigned long long msg_len, const unsigned char* dst, unsigned long long dst_len);

#ifdef __cplusplus
}
#endif

#endif // HASH_H
