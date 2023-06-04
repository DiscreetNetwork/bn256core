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

const struct bn u = { {0xEC588301, 0x5A76AE9A, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
const struct bn p = { {0x5E089667, 0x185CAC6C, 0x20B5B59E, 0xEE5B88D1, 0x6184DC21, 0xAA6FECB8, 0x4AA387F9, 0x8FB501E3, 0, 0, 0, 0, 0, 0, 0, 0} };
const struct bn order = { {0x57AC7261, 0x1A2EF45B, 0xF82B3924, 0x2E8D8E12, 0x6184DC21, 0xAA6FECB8, 0x4AA387F9, 0x8FB501E3, 0, 0, 0, 0, 0, 0, 0, 0} };
