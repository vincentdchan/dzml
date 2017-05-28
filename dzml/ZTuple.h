#pragma once
#include "dzml.h"
#include "ZObjects.h"
#include "GC.h"

namespace dzml
{

	class ZTuple : public ZGCObject
	{
	private:
		uc16 length_;
		(ZObject*) data_[];

	public:

		static ZTuple * New(uc16 len)
		{
			byte * bytes_ = GC::GetOne()->Alloc(sizeof(ZTuple) + sizeof(ZObject*) * len);
			ZTuple * This = reinterpret_cast<ZTuple*>(bytes_);
			This->Initialize();
			This->length_ = len;
			memset(This->data_, 0, sizeof(ZGCObject*) * len);
			return This;
		}

		void Initialize()
		{
			type_ = Type::Tuple;
		}

		inline uc16 GetLength() const
		{
			return length_;
		}

		inline ZObject ** GetData()
		{
			return data_;
		}

		inline ZObject * GetChild(uc16 index)
		{
			return data_[index];
		}

		inline void SetChild(uc16 index, ZObject * obj)
		{
			data_[index] = obj;
		}

		DEF_CAST(ZTuple)
		DISABLE_STD(ZTuple)

	};

}
