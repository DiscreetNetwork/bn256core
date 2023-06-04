#include <stdint.h>

#include "types.h"
#include "gfp_generic.h"
#include "constants.h"

void gfp_carry(gfp_t a, const uint64_t head) {
	gfp_t b;
	uint64_t carry = 0;
	uint64_t ncarry;
	uint64_t ai;
	uint64_t bi;

	// 0
	ai = a[0];
	bi = ai - p2[0] - carry;
	b[0] = bi;
	carry = (p2[0] & (~ai) | (p2[0] | (~ai)) & bi) >> 63;

	// 1
	ai = a[1];
	bi = ai - p2[1] - carry;
	b[1] = bi;
	carry = (p2[1] & (~ai) | (p2[1] | (~ai)) & bi) >> 63;

	// 2
	ai = a[2];
	bi = ai - p2[2] - carry;
	b[2] = bi;
	carry = (p2[2] & (~ai) | (p2[2] | (~ai)) & bi) >> 63;

	// 3
	ai = a[3];
	bi = ai - p2[3] - carry;
	b[3] = bi;
	carry = (p2[3] & (~ai) | (p2[3] | (~ai)) & bi) >> 63;

	carry = carry & (~head);
	carry = -carry;
	ncarry = ~ carry;

	a[0] = (a[0] & carry) | (b[0] & ncarry);
	a[1] = (a[1] & carry) | (b[1] & ncarry);
	a[2] = (a[2] & carry) | (b[2] & ncarry);
	a[3] = (a[3] & carry) | (b[3] & ncarry);
}

void gfp_neg(gfp_t c, const gfp_t a) {
	uint64_t carry = 0;
	uint64_t ai;
	uint64_t ci;

	// 0
	ai = a[0];
	ci = p2[0] - ai - carry;
	c[0] = ci;
	carry = (p2[0] & (~ai) | (p2[0] | (~ai)) & ci) >> 63;

	// 1
	ai = a[1];
	ci = p2[1] - ai - carry;
	c[1] = ci;
	carry = (p2[1] & (~ai) | (p2[1] | (~ai)) & ci) >> 63;

	// 2
	ai = a[2];
	ci = p2[2] - ai - carry;
	c[2] = ci;
	carry = (p2[2] & (~ai) | (p2[2] | (~ai)) & ci) >> 63;

	// 3
	ai = a[3];
	ci = p2[3] - ai - carry;
	c[3] = ci;
	carry = (p2[3] & (~ai) | (p2[3] | (~ai)) & ci) >> 63;

	gfp_carry(c, 0);
}

void gfp_add(gfp_t c, const gfp_t a, const gfp_t b) {
	uint64_t carry = 0;
	uint64_t ai;
	uint64_t bi;
	uint64_t ci;

	// 0
	ai = a[0];
	bi = b[0];
	ci = ai + bi + carry;
	c[0] = ci;
	carry = ((ai & bi) | (ai | bi) &  (~ci)) >> 63;

	// 1
	ai = a[1];
	bi = b[1];
	ci = ai + bi + carry;
	c[1] = ci;
	carry = ((ai & bi) | (ai | bi) & (~ci)) >> 63;

	// 2
	ai = a[2];
	bi = b[2];
	ci = ai + bi + carry;
	c[2] = ci;
	carry = ((ai & bi) | (ai | bi) & (~ci)) >> 63;

	// 3
	ai = a[3];
	bi = b[3];
	ci = ai + bi + carry;
	c[3] = ci;
	carry = ((ai & bi) | (ai | bi) & (~ci)) >> 63;

	gfp_carry(c, carry);
}

void gfp_sub(gfp_t c, const gfp_t a, const gfp_t b) {
	gfp_t t;
	uint64_t carry = 0;
	uint64_t bi;
	uint64_t ci;
	uint64_t ai;
	uint64_t ti;

	// 0
	bi = b[0];
	ti = p2[0] - bi - carry;
	t[0] = ti;
	carry = (bi & (~p2[0]) | (bi | (~p2[0])) & ti) >> 63;

	// 1
	bi = b[1];
	ti = p2[1] - bi - carry;
	t[1] = ti;
	carry = (bi & (~p2[1]) | (bi | (~p2[1])) & ti) >> 63;

	// 2
	bi = b[2];
	ti = p2[2] - bi - carry;
	t[2] = ti;
	carry = (bi & (~p2[2]) | (bi | (~p2[2])) & ti) >> 63;

	// 3
	bi = b[3];
	ti = p2[3] - bi - carry;
	t[3] = ti;
	carry = (bi & (~p2[3]) | (bi | (~p2[3])) & ti) >> 63;

	carry = 0;

	// 0
	ti = t[0];
	ai = a[0];
	ci = ai + ti + carry;
	c[0] = ci;
	carry = (ai & ti | (ai | ti) & (~ci)) >> 63;

	// 1
	ti = t[1];
	ai = a[1];
	ci = ai + ti + carry;
	c[1] = ci;
	carry = (ai & ti | (ai | ti) & (~ci)) >> 63;

	// 2
	ti = t[2];
	ai = a[2];
	ci = ai + ti + carry;
	c[2] = ci;
	carry = (ai & ti | (ai | ti) & (~ci)) >> 63;

	// 3
	ti = t[3];
	ai = a[3];
	ci = ai + ti + carry;
	c[3] = ci;
	carry = (ai & ti | (ai | ti) & (~ci)) >> 63;

	gfp_carry(c, carry);
}

void _mul(uint64_t res[8], const gfp_t a, const gfp_t b) {
	static const uint64_t mask16 = 0x0000ffff;
	static const uint64_t mask32 = 0xffffffff;

	static uint64_t buf[32] = { 0 };
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
		for (int j = 0; j < 8; j++) {
			block = 4 * j;
			xi = buf[block];
			yi = (buf[block + i] << shift) + head;
			zi = xi + yi + carry;
			carry = (xi & yi | (xi | yi) & (~zi)) >> 63;
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

	static uint64_t buf[18] = { 0 };
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

		for (int j = 0; j < 4; j++) {
			block = 4 * j;
			xi = buf[block];
			yi = (buf[block + i] << shift) + head;
			zi = xi + yi + carry;
			buf[block] = zi;
			carry = (xi & yi | (xi | yi) & (~zi)) >> 63;
			head = buf[block + i] >> (64 - shift);
		}
	}

	for (int i = 0; i < 4; i++) {
		res[i] = buf[4 * i];
	}
}

void gfp_mul(gfp_t c, const gfp_t a, const gfp_t b) {
	uint64_t T[8];
	uint64_t m[4];
	uint64_t t[8];
	uint64_t carry = 0;
	uint64_t Ti, ti, zi;
	
	_mul(T, a, b);
	_half_mul(m, (&T[0]), np);
	_mul(t, m, p2);

	for (int i = 0; i < 8; i++) {
		ti = t[i];
		Ti = T[i];
		zi = Ti + ti + carry;
		T[i] = zi;
		carry = (Ti & ti | (Ti | ti) & (~zi)) >> 63;
	}

	for (int i = 0; i < 4; i++) {
		c[i] = T[4 + i];
	}

	gfp_carry(c, carry);
}