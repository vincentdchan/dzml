#include "ZObjects.h"
#include "ZNumberObject.hpp"

namespace dzml
{

	void ZObject::Initialize()
	{
		type_ = Type::Integer;
	}

	ZIntegerObject* ZObject::toInt()
	{
		return reinterpret_cast<ZIntegerObject*>(this);
	}

	ZFloatObject* ZObject::toFloat()
	{
		return reinterpret_cast<ZFloatObject*>(this);
	}

	ZDoubleObject* ZObject::toDouble()
	{
		return reinterpret_cast<ZDoubleObject*>(this);
	}

	void ZGCObject::Initialize()
	{
		ZObject::Initialize();
		flag = 0;
		forwarding = nullptr;
	}

}