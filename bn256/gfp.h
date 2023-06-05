#pragma once

#include "types.h"

void mont_encode(gfp_t c, const gfp_t a);
void mont_decode(gfp_t c, const gfp_t a);
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
int legendre(const gfp_t e);