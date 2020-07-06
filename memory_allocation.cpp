#include "memory_allocation.h"
#include <iostream>
#include <exception>

static const size_t SizeOfMemory = 10;



/*Auxiliary function*/
inline Person * InitPool()
{
	return (Person *) ::operator new (sizeof(Person)*SizeOfMemory);
}
inline Person * InitFreeList()
{
	Person * freeList = Person::s_pool;
	Person ** temp;
	for (size_t i=0; i < SizeOfMemory; ++i)
	{
		temp = reinterpret_cast<Person **>(freeList);
		*temp = (freeList+1);
		freeList++;
	}
	freeList = NULL;
	return Person::s_pool;
}
Person * getNextBlock(Person * block)
{
	return *(Person**)block;
}
inline bool EndOfMemory()
{
	return (getNextBlock(Person::s_firstFree)==NULL); 
}
inline void ApdateFreeList()
{
	Person ** temp = reinterpret_cast<Person **>(Person::s_firstFree);
	Person::s_firstFree = *temp;
}

Person * GetBlock()
{
	if(!EndOfMemory())
	{
		Person * head = Person::s_firstFree;
		ApdateFreeList();
		return head;
	}
	else
	{
		throw std::bad_alloc();
	}
}

void SetBlockAsAvailable(void * person)
{
	person = (Person *)person;
	Person ** temp = reinterpret_cast<Person **>(person);
	*temp = Person::s_firstFree;
	Person::s_firstFree = *temp;
}


/*end Auxiliary function*/
Person* Person::s_pool = InitPool();
Person* Person::s_firstFree = InitFreeList();

void * Person::operator new(size_t size)
{
	if(!EndOfMemory())
	{
		Person * block = GetBlock();
		block = *(Person**)block;
		return block;
	}
	else
	{
		throw std::bad_alloc();
	}
}
void Person::operator delete(void * block_to_delete)
{
	SetBlockAsAvailable(block_to_delete);
}



