//
//  main.cpp
//  LW3
//
//  Created by Stanislav Martynov on 26/10/2019.
//  Copyright © 2019 Stanislav Martynov. All rights reserved.
//

#include <iostream>
#include <atomic>
#include "shared_ptr.h"
using namespace std;

int main(){

    Shared_Ptr<int> ptr(10);
    Shared_Ptr<int> ptr1(ptr);

    cout << "ptr count(2)" << ptr.use_count() << endl;
    cout << "ptr count(2)" << ptr1.use_count() << endl;

    Shared_Ptr<int> ptr2(ptr1);

    cout << "ptr count(3)" << ptr.use_count() << endl;
    cout << "ptr count(3)" << ptr1.use_count() << endl;

    ptr.reset();
    ptr2.reset();

    cout << "ptr count(0)" << ptr.use_count() << endl;
    cout << "ptr count(1)" << ptr1.use_count() << endl;
    cout << "ptr count(0)" << ptr2.use_count() << endl;

    Shared_Ptr<int> ptr3(15);

    ptr3.swap(ptr1);
    cout << endl;
    cout << ptr.use_count() << endl;
    cout << ptr1.use_count() << endl;
    return 0;
}
