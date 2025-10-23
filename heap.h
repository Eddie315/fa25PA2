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
        //uses upheap function i made to re organize the tree
        upheap(size, weightArr);
        size++;
        // TODO: insert index at end of heap, restore order using upheap()
    }


    int pop(int weightArr[]) {
        //use the root at first index because its already the smallest one
        int root = data[0];
        // move last element into root
data[0] = data[size-1];
        // decrease the size of the heap as we popped it out
        size--;
        // do downheap to fix the  sturcture
        downheap(0, weightArr);

        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()

        // return the popped function
        return root;
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
            if ( weightArr[data[root]] > weightArr[data[pos]]) {
                // swaps the current child when smaller than parent
                swap(data[pos], data[root]);
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
            // quick if statment to see determine what is the smallest by checking the data and if the acc size if larger
            //than the data of the right child and if it is it sets the smallest to the right child else...
            if ((rightchild < size) && weightArr[data[rightchild]] < weightArr[data[leftchild]]) {
                smallest = rightchild;
            }
            else {
                //declares the smallest child to be left since conditions arent met above
                smallest = leftchild;
            }
            if ( weightArr[data[smallest]] < weightArr[data[pos]]) {
                // swaps the current parrent downward while larger than the child
                swap(data[pos], data[smallest]);
                // reset the child logic as it has been shifted around by using child logic
                pos = smallest;
                leftchild = (pos*2)+1;
            }
            //once child and parents have been shifted to satafiy loop it ends with break
            else {
                break;
            }
        }
    }
};

#endif