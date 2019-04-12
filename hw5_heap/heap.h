
#ifndef _HEAP_H_
#define _HEAP_H_

#include <iostream>
#include <climits>
using namespace std;

#define HEAPSIZE 500000

template <class K, class E>
class Node {
    public:
        K key;
        E element;
};

template <class K, class E>
class AbsHeap {

    public:
        AbsHeap() {
            ary = new Node<K,E> [HEAPSIZE];
            size = 0;
        }

        ~AbsHeap() {
            delete[] ary;
        }

        // Remember to ++size
        virtual void push(K _key, E _element) = 0;

        // return the element with the minimum key, remember to --size
        virtual E pop() = 0;

        void printArray() const {
            cout << "(Index, Key, Element)" << endl;
            for (int i=0; i<size; i++)
                cout << "(" << i << "," << ary[i].key << "," << ary[i].element << ")" << endl;
        }

        void printByPopping() {
            while (!isEmpty())
                cout << pop();
            cout << endl;
        }

        K getTopKey() const {
            return ary[0].key;
        }

        bool isEmpty() const {
            return (size == 0);
        }

        // This function is for your convenience
        void swap(int i, int j) {
            Node<K,E> temp = ary[i];
            ary[i] = ary[j];
            ary[j] = temp;
        }

    protected:
        Node<K,E> *ary;
        int size;

};


template <class K, class E>
class Heap: public AbsHeap<K,E> {
public:
    // You need these three lines for template inheritance.
    // Otherwise, you'll have to use this->ary to access ary
    using AbsHeap<K,E>::ary;
    using AbsHeap<K,E>::size;
    using AbsHeap<K,E>::swap;

    /**************************
     * Complete your code here.
     * You need to implement all
     * pure virtual functions (push & pop).
     * ************************/
    void push(K k, E e)
    {
        ary[size].key = k;
        ary[size].element = e;
        int cur = size;
        int parent = (cur-1)/2;
        while(parent >= 0 && cur!=0)
        {
            if(ary[parent].key > ary[cur].key)
                swap(parent, cur);
            cur = parent;
            parent = (cur-1)/2;
        }
        size++;
    }
    
    E pop()
    {
        E value = ary[0].element;
        ary[0] = ary[size-1];
        size--;
        int cur = 0;
        int s_child = compare(2*cur+1, 2*cur+2);
        while(s_child < size)
        {
            if(ary[cur].key > ary[s_child].key)
                swap(cur, s_child);
            cur = s_child;
            s_child = compare(2*cur+1, 2*cur+2);
        }
        return value;
    }
    
    //helper function
    int compare(int l_child, int r_child)
    {
        if(!(l_child < size))
            return INT_MAX;
        if(ary[l_child].key > ary[r_child].key)
            return r_child;
        else
            return l_child;
    }

};


#endif
