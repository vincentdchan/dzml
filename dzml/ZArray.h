#pragma once
#include "dzml.h"
#include "ZObjects.h"
#include <functional>

namespace dzml
{

	class ZObjectPointerArray : ZGCObject
	{
	private:
		uc32 capacity_;
		(ZObject *)data_[0];

	public:
		
		static ZObjectPointerArray * New(uc32);
		static void CopyData(ZObjectPointerArray * Dst,
			ZObjectPointerArray * Src, uc32 size);

		inline uc32 GetCapacity() const
		{
			return capacity_;
		}

		inline ZObject * Get(uc32 index) const
		{
			return data_[index];
		}

		inline void Set(uc32 index, ZObject * ptr)
		{
			data_[index] = ptr;
		}

		inline ZObject*& operator=(uc32 index)
		{
			return data_[index];
		}

	};

	class ZArray : ZGCObject
	{
	private:
		uc32 size_;
		ZObjectPointerArray * array_;

		void Realloc(uc32 capacity);

	public:

		static ZArray * New();
		static ZArray * New(ZArray* another);
		void Initialize();

		bool Get(uc32 index, ZObject *& value);
		void Set(uc32 index, ZObject * value);
		void Push(ZObject * value);
		bool Pop(ZObject *& value);
		void ForEach(std::function<void(ZObject*)> iter);

		inline uc32 GetSize() const
		{
			return size_;
		}

	};

}
