// RUN: %clang_cc1 -triple=x86_64-apple-darwin -fsyntax-only -verify %s

typedef long long __m128i __attribute__((__vector_size__(16)));
typedef float __m128 __attribute__((__vector_size__(16)));
typedef double __m128d __attribute__((__vector_size__(16)));

typedef long long __m256i __attribute__((__vector_size__(32)));
typedef float __m256 __attribute__((__vector_size__(32)));
typedef double __m256d __attribute__((__vector_size__(32)));

typedef long long __m512i __attribute__((__vector_size__(64)));
typedef float __m512 __attribute__((__vector_size__(64)));
typedef double __m512d __attribute__((__vector_size__(64)));

typedef unsigned char __mmask8;
typedef unsigned short __mmask16;
typedef unsigned int __mmask32;

void call_x86_32_builtins(void) {
  (void)__builtin_ia32_readeflags_u32();                             // expected-error{{this builtin is only available on 32-bit targets}}
  (void)__builtin_ia32_writeeflags_u32(4);                           // expected-error{{this builtin is only available on 32-bit targets}}
}

__m128 test__builtin_ia32_cmpps(__m128 __a, __m128 __b) {
  return __builtin_ia32_cmpps(__a, __b, 32); // expected-error {{argument value 32 is outside the valid range [0, 31]}}
}

__m128d test__builtin_ia32_cmppd(__m128d __a, __m128d __b) {
  return __builtin_ia32_cmppd(__a, __b, 32); // expected-error {{argument value 32 is outside the valid range [0, 31]}}
}

__m128 test__builtin_ia32_cmpss(__m128 __a, __m128 __b) {
  return __builtin_ia32_cmpss(__a, __b, 32); // expected-error {{argument value 32 is outside the valid range [0, 31]}}
}

__m128d test__builtin_ia32_cmpsd(__m128d __a, __m128d __b) {
  return __builtin_ia32_cmpsd(__a, __b, 32); // expected-error {{argument value 32 is outside the valid range [0, 31]}}
}

__mmask16 test__builtin_ia32_cmpps512_mask(__m512d __a, __m512d __b) {
  return __builtin_ia32_cmpps512_mask(__a, __b, 32, -1, 4); // expected-error {{argument value 32 is outside the valid range [0, 31]}}
}

__mmask8 test__builtin_ia32_cmppd512_mask(__m512d __a, __m512d __b) {
  return __builtin_ia32_cmppd512_mask(__a, __b, 32, -1, 4); // expected-error {{argument value 32 is outside the valid range [0, 31]}}
}

__m128i test__builtin_ia32_vpcomub(__m128i __a, __m128i __b) {
  return __builtin_ia32_vpcomub(__a, __b, 8); // expected-error {{argument value 8 is outside the valid range [0, 7]}}
}

__m128i test__builtin_ia32_vpcomuw(__m128i __a, __m128i __b) {
  return __builtin_ia32_vpcomuw(__a, __b, 8); // expected-error {{argument value 8 is outside the valid range [0, 7]}}
}

__m128i test__builtin_ia32_vpcomud(__m128i __a, __m128i __b) {
  return __builtin_ia32_vpcomud(__a, __b, 8); // expected-error {{argument value 8 is outside the valid range [0, 7]}}
}

__m128i test__builtin_ia32_vpcomuq(__m128i __a, __m128i __b) {
  return __builtin_ia32_vpcomuq(__a, __b, 8); // expected-error {{argument value 8 is outside the valid range [0, 7]}}
}

__m128i test__builtin_ia32_vpcomb(__m128i __a, __m128i __b) {
  return __builtin_ia32_vpcomub(__a, __b, 8); // expected-error {{argument value 8 is outside the valid range [0, 7]}}
}

__m128i test__builtin_ia32_vpcomw(__m128i __a, __m128i __b) {
  return __builtin_ia32_vpcomuw(__a, __b, 8); // expected-error {{argument value 8 is outside the valid range [0, 7]}}
}

