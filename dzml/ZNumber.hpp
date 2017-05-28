#pragma once
#include "dzml.h"
#include "ZObjects.h"
#include "GC.h"

namespace dzml
{
	template<class T, ZObject::Type _Type>
	class ZNumber : public ZGCObject
	{
	private:
		T data_;

	public:

		static ZNumber * New()
		{
			ZNumber * This;
			GC::GetOne()->MakeGCObject<ZNumber<T>>(&This);
			This->data_ = 0;
			return This;
		}

		static ZNumber * New(T t)
		{
			ZNumber * This;
			GC::GetOne()->MakeGCObject<ZNumber<T>>(&This);
			This->data_ = t;
		}

		static ZNumber<T, _Type> * Cast(ZObject * ptr)
		{
			return reinterpret_cast<ZNumber<T, _Type>>(ptr);
		}

		void Initialize()
		{
			ZGCObject::Initialize();
			data_ = 0;
			type_ = _Type;
			SetMutable(false);
		}

		inline T GetData() const
		{
			return data_;
		}

		inline void SetData(float T)
		{
			data_ = num;
		}

		DISABLE_STD(ZNumber)

	};

	typedef ZNumber<uc32, ZObject::Type::Integer> ZInteger;
	typedef ZNumber<float, ZObject::Type::Float> ZFloat;
	typedef ZNumber<double, ZObject::Type::Double> ZDouble;

}
