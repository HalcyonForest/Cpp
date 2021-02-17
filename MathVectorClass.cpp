#include <iostream>
#include <vector>

template<typename T>
class MathVector {
private:
    std::vector<T> data;

public:
    explicit MathVector(size_t n) {
        data.resize(n);
    }

    template<typename Iter>
    MathVector(Iter first, Iter last) {
        while (first != last)
            data.push_back(*first++);
    }

    size_t Dimension() const {
        return data.size();
    }

    T &operator[](size_t i) {
        return data[i];
    }

    const T &operator[](size_t i) const {
        return data[i];
    }
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const MathVector<T> &v) {
    out << '(';
    for (size_t i = 0; i != v.Dimension(); ++i) {
        if (i > 0)
            out << ", ";
        out << v[i];
    }
    out << ')';
    return out;
}

template<typename T>
MathVector<T> &operator*=(MathVector<T> &v, const T &scalar) {
    for (size_t i = 0; i != v.Dimension(); ++i)
        v[i] *= scalar;
    return v;
}

template<typename T>
MathVector<T> operator*(const MathVector<T> &v, const T &scalar) {
    auto tmp(v);
    tmp *= scalar;
    return tmp;
}

template<typename T>
MathVector<T> operator*(const T &scalar, const MathVector<T> &v) {
    return v * scalar;
}

template<typename T>
MathVector<T> &operator+=(MathVector<T> &v1, const MathVector<T> &v2) {
    for (size_t i = 0; i < v1.Dimension(); i++) {
        v1[i] = v1[i] + v2[i];
    }
    return v1;
}

template<typename T>
MathVector<T> operator+(const MathVector<T> &v1, const MathVector<T> &v2) {
    auto v3(v1);
    v3 += v2;
    return v3;
}

int main() {
    std::vector<int> dt = {1, 2, 2, 1, 3, 5};
    std::vector<int> dt2 = {3, 0, 2, 5, 3, 1};
    auto a = MathVector<int>(dt.begin(), dt.end());
    auto b = MathVector<int>(dt2.begin(), dt2.end());

    std::cout << a;
    a *= 3;
    a += b;
    MathVector<int> c = a + b;
    std::cout << c;
    return 0;
}