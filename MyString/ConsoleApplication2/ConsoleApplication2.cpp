// ConsoleAplenplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>

#include "My_string.h"

int main()
{
    {
        SString str1;
        SString str2(str1);
        SString str("Yura");

        str1 = " hello";
        str2 = str + str1;

        std::cout << str << std::endl;
        std::cout << str1 << std::endl;
        std::cout << str2 << std::endl;
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

        SString str(nullptr);
    }

    {
        SString str("Yura");

        SString::Iterator it;
        // address of begin str
        it = str.begin();
        // address of end str
        it = str.end();

        //std::sort(str.begin(), str.end());
    }

    return 0;
}