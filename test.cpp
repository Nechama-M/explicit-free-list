#include <iostream>
#include "memory_allocation.h"
#include "test.h"

void test()
{
	try
	{
		std::cout<< Person::s_firstFree <<std::endl;
		std::cout<< Person::s_pool <<std::endl;
		
		int i = 1;
		while(true)
		{
			Person *p=new Person;
			std::cout<< "pointer to person number "<< i << " is allocated at address: " << p <<std::endl;
			i++;
		}
	}
	catch(const std::bad_alloc& e)
	{
		std::cout<< e.what() <<std::endl;
	}
}
