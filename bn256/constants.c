#include "types.h"
#include "BigInt.h"

const gfp2_t xiToPMinus1Over6 = { {0x25af52988477cdb7, 0x3d81a455ddced86a, 0x227d012e872c2431, 0x179198d3ea65d05}, {0x7407634dd9cca958, 0x36d5bd6c7afb8f26, 0xf4b1c32cebd880fa, 0x6aa7869306f455f} };

const gfp2_t xiToPMinus1Over3 = { {0x4f59e37c01832e57, 0xae6be39ac2bbbfe4, 0xe04ea1bb697512f8, 0x3097caa8fc40e10e}, {0xf8606916d3816f2c, 0x1e5c0d7926de927e, 0xbc45f3946d81185e, 0x80752a25aa738091} };

const gfp2_t xiToPMinus1Over2 = { {0x19da71333653ee20, 0x7eaaf34fc6ed6019, 0xc4ba3a29a60cdd1d, 0x75281311bcc9df79}, {0x18dbee03fb7708fa, 0x1e7601a602c843c7, 0x5dde0688cdb231cb, 0x86db5cf2c605a524} };

const gfp_t xiToPSquaredMinus1Over3 = { 0x12d3cef5e1ada57d, 0xe2eca1463753babb, 0xca41e40ddccf750, 0x551337060397e04c };

const gfp_t xiTo2PSquaredMinus2Over3 = { 0x3642364f386c1db8, 0xe825f92d2acd661f, 0xf2aba7e846c19d14, 0x5a0bcea3dc52b7a0 };

const gfp_t xiToPSquaredMinus1Over6 = { 0xe21a761d259c78af, 0x6358fa3f5e84f7e, 0xb7c444d01ac33f0d, 0x35a9333f6e50d058 };

const gfp2_t xiTo2PMinus2Over3 = { {0x51678e7469b3c52a, 0x4fb98f8b13319fc9, 0x29b2254db3f1df75, 0x1c044935a3d22fb2}, {0x4d2ea218872f3d2c, 0x2fcb27fc4abe7b69, 0xd31d972f0e88ced9, 0x53adc04a00a73b15} };

const gfp_t p2 = { 0x185cac6c5e089667, 0xee5b88d120b5b59e, 0xaa6fecb86184dc21, 0x8fb501e34aa387f9 };

const gfp_t np = { 0x2387f9007f17daa9, 0x734b3343ab8513c8, 0x2524282f48054c12, 0x38997ae661c3ef3c };

const gfp_t rN1 = { 0xcbb781e36236117d, 0xcc65f3bcec8c91b, 0x2eab68888ea1f515, 0x1fc5c0956f92f825 };

const gfp_t r2 = { 0x9c21c3ff7e444f56, 0x409ed151b2efb0c2, 0xc6dc37b80fb1651, 0x7c36e0e62c2380b7 };

const gfp_t r3 = { 0x2af2dfb9324a5bb8, 0x388f899054f538a4, 0xdf2ff66396b107a7, 0x24ebbbb3a2529292 };

const gfp_t pPlus1Over4 = { 0x86172b1b1782259a, 0x7b96e234482d6d67, 0x6a9bfb2e18613708, 0x23ed4078d2a8e1fe };

const gfp_t pMinus2 = { 0x185cac6c5e089665, 0xee5b88d120b5b59e, 0xaa6fecb86184dc21, 0x8fb501e34aa387f9 };

const gfp_t pMinus1Over2 = { 0x0c2e56362f044b33, 0xf72dc468905adacf, 0xd537f65c30c26e10, 0x47da80f1a551c3fc };

const gfp_t s = { 0x236e675956be783b, 0x053957e6f379ab64, 0xe60789a768f4a5c4, 0x04f8979dd8bad754 };

const gfp_t sMinus1Over2 = { 0x3642364f386c1db8, 0xe825f92d2acd661f, 0xf2aba7e846c19d14, 0x5a0bcea3dc52b7a0 };

const gfp_t one = { 1, 0, 0, 0 };

