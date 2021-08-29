// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <type_traits>


template <class T, std::enable_if_t<std::is_integral<T>::value, T> = 0>
void print(T data) {
    std::cout << data % 7 << std::endl;
}

template <class T, std::enable_if_t<std::is_floating_point<T>::value, T>* = nullptr>
void print(T data) {
    std::cout << data - (long long)data << std::endl;
}

template <class T, std::enable_if_t<std::is_pointer<T>::value, T>* = nullptr>
void print(T data) {
    std::cout << data << std::endl;
}

template <class T, std::enable_if_t<std::is_class<T>::value, T>* = nullptr>
void print(T data) {
    std::cout << sizeof(data) << std::endl;
}

template <class T>
struct is_anything_else {
    static const bool value = !std::is_integral<T>::value &&
        !std::is_floating_point<T>::value &&
        !std::is_unsigned<T>::value &&
        !std::is_pointer<T>::value &&
        !std::is_class<T>::value;
};
//
template <class T, std::enable_if_t<is_anything_else<T>::value, T>* = nullptr>
void print(T data) {
    std::cout << "ANything else " << std::endl;
}


template <class T, class ...Types>
void print(T first, Types... args) {
    print(std::forward<T>(first));

    if (sizeof...(args)) {
        print(std::forward<Types>(args)...);
    }
}



struct point
{
    int x;
    int y;
};

class A {
    int a = 0;
};


int main() {
    int a = 9;
    A temp;
    struct point p { 2, 6 };

    print(1);
    print(0.7);
    print(4, 2.4);
    print(4, 2.4, &a, 9.8);
    print(4, 2.4, &a, p, temp, 9.8);
    print(-1, 0.5, "world", std::make_shared<double>(7.9));

    return 0;
}
