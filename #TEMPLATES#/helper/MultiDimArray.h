#include <array>
#include <cstddef>

namespace details {
template <typename T, std::size_t Dim, std::size_t... Dims>
struct multi_dim_array {
    using type = std::array<typename multi_dim_array<T, Dims...>::type, Dim>;
};

template <typename T, std::size_t Dim>
struct multi_dim_array<T, Dim> {
    using type = std::array<T, Dim>;
};
} // namespace details

template <typename T, std::size_t... Dims>
using MultiDimArray = typename details::multi_dim_array<T, Dims...>::type;

// examples:
// static constexpr MultiDimArray<int, 4, 2> kDirections{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
