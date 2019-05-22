//
//  main.cpp
//  Linked List
//
//  Created by Dylan Hawley on 10/10/18.
//  Copyright © 2018 Dylan Hawley. All rights reserved.
//

#include "XORLinkedList.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void TestAddHead();
void TestAddTail();
void TestRemove();
void TestRemove2();
void TestRemoveAt(unsigned int index);
void PrintHeadTail(XORLinkedList<int> &data);
void TestAssign();

int main()
{
    int testNum;
    cin >> testNum;
    if (testNum == 1)
        TestAddHead();
    else if (testNum == 2)
        TestAddTail();
    else if (testNum == 3)
        TestRemove();
    else if (testNum == 4)
        TestRemove2();
    else if (testNum == 5)
        TestAssign();
    return 0;
}

void TestAddHead()
{
    cout << "=====Testing AddHead() functionality====" << endl;
    XORLinkedList<int> data;
    for (int i = 0; i < 12; i += 2)
        data.AddHead(i);
    cout << "Node count: " << data.NodeCount() << endl;
    cout << "Print list forward:" << endl;
    data.PrintForward();
    cout << "Print list in reverse:" << endl;
    data.PrintReverse();
}

void TestAddTail()
{
    cout << "=====Testing AddTail() functionality====" << endl;
    XORLinkedList<int> data;
    for (int i = 0; i <= 21; i += 3)
        data.AddTail(i);
    cout << "Node count: " << data.NodeCount() << endl;
    cout << "Print list forward:" << endl;
    data.PrintForward();
    cout << "Print list in reverse:" << endl;
    data.PrintReverse();
}

void TestRemove()
{
    cout << "=====Testing Remove() functionality=====" << endl;
    for(int i = 0; i <= 7; i++) TestRemoveAt(i);
}

void TestRemove2()
{
    cout << "=====Testing Remove2() functionality=====" << endl;
    for(int i = 1; i <= 3; i++) {
        XORLinkedList<int> data;
        for (int j = 0; j < i; j++)
            data.AddTail(3*j);
        cout << "Print list of size:" << i << endl;
        data.PrintForward();
        while(data.RemoveAt(1));
        cout << "Print list after delete:" << endl;
        data.PrintForward();
        data.PrintReverse();
        PrintHeadTail(data);
        cout << "======" << endl;
    }
    XORLinkedList<int> data;

}

void TestRemoveAt(unsigned int index) {
    XORLinkedList<int> data;
    for (int i = 0; i <= 21; i += 3)
        data.AddTail(i);
    cout << "Removing index " << index << endl;
    cout << "Print list:" << endl;
    data.PrintForward();
    data.RemoveAt(index);
    data.RemoveTail();
    cout << "Print list after delete:" << endl;
    data.PrintForward();
    PrintHeadTail(data);
    cout << endl;
}

void PrintHeadTail(XORLinkedList<int> &data) {
    cout << "Head: " << data.Head()->data << endl;
    cout << "Tail: " << data.Tail()->data << endl;
}

void TestAssign() {
    XORLinkedList<int> data;
    for (int i = 0; i <= 21; i += 3)
        data.AddTail(i);
    data.PrintForward();
    cout << "Copying..." << endl;
    XORLinkedList<int> data2;
    data2 = data;
    data.PrintForward();
}