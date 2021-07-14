#include <iostream>
#include <mutex>
using namespace std;

template <typename T> class Queue{
    private:
        T *Data = new T[0];
        int Size = 0;
        mutex m;

    public:
        ~Queue(){
            lock_guard<mutex> lock(m);
            delete [] Data;
        }

        //добавление переменной в конец
        void push(T value){
            lock_guard<mutex> lock(m);
            T *buffer = new T[Size + 1];
            for(int i = 0; i < Size; i++){
                if(value == Data[i]){
                    delete [] buffer;
                    return;
                }
                buffer[i] = Data[i];
            }
            buffer[Size] = value;
            Size++;
            delete [] Data;
            Data = buffer;
        }
        
        //удаление первого элемента
        void pop(){
            lock_guard<mutex> lock(m);
            if(Size == 0) return;
            T *buffer = new T[Size - 1];
            for(int i = 1; i < Size; i++){
                buffer[i - 1] = Data[i];
            }
            Size--;
            delete [] Data;
            Data = buffer;
        }
        
        T front(){
            lock_guard<mutex> lock(m);
            if(Size == 0){
                throw std::out_of_range ("Out of range Queue<T>::front()");
            }
            return Data[0];
        }
        
        T back(){
            lock_guard<mutex> lock(m);
            if(Size == 0){
                throw std::out_of_range ("Out of range Queue<T>::back()");
            }
            return Data[Size - 1];
        }

        bool empty(){
            lock_guard<mutex> lock(m);
            return ( Size == 0 );
        }

        int size(){
            lock_guard<mutex> lock(m);
            return Size;
        }

        void print(){
            lock_guard<mutex> lock(m);
            for(int i = 0; i < Size; i++){
                cout << "[" << i << "]: " << Data[i] << endl;
            }
        }

        void operator= (Queue<T> &newQueue){
            lock_guard<mutex> lock(m);
            delete [] Data;
            Size = newQueue.size();
            Data = new T[Size];
            for(int i = 0; i < Size; i++){
                Data[i] = newQueue.Data[i];
            }
        }
};