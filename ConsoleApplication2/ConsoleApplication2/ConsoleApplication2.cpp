// ConsoleAplenplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <algorithm>

#include <functional>
#include <array>
#include <string_view>


#define ALLOCATE_BYTES    10

typedef unsigned int index_t;

class SString {
public:
    SString() {
        this->str = nullptr;
        this->len = 0;
        this->cap = 0;
    }

    SString(const char* in) : SString() {
        while (in[this->len] != '\0') {
            this->len++;
        }
        if (this->len > 0) {
            reallocStorage(this->len + 1);

            copyString(this->str, in, this->len + 1);
        }
    }

    SString(const SString& in) : SString() {
        this->len = in.len;
        if (this->len > 0) {
            reallocStorage(this->len + 1);

            copyString(this->str, in.str, this->len + 1);
        }
    }

    SString(SString&& in) : SString() {
        this->len = in.len;
        if (this->len > 0) {
            reallocStorage(this->len + 1);

            copyString(this->str, in.str, this->len + 1);
        }

        in.str = nullptr;
    }

    ~SString() {
        std::cout << "memory free" << std::endl;
        delete[] this->str;
    }

    // return curent symbol from string
    char& operator[] (index_t ind) {
        return this->str[ind];
    }

    // return current symbol from string with access of range
    char& at(index_t ind);

    void append(const char* in);

    void append(const char* in, size_t num);

    void append(const char* in, index_t start, index_t finish);

    size_t size() {
        return this->len;
    }

    size_t capacity() {
        return this->cap;
    }

    SString& operator= (const SString& in) {
        this->len = in.len;
        this->cap = 0;

        reallocStorage(this->len + 1);

        copyString(this->str, in.str, this->len + 1);

        return *this;
    }

    SString operator+ (const SString& s2) {
        SString res("");

        res.append(this->str);
        res.append(s2.str);

        return res;
    }

    SString& operator+= (const SString& s2) {
        this->append(s2.str);

        return *this;
    }

    friend std::ostream& operator<< (std::ostream& out, const SString& s) {
        out << s.str;
        return out;
    }

private:
    const size_t len_alloc = ALLOCATE_BYTES;

    char* str;
    size_t len; // current length string 
    size_t cap; // allocated memory 

    void reallocStorage(size_t n = ALLOCATE_BYTES);
    bool isFreeStorage();
    void copyString(char* dest, const char* source, size_t len);
};

void SString::reallocStorage(size_t n) {
    this->cap += (n / len_alloc) * len_alloc;
    this->cap += (n % len_alloc) ? len_alloc : 0;
   
    if (!this->str) {
        std::cout << "memory allocated" << std::endl;
        this->str = new char[this->cap];
    }
    else {
        // alloc memory + create new pointer 
        char* str_new = new char[this->cap];
        // copy data
        copyString(str_new, this->str, this->len);

        // delete old pointer
        delete[] this->str;
        this->str = str_new;
    }
}

bool SString::isFreeStorage() {
    return (this->cap > this->len + 1);
}

void SString::copyString(char* dest, const char* source, size_t len) {
    if (!dest || !source || !len)
        return;

    for (size_t i = 0; i < len; i++) {
        dest[i] = source[i];
    }
}

void SString::append(const char* substr) {
    if (!substr) // throw exeption
        return;

    while (*substr != '\0') {
        if (!isFreeStorage()) {
            reallocStorage();
        }
        this->str[this->len++] = *substr++;
    }
    this->str[this->len] = '\0';
}

void SString::append(const char* substr, size_t sublen) {
    if (!substr) // throw exeption
        return;

    while (sublen-- > 0 && *substr != '\0') {
        if (!isFreeStorage()) {
            reallocStorage();
        }
        this->str[this->len++] = *substr++;
    }
    this->str[this->len] = '\0';
}

void SString::append(const char* in, index_t start, index_t finish) {
    for (index_t i = start; i < finish; i++) {
        if (!isFreeStorage()) {
            reallocStorage();
        }
        this->str[this->len++] = *in++;
    }
    this->str[this->len] = '\0';
}

char& SString::at(index_t ind) {
    try {
        if (ind < this->len)
            return this->str[ind];

        throw std::exception("undefined index");
    } 
    catch (const std::exception& err) {
        std::cout << "error.." << err.what() << std::endl;
    }
    return this->str[0];
}

int main()
{
    {
        SString str1;
        SString str2(str1);
        SString str("Yura");

        str1 = " hello";
        // for string " hello" create new object SString and allocated memory
        // Is it free memory?

        str2 = str + str1;
    }

    {
        SString str1("hello");
        SString str2(" world!");
        SString str3(str1);

        std::cout << str1 << std::endl;
        std::cout << str2 << std::endl;
        std::cout << str3 << std::endl;

        //str1.append(" my sunny");
        str1 = str1 + str2;
        std::cout << str1 << std::endl;

        //str1.append(" world", 6);
        str1 = str1 + "!";
        std::cout << str1 << std::endl;

        //str1.append("!", 0, 1);
        str1 += str3;
        std::cout << str1 << std::endl;
    }
    
    {
        SString str3(new char[5]);
    }

    {
        SString str("Yura");

        struct {
            bool operator()(int a, int b) const { return a < b; }
        } customLess;

        // have some problem with sort
        //std::sort(str.at(0), str.at(3), customLess);
    }
    
}