#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "Defs.h"

template<class tdata>
struct QueueItem
{
	tdata data;
	QueueItem<tdata>* next;

	inline QueueItem(const tdata& _data) : data(_data), next(NULL)
	{}
};


template<class tdata>
class Queue
{

public:

	QueueItem<tdata>* start;

public:

	inline Queue() : start(NULL)
	{}

	~Queue()
	{
		Clear();
	}

	unsigned int Count() const
	{
		unsigned int result = 0;
		QueueItem<tdata>* tmp;

		for (tmp = start; tmp != NULL; tmp = tmp->next)
			++result;

		return result;
	}

	QueueItem<tdata>* GetLast()
	{
		QueueItem<tdata>* tmp = start;

		while (tmp != NULL && tmp->next != NULL)
			tmp = tmp->next;

		return tmp;
	}

	void Push(const tdata& item)
	{
		QueueItem<tdata>* pDataItem;
		pDataItem = new QueueItem<tdata>(item);

		QueueItem<tdata>* last = GetLast();

		if (last == NULL)
		{
			start = pDataItem;
		}
		else
		{
			last->next = pDataItem;
		}
	}

	bool Pop(tdata& item)
	{
		bool result = false;

		if (start != nullptr)
		{
			QueueItem<tdata>* newStart = start->next;
			item = start->data;
			RELEASE(start);
			start = newStart;
			result = true;
		}

		return result;
	}

	const tdata* Peek(unsigned int index) const
	{
		unsigned int i = 0;
		QueueItem<tdata>* tmp;

		for (tmp = start; tmp != NULL && i < index; tmp = tmp->next)
			++i;

		if (tmp != NULL)
			return &(tmp->data);

		return NULL;
	}

	void Clear()
	{
		QueueItem<tdata>* pData;
		QueueItem<tdata>* pNext;
		pData = start;

		while (pData != NULL)
		{
			pNext = pData->next;
			RELEASE(pData);
			pData = pNext;
		}

		start = NULL;
	}

};
#endif // __QUEUE_H__
