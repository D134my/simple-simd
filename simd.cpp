
// don't forget to add -march=native if you're using clang

#include <immintrin.h>
#include <iostream>

struct Vec8u {
  union {
    __m256 reg;
    std::uint64_t entry[8];
  };

  Vec8u(std::uint64_t x) { reg = _mm256_set1_epi64x(x); };
  Vec8u(__m256i x) { reg = x; };
  Vec8u(std::uint64_t x0, std::uint64_t x1, std::uint64_t x2, std::uint64_t x3,
        std::uint64_t x4, std::uint64_t x5, std::uint64_t x6,
        std::uint64_t x7) {
    reg = _mm256_set_epi32(x0, x1, x2, x3, x4, x5, x6, x7);
  };
  // implicit conversion to register
  operator __m256i() { return reg; }

  friend std::ostream &operator<<(std::ostream &stream, const Vec8u &v) {
    for (auto &e : v.entry)
      stream << e << " ";
    return stream;
  }
};

inline Vec8u operator+(const Vec8u &a, const Vec8u &b) {
  return _mm256_add_epi64(a.reg, b.reg);
}

inline Vec8u operator-(const Vec8u &a, const Vec8u &b) {
  return _mm256_sub_epi64(a.reg, b.reg);
}
inline Vec8u operator*(const Vec8u &a, const Vec8u &b) {
  return _mm256_mullo_epi64(a.reg, b.reg);
}

int main() {

  Vec8u v1(std::uint64_t(4));
  Vec8u v2(std::uint64_t(10));
  auto result = v1 + v2;
  std::cout << "result of v1 + v2 : " << result << std::endl;

  return 0;
}
