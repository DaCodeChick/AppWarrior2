#include "../include/CPtrList.hpp"


struct SNode
{
	void *next, *prev;
};


void CVoidPtrList::AddItem(void *inData)
{
	SNode *node = (SNode *)((uint8 *)inData + mOffset);
	node->next = NULL;
	node->prev = mTail;

	if (!mTail)
		mHead = inData;
	else
	{
		SNode *tail = (SNode *)((uint8 *)mTail + mOffset);
		tail->next = inData;
	}

	mTail = inData;
	mCount++;
}
