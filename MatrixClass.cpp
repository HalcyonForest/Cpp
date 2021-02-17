#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Matrix {
private:
    pair<size_t, size_t> matrixSize;
    vector<vector<T>> m;

public:
    explicit Matrix(const vector<vector<T>> &inp_mat) {
        m = inp_mat;
        matrixSize = make_pair(m.size(), m[0].size());
    }

    pair<size_t, size_t> size() const {
        return matrixSize;
    }

    Matrix<T> transpose() {
        vector<vector<T>> matrixArray(this->size().second, vector<T>(this->size().first));
        Matrix<T> object(matrixArray);
        for (size_t i = 0; i < object.size().first; ++i) {
            for (size_t j = 0; j < object.size().second; ++j) {
                object.m[i][j] = this->m[j][i];
            }
        }
        *this = object;
        return *this;
    }

    Matrix<T> transposed() const {
        Matrix<T> object(this->m);
        object.transpose();
        return object;
    }

    class Iterator {
    private:
        vector<vector<T>> &data;
        size_t it;

    public:
        Iterator(vector<vector<T>> &data, size_t it) : data(data), it(it) {}

        Iterator &operator++() {
            ++it;
            return *this;
        }

        T operator*() {
            size_t cols = data[0].size();
            return data[it / cols][it % cols];
        }

        bool operator==(const Iterator &it1) {
            return it == it1.it;
        }

        bool operator!=(const Iterator &it1) {
            return it != it1.it;
        }
    };

    template<typename TL>
    friend ostream &operator<<(ostream &out, const Matrix<TL> &object);

    Matrix<T> operator+=(const Matrix<T> &object) {
        for (size_t i = 0; i < object.size().first; ++i) {
            for (size_t j = 0; j < object.size().second; ++j) {
                this->m[i][j] += object.m[i][j];
            }
        }
        return *this;
    }

    Matrix<T> operator*=(const Matrix<T> &object) {
        *this = *this * object;
        return *this;
    }

    Matrix<T> operator*=(const int &scalar) {
        *this = *this * scalar;
        return *this;
    }

    class ConstIterator {
    private:
        const vector<vector<T>> &data;
        size_t it;

    public:
        ConstIterator(const vector<vector<T>> &data, size_t it) : data(data), it(it) {}

        ConstIterator &operator++() {
            ++it;
            return *this;
        }

        T operator*() const {
            size_t cols = data[0].size();
            return data[it / cols][it % cols];
        }

        bool operator==(const ConstIterator &it1) {
            return it == it1.it;
        }

        bool operator!=(const ConstIterator &it1) {
            return it != it1.it;
        }
    };

    Iterator begin() {
        return Iterator(m, 0);
    }

    Iterator end() {
        return Iterator(m, matrixSize.first * matrixSize.second);
    }

    ConstIterator begin() const {
        return ConstIterator(m, 0);
    }

    ConstIterator end() const {
        return ConstIterator(m, matrixSize.first * matrixSize.second);
    }

    template<typename TL>
    friend Matrix<TL> operator+(const Matrix<TL> &object1, const Matrix<TL> &object2);

    template<typename TL>
    friend Matrix<TL> operator*(const Matrix<TL> &object1, const int &scalar);

    template<typename TL, typename TL1>
    friend Matrix<TL> operator*(const Matrix<TL> &object1, const Matrix<TL1> &object2);
};

template<typename T>
ostream &operator<<(ostream &out, const Matrix<T> &object) {
    for (size_t i = 0; i < object.size().first; ++i) {
        for (size_t j = 0; j < object.size().second; ++j) {
            out << object.m[i][j];
            if (j < object.m[i].size() - 1) {
                out << '\t';
            }
        }
        if (i < object.size().first - 1) {
            out << '\n';
        }
    }
    return out;
}

template<typename TL>
Matrix<TL> operator+(const Matrix<TL> &object1, const Matrix<TL> &object2)  {
    vector<vector<TL>> matrixArray(object1.size().first, vector<TL>(object1.size().second));
    Matrix<TL> object3(matrixArray);
    for (size_t i = 0; i < object1.size().first; ++i) {
        for (size_t j = 0; j < object1.size().second; ++j) {
            object3.m[i][j] = object1.m[i][j] + object2.m[i][j];
        }
    }
    return object3;
}

template<typename TL>
Matrix<TL> operator*(const Matrix<TL> &object1, const int &scalar) {
    Matrix<TL> object3 = object1;
    for (size_t i = 0; i < object1.size().first; ++i) {
        for (size_t j = 0; j < object1.size().second; ++j) {
            object3.m[i][j] *= scalar;
        }
    }
    return object3;
}

template<typename TL, typename TL1>
Matrix<TL> operator*(const Matrix<TL> &object1, const Matrix<TL1> &object2) {
    vector<vector<TL>> matrixArray(object1.size().first, vector<TL>(object2.size().second));
    Matrix<TL> object3(matrixArray);
    for (size_t i = 0; i < object3.size().first; ++i) {
        for (size_t j = 0; j < object3.size().second; ++j) {
            object3.m[i][j] = 0;
            for (size_t k = 0; k < object1.size().second; ++k) {
                object3.m[i][j] += object1.m[i][k] * object2.m[k][j];
            }
        }
    }
    return object3;
}

int main() {

    return 0;
}
