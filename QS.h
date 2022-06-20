//
// Created by Nate Lampros on 11/29/21.
//

#ifndef INC_10_CS235_QUICKSORT_QS_H
#define INC_10_CS235_QUICKSORT_QS_H
#include "QSInterface.h"
#include <string>
#include <sstream>
using namespace std;

template<typename T>
class QS : public QSInterface<T> {
private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    size_t comparison = 0;
    size_t exchange = 0;
    T* qsArray;

public:

    QS(size_t capacity) {

        capacity_ = capacity;
        qsArray = new T[capacity_];
    }

    virtual ~QS() {

        if(qsArray != NULL) { delete[] qsArray; }
    }

    /** Add an element to the QuickSort array. Dynamically grow array as needed. */
    virtual bool addElement(T element) {

        if (size_ == capacity_) reallocate();

        qsArray[size_] = element;
        ++size_;

        return qsArray[size_ - 1] = element;
    }

    void reallocate(){

            size_t new_capacity = 2 * capacity_;
            T* newArray = new T[new_capacity];

            for (size_t i = 0; i < size_; ++i)
            {
                newArray[i] = qsArray[i];
            }

            capacity_ = new_capacity;

            delete [] qsArray;
            qsArray = newArray;

    }


    /** Sort the elements of a QuickSort subarray using median and partition functions. */
    virtual bool sort(size_t left, size_t right) {

        size_t pivotIndex = medianOfThree(left, right);

        if (pivotIndex == -1) return false;

        size_t temp = partition(left, right, pivotIndex);

        if (temp == -1) return false;

        sort(left, temp);
        sort(temp, right);

        return true;
    }

    void resetStats(){

        comparison = 0;
        exchange = 0;
    }

    /** Sort all elements of the QuickSort array using median and partition functions. */
    virtual bool sortAll() {

        size_t left = 0;
        size_t right = size_;

        sort(left, right);
    }

    /** Removes all items from the QuickSort array. */
    virtual bool clear() {

        size_ = 0;

        if (qsArray != NULL) {
            delete[] qsArray;
            qsArray = NULL;
        }

        qsArray = new T[capacity_];
    }

    /** Return size of the QuickSort array. */
    virtual size_t capacity() const {

        return capacity_;

    }

    /** Return number of elements in the QuickSort array. */
    virtual size_t size() const {

        return size_;

    }

    size_t comparisons() const {

        return comparison;

    }
    size_t exchanges() const {

        return exchange;

    }

    /** Calculate the median of three values and bubble sort them*/
    virtual int medianOfThree(size_t left, size_t right) {

        size_t L = left;
        size_t R = right;

        right = right - 1;

        if (size_ == 0) return -1;
        if (left < 0 || right >= size_) return -1;
        if (left > right) return -1;

        size_t middle = (L + R) / 2;

        bubbleSort(left, middle, right);
        ++comparison; // = comparison + 3;

        return middle;
    }

    void bubbleSort(size_t L, size_t M, size_t R){
        if (qsArray[L] > qsArray[M]) {
            swap(qsArray[L], qsArray[M]);
            ++exchange;
        }
        if (qsArray[L] > qsArray[R]) {
            swap(qsArray[L], qsArray[R]);
            ++exchange;
        }
        if (qsArray[M] > qsArray[R]) {
            swap(qsArray[M], qsArray[R]);
            ++exchange;
        }

    }


    /** Partitions a subarray around a pivot value selected according
    to median-of-three pivot selection.*/
    virtual int partition(size_t left, size_t right, size_t pivotIndex) {

        right = right - 1;

        if (size_ == 0) return -1;
        if (left < 0 || right >= size_) return -1;
        if (left >= right) return -1;

        swap(qsArray[left], qsArray[pivotIndex]);

        size_t up = left + 1; //up
        size_t down = right; //down

        while (up < down) {

            while (qsArray[up] <= qsArray[left] && up != right) {
                ++up;
                ++comparison;

            }
            while (qsArray[down] > qsArray[left] && down != left) {

                --down;
                ++comparison;

            }
            if (up < down) {

                swap(qsArray[up], qsArray[down]);
                ++exchange;

            }

            ++comparison;
        }

        swap(qsArray[left], qsArray[down]);
        ++exchange;

        cout << "returning partition" << endl;
        return down;

    }


    /** @return: comma delimited string representation of the array. */
    virtual std::string toString() const {

        stringstream out;

        if (size_ == 0) throw string ("Empty");

        for (int i = 0; i <= size_ - 2; ++i){

            out << qsArray[i] << ",";

        }

        out << qsArray[size_ - 1];

        return out.str();
    }
};
#endif //INC_10_CS235_QUICKSORT_QS_H
