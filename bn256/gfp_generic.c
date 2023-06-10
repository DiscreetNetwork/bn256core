#include <stdint.h>

#include "types.h"
#include "gfp_generic.h"
#include "constants.h"

#if !defined(NONGENERIC)
void gfp_carry(gfp_t a, const uint64_t head) {
	gfp_t b;
	uint64_t carry = 0;
	uint64_t ncarry;
	uint64_t ai;
	uint64_t bi;
	uint64_t pi;

	for (int i = 0; i < 4; i++) {
		ai = a[i];
		pi = p2[i];
		bi = ai - pi - carry;
		b[i] = bi;
		carry = ((pi & (~ai)) | ((pi | (~ai)) & bi)) >> 63;
	}

	carry = carry & (~head);
	carry = (uint64_t)(-(int64_t)carry);
	ncarry = (~carry);
	for (int i = 0; i < 4; i++) {
		a[i] = (a[i] & carry) | (b[i] & ncarry);
	}
}

void gfp_neg(gfp_t c, const gfp_t a) {
	uint64_t carry = 0;
	uint64_t ai;
	uint64_t ci;
	uint64_t pi;
	
	for (int i = 0; i < 4; i++) {
		ai = a[i];
		pi = p2[i];
		ci = pi - ai - carry;
		c[i] = ci;
		carry = ((ai & (~pi)) | ((ai | (~pi)) & ci)) >> 63;
	}

	gfp_carry(c, 0);
}

void gfp_add(gfp_t c, const gfp_t a, const gfp_t b) {
	uint64_t carry = 0;
	uint64_t ai;
	uint64_t bi;
	uint64_t ci;

	for (int i = 0; i < 4; i++) {
		ai = a[i];
		bi = b[i];
		ci = ai + bi + carry;
		c[i] = ci;
		carry = ((ai & bi) | ((ai | bi) & (~ci))) >> 63;
	}

	gfp_carry(c, carry);
}

void gfp_sub(gfp_t c, const gfp_t a, const gfp_t b) {
	gfp_t t;
	uint64_t carry = 0;
	uint64_t bi;
	uint64_t ci;
	uint64_t ai;
	uint64_t ti;
	uint64_t pi;

	for (int i = 0; i < 4; i++) {
		pi = p2[i];
		bi = b[i];
		ti = pi - bi - carry;
		t[i] = ti;
		carry = ((bi & (~pi)) | ((bi | (~pi)) & ti)) >> 63;
	}

	carry = 0;

	for (int i = 0; i < 4; i++) {
		ai = a[i];
		ti = t[i];
		ci = ai + ti + carry;
		c[i] = ci;
		carry = ((ai & ti) | ((ai | ti) & (~ci))) >> 63;
	}

	gfp_carry(c, carry);
}

void _mul(uint64_t res[8], const gfp_t a, const gfp_t b) {
	static const uint64_t mask16 = 0x0000ffff;
	static const uint64_t mask32 = 0xffffffff;

	uint64_t buf[32];

	for (int i = 0; i < 32; i++) buf[i] = 0;

	uint64_t a0, a1, a2, a3;
	uint64_t b0, b2;
	int off;
	int shift;
	int block;
	uint64_t head = 0;
	uint64_t carry = 0;
	uint64_t xi, yi, zi;

	for (int i = 0; i < 4; i++) {
		a0 = a[i] & mask16;
		a1 = (a[i] >> 16) & mask16;
		a2 = (a[i] >> 32) & mask16;
		a3 = a[i] >> 48;

		for (int j = 0; j < 4; j++) {
			b0 = b[j] & mask32;
			b2 = b[j] >> 32;

			off = 4 * (i + j);
			buf[off + 0] += a0 * b0;
			buf[off + 1] += a1 * b0;
			buf[off + 2] += a2 * b0 + a0 * b2;
			buf[off + 3] += a3 * b0 + a1 * b2;
			buf[off + 4] += a2 * b2;
			buf[off + 5] += a3 * b2;
		}
	}

	for (int i = 1; i < 4; i++) {
		shift = 16 * i;
		carry = 0;
		head = 0;
		for (int j = 0; j < 8; j++) {
			block = 4 * j;

			xi = buf[block];
			yi = (buf[block + i] << shift) + head;
			zi = xi + yi + carry;
			buf[block] = zi;
			carry = ((xi & yi) | ((xi | yi) & (~zi))) >> 63;
			head = buf[block + i] >> (64 - shift);
		}
	}

	for (int i = 0; i < 8; i++) {
		res[i] = buf[4 * i];
	}
}

void _half_mul(gfp_t res, const gfp_t a, const gfp_t b) {
	static const uint64_t mask16 = 0x0000ffff;
	static const uint64_t mask32 = 0xffffffff;

	uint64_t buf[18];

	for (int i = 0; i < 18; i++) buf[i] = 0;

	uint64_t a0, a1, a2, a3;
	uint64_t b0, b2;
	int off;
	int shift;
	int block;
	uint64_t head = 0;
	uint64_t carry = 0;
	uint64_t xi, yi, zi;

	for (int i = 0; i < 4; i++) {
		a0 = a[i] & mask16;
		a1 = (a[i] >> 16) & mask16;
		a2 = (a[i] >> 32) & mask16;
		a3 = a[i] >> 48;

		for (int j = 0; j < 4; j++) {
			if (i + j > 3) break;

			b0 = b[j] & mask32;
			b2 = b[j] >> 32;

			off = 4 * (i + j);
			buf[off + 0] += a0 * b0;
			buf[off + 1] += a1 * b0;
			buf[off + 2] += a2 * b0 + a0 * b2;
			buf[off + 3] += a3 * b0 + a1 * b2;
			buf[off + 4] += a2 * b2;
			buf[off + 5] += a3 * b2;
		}
	}

	for (int i = 1; i < 4; i++) {
		shift = 16 * i;
		carry = 0;
		head = 0;

		for (int j = 0; j < 4; j++) {
			block = 4 * j;

			xi = buf[block];
			yi = (buf[block + i] << shift) + head;
			zi = xi + yi + carry;
			buf[block] = zi;
			carry = ((xi & yi) | ((xi | yi) & (~zi))) >> 63;
			head = buf[block + i] >> (64 - shift);
		}
	}

	for (int i = 0; i < 4; i++) {
		res[i] = buf[4 * i];
	}
}

void gfp_mul(gfp_t c, const gfp_t a, const gfp_t b) {
	uint64_t T[8];
	gfp_t Tc;
	uint64_t m[4];
	uint64_t t[8];
	uint64_t carry = 0;
	uint64_t Ti, ti, zi;
	
	_mul(T, a, b);
	for (int i = 0; i < 4; i++) {
		Tc[i] = T[i];
	}
	_half_mul(m, Tc, np);
	_mul(t, m, p2);

	for (int i = 0; i < 8; i++) {
		ti = t[i];
		Ti = T[i];
		zi = Ti + ti + carry;
		T[i] = zi;
		carry = ((Ti & ti) | ((Ti | ti) & (~zi))) >> 63;
	}

	for (int i = 0; i < 4; i++) {
		c[i] = T[4 + i];
	}

	gfp_carry(c, carry);
}
#endif // NONGENERIC