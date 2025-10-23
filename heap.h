//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        data[size] = idx;
        upheap(size, weightArr);
        size++;
        // TODO: insert index at end of heap, restore order using upheap()
    }


    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        // little while loop to traverse and swap the child upwards while the pos is greater than 0 and
        // stops once it's less than 0
        while (pos >0) {
            //used to find the root aka parrent
            // to find left child do (pos*2)+1
            // to find right child do (pos*2)+2
            int root = (pos - 1) / 2;
            if ( weightArr[root] > weightArr[pos] ) {
                // swaps the current child when smaller than parent
                swap(data[pos], weightArr[root]);
                pos = root;
            }
            //if pos is less than 0 will end the loop cycle
            else {
                break;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        int leftchild = (pos*2)+1;
        while (leftchild < size) {
            //used to find the root aka parrent same code as
            int rightchild = (pos*2)+2;
            int smallest;
            if (weightArr[data[leftchild]] > weightArr[data[rightchild]] && rightchild < size) {
                smallest = rightchild;
            }
            else {
                smallest = leftchild;
            }
            if ( weightArr[data[smallest]] < weightArr[data[pos]]) {
                // swaps the current child when smaller than parent
                swap(data[pos], data[smallest]);
                pos = smallest;
                leftchild = (pos*2)+1;
            }
            //if pos is less than 0, will end the loop cycle
            else {
                break;
            }
        }
    }
};

#endif