__m128i test__builtin_ia32_vpcomd(__m128i __a, __m128i __b) {
  return __builtin_ia32_vpcomud(__a, __b, 8); // expected-error {{argument value 8 is outside the valid range [0, 7]}}
}

__m128i test__builtin_ia32_vpcomq(__m128i __a, __m128i __b) {
  return __builtin_ia32_vpcomuq(__a, __b, 8); // expected-error {{argument value 8 is outside the valid range [0, 7]}}
}

__mmask16 test__builtin_ia32_cmpps512_mask_rounding(__m512 __a, __m512 __b, __mmask16 __u) {
  return __builtin_ia32_cmpps512_mask(__a, __b, 0, __u, 0); // expected-error {{invalid rounding argument}}
}

__m128i test_mm_mask_i32gather_epi32(__m128i a, int const *b, __m128i c, __m128i mask) {
  return __builtin_ia32_gatherd_d(a, b, c, mask, 5); // expected-error {{scale argument must be 1, 2, 4, or 8}}
}

void _mm512_mask_prefetch_i32gather_ps(__m512i index, __mmask16 mask, int const *addr) {
  __builtin_ia32_gatherpfdps(mask, index, addr, 5, 1); // expected-error {{scale argument must be 1, 2, 4, or 8}}
}

void _mm512_mask_prefetch_i32gather_ps_2(__m512i index, __mmask16 mask, int const *addr) {
  __builtin_ia32_gatherpfdps(mask, index, addr, 1, 1); // expected-error {{argument value 1 is outside the valid range [2, 3]}}
}

__m512i test_mm512_shldi_epi64(__m512i __A, __m512i __B) {
  return __builtin_ia32_vpshldq512(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m512i test_mm512_shldi_epi32(__m512i __A, __m512i __B) {
  return __builtin_ia32_vpshldd512(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m512i test_mm512_shldi_epi16(__m512i __A, __m512i __B) {
  return __builtin_ia32_vpshldw512(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m512i test_mm512_shrdi_epi64(__m512i __A, __m512i __B) {
  return __builtin_ia32_vpshrdq512(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m512i test_mm512_shrdi_epi32(__m512i __A, __m512i __B) {
  return __builtin_ia32_vpshrdd512(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m512i test_mm512_shrdi_epi16(__m512i __A, __m512i __B) {
  return __builtin_ia32_vpshrdw512(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m256i test_mm256_shldi_epi64(__m256i __A, __m256i __B) {
  return __builtin_ia32_vpshldq256(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m128i test_mm128_shldi_epi64( __m128i __A, __m128i __B) {
  return __builtin_ia32_vpshldq128(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m256i test_mm256_shldi_epi32(__m256i __A, __m256i __B) {
  return __builtin_ia32_vpshldd256(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m128i test_mm128_shldi_epi32(__m128i __A, __m128i __B) {
  return __builtin_ia32_vpshldd128(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m256i test_mm256_shldi_epi16( __m256i __A, __m256i __B) {
  return __builtin_ia32_vpshldw256(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m128i test_mm128_shldi_epi16(__m128i __A, __m128i __B) {
  return __builtin_ia32_vpshldw128(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m256i test_mm256_shrdi_epi64(__m256i __A, __m256i __B) {
  return __builtin_ia32_vpshrdq256(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m128i test_mm128_shrdi_epi64(__m128i __A, __m128i __B) {
  return __builtin_ia32_vpshrdq128(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m256i test_mm256_shrdi_epi32(__m256i __A, __m256i __B) {
  return __builtin_ia32_vpshrdd256(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m128i test_mm128_shrdi_epi32(__m128i __A, __m128i __B) {
  return __builtin_ia32_vpshrdd128(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m256i test_mm256_shrdi_epi16(__m256i __A, __m256i __B) {
  return __builtin_ia32_vpshrdw256(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}

__m128i test_mm128_shrdi_epi16(__m128i __A, __m128i __B) {
  return __builtin_ia32_vpshrdw128(__A, __B, 1024); // expected-error {{argument value 1024 is outside the valid range [0, 255]}}
}
