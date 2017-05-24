#pragma once
#include "dzml.h"
#include "ZObjects.h"

namespace dzml
{
	template<class T, ZObject::Type _Type>
	class ZNumberObject : public ZGCObject
	{
	private:
		T data_;

	public:
		void Initialize()
		{
			ZGCObject::Initialize();
			data_ = 0;
			type_ = _Type;
		}

		inline T GetData() const
		{
			return data_;
		}

		inline void SetData(float T)
		{
			data_ = num;
		}

	};


	class ZIntegerObject : public ZNumberObject<uc32, ZObject::Type::Integer>
	{
		DISABLE_STD(ZIntegerObject)
	};

	class ZFloatObject : public ZNumberObject<float, ZObject::Type::Float>
	{
		DISABLE_STD(ZFloatObject)
	};

	class ZDoubleObject : public ZNumberObject<double, ZObject::Type::Double>
	{
		DISABLE_STD(ZDoubleObject)
	};
}
