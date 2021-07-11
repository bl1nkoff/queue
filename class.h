#include <iostream>
#include <mutex>
using namespace std;

template <typename T> class Queue{
    private:
        T *Data;
        int Size;
        mutex m;

    public:
        Queue(){
            Data = new T[0];
            Size = 0;
        }
        ~Queue(){
            delete [] Data;
        }

        //добавление переменной в конец
        void push(T value){
            m.lock();
            T *buffer = new T[Size + 1];
            for(int i = 0; i < Size; i++){
                if(value == Data[i]){
                    delete [] buffer;
                    m.unlock();
                    return;
                }
                buffer[i] = Data[i];
            }
            buffer[Size] = value;
            Size++;
            delete [] Data;
            Data = buffer;
            m.unlock();
        }
        
        //удаление первого элемента
        void pop(){
            if(Size == 0) return
            m.lock();
            T *buffer = new T[Size - 1];
            for(int i = 1; i < Size; i++){
                buffer[i - 1] = Data[i];
            }
            Size--;
            delete [] Data;
            Data = buffer;
            m.unlock();
        }
        
        T front(){
            return Data[0];
        }
        
        T back(){
            return Data[Size - 1];
        }

        bool empty(){
            return Size == 0;
        }

        int size(){
            return Size;
        }

        void print(){
            m.lock();
            for(int i = 0; i < Size; i++){
                cout << "[" << i << "]: " << Data[i] << endl;
            }
            m.unlock();
        }

        void operator= (Queue<T> &newQueue){
            delete [] Data;
            Size = newQueue.size();
            Data = new T[Size];;
            for(int i = 0; i < Size; i++){
                Data[i] = newQueue.Data[i];
            }
        }
        
        bool operator== (Queue<T> &newQueue){
            if(Size != newQueue.size()) return false;
            if(Size == 0) return true;
            for(int i = 0; i < Size; i++){
                if(Data[i] != newQueue.Data[i]) return false;
            }
            return true;
        }
};