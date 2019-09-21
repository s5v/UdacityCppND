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
        while(ptr != NULL) {
            std::cout<< ptr->value <<" : ";
            ptr = ptr->next;
        }
        std::cout << std::endl;
    }
}

int main() {

    custom::list< int > list;
#if 1
    Pointer<int> p = new int(19);
    p = new int(21);
    p = new int(28);
    
    Pointer<int> p1;
    p1 = new int;
    *p1 = 88;
    
    int k = *p1;
    std::cout << "Test1: P1 and k are " << k << " and " << *p1 << std::endl;
#endif
#if 1
    std::cout << "Add 5 numbers: " << std::endl;
    for(int i = 0; i < 5; i++) {
        int temp = 42*2;
        std::cout<<"Add "<< i+1<< ". element:"<< std::endl;
        //std::cin >>temp;
        list.push_back(temp);
    }
    
    list.print();
#endif
    return 0;
}

#if 0

#include "gc_pointer.h"
#include "LeakTester.h"
#include <iostream>

int main()
{
    std::cout << "Hello, World!\n";
    Pointer<int> p = new int(19);
    p = new int(21);
    p = new int(28);
    
    return 0;
}


#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
#endif


