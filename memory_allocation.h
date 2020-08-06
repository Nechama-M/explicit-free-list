#ifndef __MEMORY_ALLOCATION_H__
#define __MEMORY_ALLOCATION_H__

#include <iostream>
#include <cstring>/*for strcpy*/


class Base
{
public:
	Base(){}
	~Base();
	
private:
	void * operator new[](size_t);
	void operator delete[](void *);
	Base(const Base &);
	Base & operator=(const Base &);
};



class Person : private Base
{
public:
	Person(){}
	Person(char * fullname,unsigned int id,unsigned char age);

	void * operator new(size_t);
	void operator delete(void *);
	void Initialization();

	static Person * s_pool;
	static Person * s_firstFree;
	
private:

	unsigned int m_id;
	unsigned char m_age;
	char m_fullname[32];	
};


inline Person::Person(char * fullname,unsigned int id,unsigned char age):m_id(id),m_age(age),m_fullname("\0")
{
	strcpy(m_fullname,fullname);
}



#endif /*__MEMORY_ALLOCATION_H__*/
