#if !defined(GFP_H)
#define GFP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

void mont_encode(gfp_t c, const gfp_t a);
void mont_decode(gfp_t c, const gfp_t a);
void gfp_marshal(void* res, const gfp_t a);
void gfp_unmarshal(gfp_t c, const void* a);
void new_gfp(gfp_t res, const int64_t x);
void hash_to_base(gfp_t res, const unsigned char* msg, const unsigned long long msg_len, const unsigned char* dst, const unsigned long long dst_len);
void gfp_set(gfp_t c, const gfp_t a);
void gfp_exp(gfp_t c, const gfp_t f, const uint64_t bits[4]);
void gfp_invert(gfp_t c, const gfp_t f);
void gfp_sqrt(gfp_t c, const gfp_t f);
void gfp_to_bytes(unsigned char* out, const gfp_t a);
void gfp_from_bytes(gfp_t c, const unsigned char* in);
int gfp_sign0(const gfp_t e);
int gfp_iszero(const gfp_t f);
int gfp_isone(const gfp_t f);
int gfp_equal(const gfp_t a, const gfp_t b);
int legendre(const gfp_t e);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // GFP_H