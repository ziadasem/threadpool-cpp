#include "../include/threadpool.hpp"

#include <iostream>
#define print(X) {std::cout<<X<<std::endl;}

template<int id, int m_seconds>
void task() {
    std::this_thread::sleep_for(std::chrono::seconds(m_seconds));
    print("Goodbye I was "<<id<<"and now I have finished!!");
}

int main() {
    ThreadPool threadpool(4);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ;
    threadpool.addTask(&task<0, 2>);
    threadpool.addTask(&task<1, 3>);
    threadpool.addTask(&task<2, 4>);
    threadpool.addTask(&task<3, 1>);
    // //blocking
    threadpool.addTask(&task<4, 3>);


    threadpool.addTask(&task<4, 5>);
    threadpool.addTask(&task<5, 5>);
    threadpool.addTask(&task<6, 5>);
    threadpool.addTask(&task<7, 5>);
    
    threadpool.expandPool(2);

    threadpool.addTask(&task<8, 5>);
    threadpool.addTask(&task<9, 5>);
    threadpool.addTask(&task<10, 5>);
    threadpool.addTask(&task<11, 5>);
    threadpool.addTask(&task<12, 5>);
    threadpool.addTask(&task<13, 5>);
    threadpool.addTask(&task<14, 5>);
    threadpool.addTask(&task<15, 5>);


    print("Done")

}