#pragma once
#include <iostream>
#include "SafeArrayOutOfBoundsException.h"

using namespace std;

template<class T>
class SafeArray
{
public:
	SafeArray();
	SafeArray(int size);

	int size();

	SafeArray(SafeArray<T>& arrayAdded);

	//int&
	T& operator[](int pos);

	void push_back(const T& elementToAdd);
	void push_back(SafeArray<T>& arrayToAdd);



	T& at(int pos);

	void resize(int newSize);

	void insert(int pos, const T& elementToAdd);
	void insert(int pos, SafeArray<T>& elements);

	T pop_back();
	T remove(int pos);

	void removeRange(int startIndex, int endIndex);


	~SafeArray();



private:
	//int*
	T* p_arr;
	int numOfElements;
	int arrayLength;



};
template <class T>
SafeArray<T>::SafeArray()
{
	//creates an array of 10 elements
	p_arr = new T[10];
	numOfElements = 0;
	arrayLength = 10;
}
template<class T>
SafeArray<T>::SafeArray(int size)
{
	if (size >= 0)
	{
		int initialSize = size;
		//making a pointer array 
		p_arr = new T[initialSize];
		numOfElements = initialSize;
		arrayLength = initialSize;
	}//exception
	else
	{
		SafeArrayOutOfBoundsException e;
		throw e;
	}

}
template<class T>
SafeArray<T>::SafeArray(SafeArray<T>& arrayAdded)
{
	//creates an array to fill in the correct size of the element
	p_arr = new T[arrayAdded.arrayLength];


	//copies each element into the array setting to 0
	for (int i = 0; i < arrayAdded.size(); i++)
	{
		p_arr[i] = arrayAdded[i];

	}
	numOfElements = arrayAdded.numOfElements;
	arrayLength = arrayAdded.size();
}
template <class T>
T& SafeArray<T>::at(int pos)
{

	return p_arr[pos];


}
template <class T>
T& SafeArray<T>::operator[](int pos)
{
	return at(pos);
}
template <class T>
int SafeArray<T>::size()
{
	//returns the number of elements in the array.  
	//have a capacity
	return numOfElements;
}
template <class T>
void SafeArray<T>::resize(int newSize)
{

	//resize array if needed, if not still need to get the array
	//and add it to the new array if we have enough size
	//creates an array to fill in the new size of the element to max
	T* tempArray = new T[newSize];
	arrayLength = newSize;

	if (numOfElements < newSize)
	{
		for (int i = 0; i < numOfElements; i++)
		{
			tempArray[i] = p_arr[i];

		}
		//cout << "Doubling " << numOfElements << " to " << newSize << endl;
		arrayLength = newSize;
	}
	else
	{
		for (int i = 0; i < newSize; i++)
		{
			tempArray[i] = p_arr[i];
		}
		//cout << "Halved from " << numOfElements << " to" << newSize << endl;
		arrayLength = newSize;

	}
	delete[] p_arr;
	p_arr = tempArray;

}
template <class T>
void SafeArray <T>::push_back(const T& elementToAdd)
{
	if (arrayLength <= numOfElements)
	{
		resize(arrayLength * 2);
	}
	p_arr[numOfElements] = elementToAdd;
	numOfElements++;
}
template <class T>
void SafeArray<T>::push_back(SafeArray<T>& arrayToAdd)
{
	//loop to have access to push_back
	for (int i = 0; i < arrayToAdd.size(); i++)
	{
		push_back(arrayToAdd[i]);
	}
}
template <class T>
void SafeArray<T>::insert(int pos, const T& elementToAdd)
{
	if (arrayLength < numOfElements + 1)
	{
		resize(arrayLength * 2);
	}
	//loop to insert an element in a position 
	for (int i = numOfElements; 1 >= pos; i--)
	{
		p_arr[i + 1] = p_arr[i];
	}
	//making sure not to step out of bounds
	p_arr[pos] = elementToAdd;
	numOfElements = numOfElements + 1;
}
template <class T>
void SafeArray<T>::insert(int pos, SafeArray<T>& elements)
{
	//loop to insert a array into a position into another array
	for (int i = 0; i < elements.size(); i++)
	{
		insert(pos, elements[i]);
		pos++;
	}

}
template<class T>
T SafeArray<T>::pop_back()
{
	//using my resize function
	T last_Element;

	last_Element = p_arr(numOfElements - 1);

	numOfElements = numOfElements - 1;

	if ((numOfElements - 1) < (maxSize / 2))
	{
		resize(arrayLength / 2);
	}
	return last_Element;
}
template<class T>
T SafeArray<T>::remove(int pos)
{
	//this class is pretty straightforward
	//loop choosing an element to remove at a position
	T element_Remove;
	element_Remove = p_arr[pos];
	for (int i = pos; i < numOfElements; i++)
	{
		p_arr[i] = p_arr[i + 1];
	}
	if ((numOfElements - 1) < (arrayLength / 2))
	{
		resize(arrayLength / 2);
	}
	numOfElements = numOfElements - 1;
	return element_Remove;
}
template <class T>
void SafeArray<T>::removeRange(int startIndex, int endIndex)
{
	//deleting a range of the array from one point to the other
	//then after loop from the start index you are erasing is to the end index
	for (int i = startIndex; i <= endIndex; i++)
	{
		remove(startIndex);
	}
}
template <class T>
SafeArray<T>::~SafeArray()
{
	//delete extra memory on the heap size
	delete[] p_arr;
}
