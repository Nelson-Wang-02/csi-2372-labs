/*Ex2 devoir4 CSI2772A*/


#include <iostream> 
#include "myFile2.h"
using namespace std;


int main() {
    SetInt a; 	// object creation
    int* tab;

    while (a.nbElem() < 5)
    {
        cout << "add an int element" << endl;
        int elem;
        cin >> elem;
        a.add(elem);

    }
    cout << "a contains 10 :" << a.contains(10) << endl;
    cout << "remove 10 " << endl;
    a.remove(10);
    cout << "a contains 10 :" << a.contains(10) << endl;
    cout << "a contains :" << a.nbElem() << " elements " << endl;
    tab = a.tabElem();
    cout << "The elements of a are :" << endl;
    for (int i =0; i<a.nbElem(); i++)
        cout << tab[i] << endl;

    return 0;
}

SetInt::SetInt(int arr[], int n) : size(n) {
    if (n > 0) {
        elem = new int[n];
        for (int i = 0; i < n; ++i) {
            elem[i] = arr[i];
        }
    }
    else {
        elem = NULL;
    }

}

SetInt::~SetInt() {
    delete[] elem;
}

SetInt::SetInt(const SetInt& x) : size(x.size) {
    if (size > 0) {
        elem = new int[size];
        for (int i = 0; i < size;++i) {
            elem[i] = x.elem[i];
        }
    }
    else {
        elem = NULL;
    }
}

void SetInt::add(int n) {
    if (!contains(n)) {
        int* newElem = new int[size + 1];
        for (int i = 0; i < size; ++i) {
            newElem[i] = elem[i];
        }
        newElem[size] = n;
        delete[] elem;
        elem = newElem;
        ++size;
    }
}

void SetInt::remove(int n) {
    int index;
    if (containsIn(n, index)) {
        int* newElem = new int[size - 1];
        for (int i = 0, j = 0; i < size; ++i) {
            if (i != index) {
                newElem[j++] = elem[i];
            }
        }
        delete[] elem;
        elem = newElem;
        --size;
    }
}

bool SetInt::contains(int n) {
    int index;
    return containsIn(n, index);
}

int SetInt::nbElem() {
    return size;
}

int* SetInt::tabElem() {
    if (size == 0) {
        return NULL;
    }
    else {
        int* result = new int[size];
        for (int i = 0; i < size; ++i) {
            result[i] = elem[i];
        }
        return result;
    }
}

bool SetInt::containsIn(int n, int& index) {
    for (int i = 0; i < size; ++i) {
        if (elem[i] == n) {
            index = i;
            return true;
        }
    }
    return false;
}