const gfp12_t gfp12gen = { 
	{
		{
			{0x62d608d6bb67a4fb, 0x9a66ec93f0c2032f, 0x5391628e924e1a34, 0x2162dbf7de801d0e}, /* x.x.x */
			{0x3e0c1a72bf08eb4f, 0x4972ec05990a5ecc, 0xf7b9a407ead8007e, 0x3ca04c613572ce49}  /* x.x.y */
		},
		{
			{0xace536a5607c910e, 0xda93774a941ddd40, 0x5de0e9853b7593ad, 0xe05bb926f513153}, /* x.y.x */
			{0x3f4c99f8abaf1a22, 0x66d5f6121f86dc33, 0x8e0a82f68a50abba, 0x819927d1eebd0695} /* x.y.y */
		},
		{
			{0x7cdef49c5477faa, 0x40eb71ffedaa199d, 0xbc896661f17c9b8f, 0x3144462983c38c02}, /* x.z.x */
			{0xcd09ee8dd8418013, 0xf8d050d05faa9b11, 0x589e90a555507ee1, 0x58e4ab25f9c49c15} /* x.z.y */
		}
	},
	{
		{
			{0x7e76809b142d020b, 0xd9949d1b2822e995, 0x3de93d974f84b076, 0x144523477028928d}, /* y.x.x */
			{0x79952799f9ef4b0, 0x4102c47aa3df01c6, 0xfa82a633c53da2e1, 0x54c3f0392f9f7e0e}   /* y.x.y */
		},
		{
			{0xd3432a335533272b, 0xa008fbbdc7d74f4a, 0x68e3c81eb7295ed9, 0x17fe34c21fdecef2}, /* y.y.x */
			{0xfb0bc4c0ef6df55f, 0x8bdc585b70bc2120, 0x17d498d2cb720def, 0x2a368248319b899c}  /* y.y.y */
		},
		{
			{0xf8487d81cb354c6c, 0x7421be69f1522caa, 0x6940c778b9fb2d54, 0x7da4b04e102bb621}, /* y.z.x */
			{0x97b91989993e7be4, 0x8526545356eab684, 0xb050073022eb1892, 0x658b432ad09939c0}  /* y.z.y */
		} 
	}
};

const curvepoint_t g1gen = {
		{0xe7a35393a1f76999, 0x11a4772edf4a4a61, 0x559013479e7b23de, 0x704afe1cb55c7806},
		{0x6172b1b17822599c, 0xb96e234482d6d678, 0xa9bfb2e186137087, 0x3ed4078d2a8e1fe6},
		{0xe7a35393a1f76999, 0x11a4772edf4a4a61, 0x559013479e7b23de, 0x704afe1cb55c7806},
		{0xe7a35393a1f76999, 0x11a4772edf4a4a61, 0x559013479e7b23de, 0x704afe1cb55c7806}
};

const gfp_t curveg1b = { 0x8630a1e229d50ffd, 0x583653ea5c7373e9, 0xabd060661867b356, 0x3176f68f8ace581f };

const twistpoint_t g2gen = {
	{
		{0x402c4ab7139e1404, 0xce1c368a183d85a4, 0xd67cf9a6cb8d3983, 0x3cf246bbc2a9fbe8},
		{0x88f9f11da7cdc184, 0x18293f95d69509d3, 0xb5ce0c55a735d5a1, 0x15134189bfd45a0}
	},
	{
		{0xbfac7d731e9e87a2, 0xa50bb8007962e441, 0xafe910a4e8270556, 0x5075c5429d69159a},
		{0xc2e07c1463ea9e56, 0xee4442052072ebd2, 0x561a519486036937, 0x5bd9394cc0d2cce}
	},
	{
		{0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000},
		{0xe7a35393a1f76999, 0x11a4772edf4a4a61, 0x559013479e7b23de, 0x704afe1cb55c7806}
	},
	{
		{0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000},
		{0xe7a35393a1f76999, 0x11a4772edf4a4a61, 0x559013479e7b23de, 0x704afe1cb55c7806}
	}
};

const gfp2_t curveg2b = {
	{0x75046774386b8d71, 0x5bd0854a46d36cf8, 0x664327a1d41c8414, 0x96c9abb932eeb2f},
	{0xb94f760fb4c5ee14, 0xdae9f8f24c3b6eb4, 0x77a675d2e52f4fe4, 0x736f31b09116c66b}
};

const struct bn u = { {0xEC588301, 0x5A76AE9A, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
const struct bn p = { {0x5E089667, 0x185CAC6C, 0x20B5B59E, 0xEE5B88D1, 0x6184DC21, 0xAA6FECB8, 0x4AA387F9, 0x8FB501E3, 0, 0, 0, 0, 0, 0, 0, 0} };
const struct bn order = { {0x57AC7261, 0x1A2EF45B, 0xF82B3924, 0x2E8D8E12, 0x6184DC21, 0xAA6FECB8, 0x4AA387F9, 0x8FB501E3, 0, 0, 0, 0, 0, 0, 0, 0} };
