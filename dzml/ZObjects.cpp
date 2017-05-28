#include "ZObjects.h"
#include "ZNumber.hpp"
#include "ZString.hpp"

namespace dzml
{

	ZObject::ZObject() :
		type_(Type::Nil)
	{
	}

	void ZGCObject::Initialize()
	{
		flag = 0;
		forwarding = nullptr;
	}

}