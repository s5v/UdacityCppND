//
//  main.cpp
//  CppND-GarbageCollector
//
//  Created by Sanjeev Shankar on 7/27/19.
//  Copyright © 2019 s5v. All rights reserved.
//



#include <memory>
#include "gc_pointer.h"
#include "LeakTester.h"
#include <iostream>

namespace custom {
    template< typename T>
    class list {
    private:
        struct node{
            T value;
            Pointer< node > prev;
            Pointer< node > next;
            node(T val, node* _prev, node* _next) : value(val), prev(_prev), next(_next) {}
        };
        node* head;
        node* tail;
    public:
        
        // We don't have any destructors or freeing of memory
        list(): head(NULL), tail(NULL){}
        void push_back(T);
        bool empty() const { return ( !head || !tail ); }
        void print();
    };
    
    template <typename T>
    void list<T>::push_back(T val){
        list::tail = new node(val, list::tail, NULL);
        if(list::tail->prev){
            list::tail->prev->next = list::tail;
        }
        if( list::empty()){
            list::head = list::tail;
        }

    }
    
    template< typename T>
    void list<T>::print() {
        node* ptr= list::head;
        std::cout<< ptr->value <<" : ";
        while(ptr != NULL) {
            std::cout<< ptr->value <<" : ";
            ptr = ptr->next;
        }
        std::cout << std::endl;
    }
}

int main() {

    custom::list< int > list;

    Pointer<int> p = new int(19);
    p = new int(21);
    p = new int(28);
    
    Pointer<int,3> p1;
    p1 = new int[3];
    p1[0] = 88;
    //*p=p1[0];
    p1[1] = 98;
    p1[2] = 9090;
    
    int k = *p1;
    std::cout << "Test1: P1 and k are " << k << " and " << *p1 << " And " << p1[1] << std::endl;

    std::cout << "Add 5 numbers: " << std::endl;
    for(int i = 0; i < 5; i++) {
        int temp = i;
        std::cout<<"Please Enter "<< i+1<< ". integer element:"<< std::endl;
        std::cin >>temp;
        list.push_back(temp);
    }
    
    list.print();

    return 0;
}




