#include <algorithm>
#include <iostream>

using namespace std;


template<class T>
class Unique_ptr {
private:
    T *ptr;
public:
    Unique_ptr(T *ptr = nullptr) : ptr(ptr) {}

    Unique_ptr(Unique_ptr<T> &&oldPtr) {
        this->ptr = move(oldPtr.ptr);
        oldPtr.ptr = nullptr;
    }

    Unique_ptr &operator=(Unique_ptr<T> &oldPtr) {
        if (this == &oldPtr)
            return *this;
        delete ptr;
        ptr = oldPtr.ptr;
        oldPtr.ptr = nullptr;
        return *this;
    }

    T &operator*() {
        return *this->ptr;
    }

    T *operator->() {
        return &this->ptr;
    }

    ~Unique_ptr() {
        delete ptr;
    }
};
