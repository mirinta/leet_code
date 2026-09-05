#include <array>
#include <type_traits>

namespace details {
template <typename T, std::size_t Dim, std::size_t... Dims>
struct multi_dim_array : public std::type_identity<std::array<typename multi_dim_array<T, Dims...>::type, Dim>> {
};

template <typename T, std::size_t Dim>
struct multi_dim_array<T, Dim> : public std::type_identity<std::array<T, Dim>> {
};
} // namespace details

template <typename T, std::size_t... Dims>
using MultiDimArray = typename details::multi_dim_array<T, Dims...>::type;
