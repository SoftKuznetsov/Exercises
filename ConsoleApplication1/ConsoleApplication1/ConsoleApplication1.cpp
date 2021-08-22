// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

class DummyLogClass;

template <class T>
class UniquePtr {
public:
    UniquePtr(T* p) {
        this->pointer = p;
    }

    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator= (const UniquePtr&& other) = delete;

    UniquePtr(UniquePtr&& other) noexcept {
        pointer = other.pointer;
        other.pointer = nullptr;
    }

    ~UniquePtr() {
        delete pointer;
    }
private:
    T* pointer;
};

UniquePtr<DummyLogClass> getObject()
{
    UniquePtr<DummyLogClass> ptr{ new DummyLogClass() };
    return ptr; //OK if NRVO works. Compile error otherwise.
}



class DummyLogClass
{
public:
    DummyLogClass()
    {
        std::cout << "DummyLogClass()\n";
    }
    DummyLogClass(const DummyLogClass&)
    {
        std::cout << "DummyLogClass(const DummyLogClass&)\n";
    }
    ~DummyLogClass()
    {
        std::cout << "~DummyLogClass\n";
    }
};

int main()
{
    {
        UniquePtr<DummyLogClass> ptr{ new DummyLogClass() }; // DummyLogClass()
    } // ~DummyLogClass()

    {
        UniquePtr<DummyLogClass> ptr{ new DummyLogClass() };
        //UniquePtr<DummyLogClass> ptr1{ ptr }; //Compile error;
        //UniquePtr<DummyLogClass> ptr1 = ptr;  //Compile error;
    }

    {
        auto ptr = getObject();//OK
    }

    {
        std::vector<UniquePtr<DummyLogClass>> vec; // OK
        for (int i = 0; i < 1000000; ++i)
        {
            vec.push_back(UniquePtr<DummyLogClass>{new DummyLogClass()}); // OK
        }
    }

    return 0;
}