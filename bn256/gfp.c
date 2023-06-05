#include "gfp_generic.h"
#include "constants.h"
#include "BigInt.h"
#include "hmacsha256.h"

void mont_encode(gfp_t c, const gfp_t a) {
	gfp_mul(c, a, r2);
}

void mont_decode(gfp_t c, const gfp_t a) {
	gfp_mul(c, a, one);
}

void new_gfp(gfp_t res, const int64_t x) {
	res[0] = 0;
	res[1] = 0;
	res[2] = 0;
	res[3] = 0;

	if (x >= 0) {
		res[0] = x;
	}
	else {
		res[0] = -x;
		gfp_neg(res, res);
	}

	mont_encode(res, res);
}

void hash_to_base(gfp_t res, const unsigned char* msg, unsigned long long msg_len, const unsigned char * dst, unsigned long long dst_len) {
	hmacsha256_ctx state;
	unsigned char t[64];
	uint32_t* t_p = (uint32_t*)t;
	struct bn x;
	struct bn xp;

	hmacsha256_init(&state, dst, dst_len);
	hmacsha256_update(&state, msg, msg_len);

	hmacsha256_final(&state, &t[0]);
	hmacsha256_final(&state, &t[32]);

	bignum_init(&x);
	for (int i = 0; i < 12; i++) {
		x.array[i] = t_p[i];
	}

	bignum_mod(&x, &p, &xp);
	gfp_from_bignum(res, &xp);

	mont_encode(res, res);

	return 0;
}

void gfp_set(gfp_t c, const gfp_t a) {
	c[0] = a[0];
	c[1] = a[1];
	c[2] = a[2];
	c[3] = a[3];
}

void gfp_exp(gfp_t c, const gfp_t f, const uint64_t bits[4]) {
	gfp_t sum;
	gfp_t power;

	gfp_set(sum, rN1);
	gfp_set(power, f);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 64; j++) {
			if ((bits[i] >> j) & 1 == 1) {
				gfp_mul(sum, sum, power);
			}
			gfp_mul(power, power, power);
		}
	}

	gfp_mul(sum, sum, r3);
	gfp_set(c, sum);
}

void gfp_invert(gfp_t c, const gfp_t f) {
	gfp_exp(c, f, pMinus2);
}

void gfp_sqrt(gfp_t c, const gfp_t f) {
	gfp_exp(c, f, pPlus1Over4);
}

void gfp_to_bytes(unsigned char* out, const gfp_t a) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			out[8 * i + j] = (unsigned char)(a[3 - i] >> (56 - 8 * j));
		}
	}
}

void gfp_from_bytes(gfp_t c, const unsigned char* in) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			c[3 - i] += (uint64_t)in[8 * i + j] << (56 - 8 * j);
		}
	}
}

int gfp_sign0(const gfp_t e) {
	gfp_t x;
	mont_decode(x, e);
	for (int i = 3; i >= 0; i--) {
		if (x[i] > pMinus1Over2[i]) {
			return 1;
		} 
		else if (x[i] < pMinus1Over2[i]) {
			return -1;
		}
	}

	return 1;
}

int gfp_iszero(const gfp_t f) {
	return f[0] == 0 && f[1] == 0 && f[2] == 0 && f[3] == 0;
}

int gfp_isone(const gfp_t f) {
	return f[0] == 1 && f[1] == 0 && f[2] == 0 && f[3] == 0;
}

int gfp_equal(const gfp_t a, const gfp_t b) {
	return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}

int legendre(const gfp_t e) {
	gfp_t f;
	
	gfp_exp(f, e, pMinus1Over2);

	mont_decode(f, f);

	if (!gfp_iszero(f)) {
		return 2 * (int)(f[0] & 1) - 1;
	}

	return 0;
}



