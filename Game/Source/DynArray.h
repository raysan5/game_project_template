#ifndef __DYNARRAY_H__
#define __DYNARRAY_H__

#include "Defs.h"

#define DYN_ARRAY_BLOCK_SIZE 16

template<class VALUE>
class DynArray
{
private:

	VALUE* data;
	unsigned int memCapacity;
	unsigned int numElements;

public:

	// Constructors
	DynArray() : memCapacity(0), numElements(0), data(NULL)
	{
		Alloc(DYN_ARRAY_BLOCK_SIZE);
	}

	DynArray(unsigned int capacity) : memCapacity(0), numElements(0), data(NULL)
	{
		Alloc(capacity);
	}

	// Destructor
	~DynArray()
	{
		delete[] data;
	}

	// Operators
	VALUE& operator[](unsigned int index)
	{
		ASSERT(index < numElements);
		return data[index];
	}

	const VALUE& operator[](unsigned int index) const
	{
		assert(index < numElements);
		return data[index];
	}

	const DynArray<VALUE>& operator+= (const DynArray<VALUE>& array)
	{
		if(numElements + array.numElements > memCapacity)
			Alloc(numElements + array.numElements);

		for(uint i = 0; i < array.numElements; ++i)
			data[numElements++] = array.data[i];

		return(*this);
	}

	// Data Management
	void PushBack(const VALUE& element)
	{
		if(numElements >= memCapacity)
		{
			Alloc(memCapacity + DYN_ARRAY_BLOCK_SIZE);
		}

		data[numElements++] = element;
	}

	bool Pop(VALUE& result)
	{
		if(numElements > 0)
		{
			result = data[--numElements];
			return true;
		}
		return false;
	}

	void Clear()
	{
		numElements = 0;
	}

	bool Insert(const VALUE& element, unsigned int position)
	{
		if(position > numElements)
			return false;

		if(position == numElements)
		{
			PushBack(element);
			return true;
		}

		if(numElements + 1 > memCapacity)
			Alloc(memCapacity + DYN_ARRAY_BLOCK_SIZE);

		for(unsigned int i = numElements; i > position; --i)
		{
			data[i] = data[i - 1];
		}

		data[position] = element;
		++numElements;

		return true;
	}

	bool Insert(const DynArray<VALUE>& array, unsigned int position)
	{
		if(position > numElements)
			return false;

		if(numElements + array.numElements > memCapacity)
			Alloc(numElements + array.numElements + 1);

		for(unsigned int i = position; i < position + array.numElements; ++i)
		{
			data[i + array.numElements] = data[i];
			data[i] = array[i - position];
			++numElements;
		}

		return true;
	}

	VALUE* At(unsigned int index)
	{
		VALUE* result = NULL;

		if(index < numElements)
			return result = &data[index];

		return result;
	}

	const VALUE* At(unsigned int index) const
	{
		VALUE* result = NULL;

		if(index < numElements)
			return result = &data[index];

		return result;
	}

	// Utils
	unsigned int GetCapacity() const
	{
		return memCapacity;
	}

	unsigned int Count() const
	{
		return numElements;
	}

	// Sort
	int BubbleSort()
	{
		int ret = 0;
		bool swapped = true;

		while(swapped)
		{
			swapped = false;
			for(unsigned int i = 0; i < numElements - 2; ++i)
			{
				++ret;
				if(data[i] > data[i + 1])
				{
					SWAP(data[i], data[i + 1]);
					swapped = true;
				}
			}
		}

		return ret;
	}


	int BubbleSortOptimized()
	{
		int ret = 0;
		unsigned int count;
		unsigned int last = numElements - 2;

		while(last > 0)
		{
			count = last;
			last = 0;
			for(unsigned int i = 0; i < count; ++i)
			{
				++ret;
				if(data[i] > data[i + 1])
				{
					SWAP(data[i], data[i + 1]);
					last = i;
				}
			}
		}
		return ret;
	}


	int CombSort()
	{
		int ret = 0;
		bool swapped = true;
		int gap = numElements - 1;
		float shrink = 1.3f;

		while(swapped || gap > 1)
		{
			gap = MAX(1, gap / shrink);

			swapped = false;
			for(unsigned int i = 0; i + gap < numElements - 1; ++i)
			{
				++ret;
				if(data[i] > data[i + gap])
				{
					SWAP(data[i], data[i + gap]);
					swapped = true;
				}
			}
		}

		return ret;
	}

	void Flip()
	{
		VALUE* start = &data[0];
		VALUE* end = &data[numElements-1];

		while(start < end) SWAP(*start++, *end--);
	}

private:

	// Private Utils
	void Alloc(unsigned int mem)
	{
		VALUE* tmp = data;

		memCapacity = mem;
		data = new VALUE[memCapacity];

		numElements = MIN(memCapacity, numElements);

		if(tmp != NULL)
		{
			for(unsigned int i = 0; i < numElements; ++i) data[i] = tmp[i];

			delete[] tmp;
		}
	}
};

#endif // __DYNARRAY_H__