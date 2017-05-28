#pragma once
#include "dzml.h"
#include "ZObjects.h"
#include "GC.h"
#include <cstring>

namespace dzml
{

	/*
	 * A string will never be mutable
	 * so the old gen string will not
	 * point to the young gen area.
	 * 
	 * And the pointer in a string
	 * will not change. It will point to
	 * a byte array.
	 * 
	 * The BytesArray will not use a 0 as
	 * the end.
	 *
	 */
	template <typename ByteType>
	class BytesArray : public ZGCObject
	{
	protected:
		uc32 length_;
		ByteType data_[];

	public:

		static BytesArray<ByteType> * 
			New(BytesArray<ByteType> * another)
		{
			byte * bytes = GC::GetOne()->Alloc(
				sizeof(BytesArray<ByteType>) + 
				another->length_ * sizeof(ByteType)
			);
			BytesArray<ByteType> * This = reinterpret_cast<BytesArray<ByteType> *>(bytes);
			This->Initialize();
			This->length_ = another->length_;
			memcpy(This->data_, another->data_, sizeof(ByteType) * This->length_);
			return This;
		}

		void Initialize()
		{
			SetMutable(false);
			type_ = Type::String
		}

		inline uc32 GetLength() const
		{
			return length_;
		}

		inline ByteType* GetData()
		{
			return data_;
		}

		inline void SetData(uc32 index, ByteType char_)
		{
			data_[index] = char_;
		}

		DEF_CAST(BytesArray<ByteType>)
		DISABLE_STD(BytesArray)

	};

	typedef BytesArray<uc32> ZString;

}
