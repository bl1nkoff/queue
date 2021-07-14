#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include "class.h"
using namespace std;

void threadFunc(Queue<int> *queue, int a, int n){
    for(int i = 0; i < n; i++){
        queue -> push(queue -> back() + a + 1);
    }
}

int main(){
    Queue<int> threadQueue;
    threadQueue.push(0);

    const int n = 4000;
    const int threadsNums = 4;
    const int runsNum = n * threadsNums;
    
    std::thread t0(threadFunc, &threadQueue, 0, n);
    std::thread t1(threadFunc, &threadQueue, 1, n);
    std::thread t2(threadFunc, &threadQueue, 2, n);
    std::thread t3(threadFunc, &threadQueue, 3, n);

    t0.join();
    t1.join();
    t2.join();
    t3.join();

    cout << "Размер: " << threadQueue.size() << ", Дубликатов: " << runsNum - threadQueue.size() - 1<< ", Всего операций:" << runsNum << endl << endl;
    
    Queue<char> queue;

    queue.push('2');
    queue.push('4');
    queue.push('5');
    queue.push('6');
    
    queue.print();

    cout << endl << "Front: " << queue.front() << endl;
    cout << "Back: " << queue.back() << endl;
    cout << "Empty: " << queue.empty() << endl;
    cout << "Size: " << queue.size() << endl;

    cout << endl << "Pop!" << endl;
    queue.pop();    
    cout << "Front: " << queue.front() << endl;
    cout << "Size:" << queue.size() << endl;
    queue.print();

    cout << endl << "Push duplicate!" << endl;
    cout << "Size:" << queue.size() << endl;
    queue.print();

    Queue<char> queueCopy;
    queueCopy = queue;
    cout << endl << "Copy in another one!" << endl;
    cout << "Original size: " << queue.size() << endl;
    queue.print();
    cout << "Copy size: " << queueCopy.size() << endl;
    queueCopy.print();

    cout << endl << "Try to get the first element of an empty queue: " << endl;
    Queue<int> emptyQueue;
    cout << emptyQueue.front() << endl;

    return 0;
}