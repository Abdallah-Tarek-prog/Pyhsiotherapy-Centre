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
		count = 0;
		this->capacity = capacity;
	}
	int getCapacity() const
	{
		return capacity;
	}
	int getCount() const
	{
		return count;
	}
	void InCount()
	{
		count++;
	}
	void DeCount()
	{
		count--;
	}

	friend std::ostream& operator<<(std::ostream& out,const XResource& r) {
		out << 'R' << r.ID << '[' << r.count << ", " << r.capacity << ']';

		return out;
	}
};

