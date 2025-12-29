#include <tuple>

namespace std {
template <>
struct hash<tuple<int, int, int>> {
    size_t operator()(const tuple<int, int, int>& t) const
    {
        const auto& [a, b, c] = t;
        size_t seed = 0;
        seed ^= hash<int>{}(a) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash<int>{}(b) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash<int>{}(c) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};
} // namespace std
