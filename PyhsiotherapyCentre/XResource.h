#pragma once
#include"UEResource.h"
// XResoruce is the same as RoomSource but i renamed it for compatibility
class XResource : public UEResource
{
private:
	int capacity;
	int count;
public:
	XResource(char Type,int capacity) :UEResource(Type)
	{
		this->capacity = capacity;
	}
	int getCapacity()
	{
		return capacity;
	}
	void InCount()
	{
		count++;
	}
	void DeCount()
	{
		count--;
	}
};

