// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>

void produce(int&);
void consume(int&, unsigned short); 

bool is_ready = false;
bool is_processing = true;

std::mutex g_mutex;
std::condition_variable cv;

int main()
{
    int counter = 0;
    unsigned short size = 0;

    std::cout << "enter number of range 0..";
    std::cin >> size;

    std::thread woker_thread(consume, std::ref(counter), size);

    do {
        produce(std::ref(counter));
    } while (counter < size);
    
    woker_thread.join();
    return 0;
}

void produce(int& n) {
    std::unique_lock<std::mutex> lk(g_mutex);
    cv.wait(lk, [] {return is_processing;});

    is_ready = true;
    is_processing = false;
    n++;

    lk.unlock();
    cv.notify_all();
}

void consume(int& n, unsigned short s) {
    do {
        std::unique_lock<std::mutex> lk(g_mutex);
        cv.wait(lk, [] {return is_ready; });

        if (n < s) {
            std::cout << n << ", ";
        }
        else {
            std::cout << n << "..";
        }
        
        is_ready = false;
        is_processing = true;

        lk.unlock();
        cv.notify_all();
    } while (n < s);
}
