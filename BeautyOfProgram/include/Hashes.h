#ifndef BEAUTY_HASHES_H
#define BEAUTY_HASHES_H

#include <cstdint>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

struct PrimeHashFamily {
    PrimeHashFamily(uint32_t prime_) : prime{prime_} {}

    size_t operator()(const uint32_t x) const { return (x * prime) & 0xFFFFFFFF; }
    double normalized_hash(const int32_t x) const {
        return (this->operator()(x)) / static_cast<double>(std::numeric_limits<uint32_t>::max());
    }

    typedef size_t result_type;
    const uint32_t prime;
};

inline vector<PrimeHashFamily> generate_hash_family() {
    vector<PrimeHashFamily> ret;
    ret.emplace_back(10619863);
    ret.emplace_back(24036583);
    ret.emplace_back(25964951);
    ret.emplace_back(29986577);
    ret.emplace_back(30402457);
    ret.emplace_back(40960001);
    ret.emplace_back(45212177);
    ret.emplace_back(59969537);
    ret.emplace_back(60000049);
    ret.emplace_back(65610001);
    return ret;
}

#endif
