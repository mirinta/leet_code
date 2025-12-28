#include <array>

template<size_t M, size_t N, std::enable_if_t<(M > 0 && N > 0), bool> = true>
class Mat {
public:
    explicit Mat() = default;
    virtual ~Mat() = default;

    long long& operator()(size_t i, size_t j)
    {
        return const_cast<long long&>(const_cast<const Mat*>(this)->operator()(i, j));
    }
    const long long& operator()(size_t i, size_t j) const
    {
        return data[i][j];
    }

    /**
     * @return Mat<M, D> = (*this) * Mat<N, D>
     */
    template<size_t D>
    Mat<M, D> operator*(const Mat<N, D>& mat) const
    {
        Mat<M, D> result;
        for (size_t i = 0; i < M; ++i) {
            for (size_t k = 0; k < N; ++k) {
                if ((*this)(i, k) == 0)
                    continue;

                for (size_t j = 0; j < D; ++j) {
                    if (mat(k, j) == 0)
                        continue;

                    result(i, j) = (result(i, j) + (*this)(i, k) * mat(k, j) % kMod) % kMod;
                }
            }
        }
        return result;
    }

private:
    static constexpr long long kMod = 1e9 + 7;
    std::array<std::array<long long, N>, M> data{};
};

template<size_t M>
class Identity : public Mat<M, M> {
public:
    explicit Identity()
    {
        for (size_t i = 0; i < M; ++i) {
            (*this)(i, i) = 1;
        }
    }
};

/**
 * @return Mat<M, M> = mat ^ n
 */
template<size_t M>
Mat<M, M> fastPow(const Mat<M, M>& mat, long long n)
{
    Mat<M, M> result = Identity<M>();
    Mat<M, M> base = mat;
    while (n > 0) {
        if (n & 1) {
            result = result * base;
        }
        base = base * base;
        n >>= 1;
    }
    return result;
}
