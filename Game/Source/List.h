#ifndef __LIST_H__
#define __LIST_H__

#include "Defs.h"

// Contains items from double linked list
template<class tdata>
struct ListItem
{
	tdata data;
	ListItem<tdata>* next;
	ListItem<tdata>* prev;

	inline ListItem(const tdata& pData)
	{
		data = pData;
		next = prev = NULL;
	}

	~ListItem()
	{}
};

// Manages a double linked list
template<class tdata>
class List
{

public:

	ListItem<tdata>* start;
	ListItem<tdata>* end;

private:

	unsigned int size;

public:

	// Constructor
	inline List()
	{
		start = end = NULL;
		size = 0;
	}

	// Destructor
	~List()
	{
		Clear();
	}

	// Get Size
	unsigned int Count() const
	{
		return size;
	}

	// Add new item
	ListItem<tdata>* Add(const tdata& item)
	{
		ListItem<tdata>* dataItem;
		dataItem = new ListItem<tdata>(item);

		if(start == NULL)
		{
			start = end = dataItem;
		}
		else
		{
			dataItem->prev = end;
			end->next = dataItem;
			end = dataItem;
		}

		++size;
		return(dataItem);
	}

	// Deletes an item from the list
	bool Del(ListItem<tdata>* item)
	{
		if(item == NULL)
		{
			return (false);
		}

		// Now reconstruct the list
		if(item->prev != NULL)
		{
			item->prev->next = item->next;

			if(item->next != NULL)
			{
				item->next->prev = item->prev;
			}
			else
			{
				end = item->prev;
			}
		}
		else
		{
			if(item->next)
			{
				item->next->prev = NULL;
				start = item->next;
			}
			else
			{
				start = end = NULL;
			}
		}

		RELEASE(item);
		--size;
		return(true);
	}

	// Destroy and free all mem
	void Clear()
	{
		ListItem<tdata>* pData;
		ListItem<tdata>* pNext;
		pData = start;

		while(pData != NULL)
		{
			pNext = pData->next;
			RELEASE(pData);
			pData = pNext;
		}

		start = end = NULL;
		size = 0;
	}

	// Read/write operator access directly to a position in the list
	tdata& operator [](const unsigned int index)
	{
		long pos;
		ListItem<tdata>* pItem;
		pos = 0;
		pItem = start;

		while(pItem != NULL)
		{
			if(pos == index)
			{
				break;
			}

			++pos;
			pItem = pItem->next;
		}

		return(pItem->data);
	}

	/**
	* const read operator access directly to a position in the list
	*/
	const tdata& operator [](const unsigned int index) const
	{
		long pos;
		ListItem<tdata>* pItem;
		pos = 0;
		pItem = start;

		while(pItem != NULL)
		{
			if(pos == index)
			{
				break;
			}

			++pos;
			pItem = pItem->next;
		}

		ASSERT(pItem);

		return(pItem->data);
	}

	const List<tdata>& operator +=(const List<tdata>& other_list)
	{
		ListItem<tdata>* pItem = other_list.start;

		while(pItem != NULL)
		{
			Add(pItem->data);
			pItem = pItem->next;
		}

		return(*this);
	}

	const ListItem<tdata>* At(unsigned int index) const
	{
		long pos = 0;
		ListItem<tdata>* pItem = start;

		while(pItem != NULL)
		{
			if(pos++ == index)
				break;

			pItem = pItem->next;
		}

		return pItem;
	}

	ListItem<tdata>* At(unsigned int index)
	{
		long pos = 0;
		ListItem<tdata>* pItem = start;

		while(pItem != NULL)
		{
			if(pos++ == index)
				break;

			pItem = pItem->next;
		}

		return pItem;
	}

	// Sort
	int BubbleSort()
	{
		int ret = 0;
		bool swapped = true;

		while(swapped)
		{
			swapped = false;
			ListItem<tdata>* tmp = start;

			while(tmp != NULL && tmp->next != NULL)
			{
				++ret;
				if(tmp->data > tmp->next->data)
				{
					SWAP(tmp->data, tmp->next->data);
					swapped = true;
				}

				tmp = tmp->next;
			}
		}

		return ret;
	}

	int Find(const tdata& data)
	{
		ListItem<tdata>* tmp = start;
		int index = 0;

		while(tmp != NULL)
		{
			if(tmp->data == data)
				return(index);

			++index;
			tmp = tmp->next;
		}
		return (-1);
	}

	void InsertAfter(uint position, const List<tdata>& list)
	{
		ListItem<tdata>* pMyList = At(position);
		ListItem<tdata>* pOtherList = list.start;

		while(pOtherList != NULL)
		{
			ListItem<tdata>* pNewItem = new ListItem<tdata>(pOtherList->data);

			pNewItem->next = (pMyList) ? pMyList->next : NULL;

			if(pNewItem->next != NULL)
				pNewItem->next->prev = pNewItem;
			else
				end = pNewItem;

			pNewItem->prev = pMyList;

			if(pNewItem->prev != NULL)
				pNewItem->prev->next = pNewItem;
			else
				start = pNewItem;

			pMyList = pNewItem;
			pOtherList = pOtherList->next;
		}
	}
};
#endif // __LIST_H__