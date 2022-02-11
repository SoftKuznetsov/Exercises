// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main()
{
    std::set <std::string> vocabulary;

    //=======================================================
    std::string path = "Test.txt";
    std::ifstream fin;
    fin.open(path);

    if (fin.is_open()) {
        int i = 0;
        while (!fin.eof()) {
            std::string str = "";
            std::getline(fin, str); 
            vocabulary.insert(str);
        }
    }
    else {
        throw std::runtime_error("error file");
    }

    fin.close();

    //=======================================================
    std::cout << "enter key:" << std::endl;
    std::cout << "->";
    std::string key;
    std::cin >> key;

    std::set <std::string>::iterator it = vocabulary.lower_bound(key);
    while (it != vocabulary.end()) {
        if (it->rfind(key, 0) != 0) {
            break;
        }

        std::cout << "<-" << *it << std::endl;
        it++;
    }
    
}