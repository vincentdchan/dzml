#include "ZArray.h"
#include "GC.h"
#include <cstring>

namespace dzml
{

	ZObjectPointerArray *
		ZObjectPointerArray::New(uc32 capacity)
	{
		byte * space = GC::GetOne()->Alloc(sizeof(ZObjectPointerArray) + sizeof(ZObjectPointerArray*) * capacity);
		auto This = reinterpret_cast<ZObjectPointerArray*>(space);
		This->capacity_ = capacity;
		memset(This->data_, 0, sizeof(ZObjectPointerArray*) * capacity);
		return This;
	}

	void ZObjectPointerArray::CopyData(ZObjectPointerArray * Dst,
		ZObjectPointerArray * Src, uc32 size)
	{
		memcpy(Dst->data_, Src->data_, sizeof(ZObject * ) * size);
	}

	ZArray * ZArray::New()
	{
		ZArray * This = nullptr;
		GC::GetOne()->MakeGCObject<ZArray>(&This);
		This->array_ = ZObjectPointerArray::New(ARRAY_DEFAULT_SIZE);
		return This;
	}

	ZArray * ZArray::New(ZArray * another)
	{
		ZArray * This = nullptr;
		GC::GetOne()->MakeGCObject<ZArray>(&This);
		This->array_ = ZObjectPointerArray::New(ARRAY_DEFAULT_SIZE);
		another->ForEach([&This](ZObject * obj){
			This->Push(obj);
		});
		return This;
	}

	void ZArray::Initialize()
	{
		type_ = Type::Array;
		SetMutable(true);
		size_ = 0;
	}

	bool ZArray::Get(uc32 index, ZObject *& value)
	{
		if (index >= size_) return false;
		value = array_->Get(index);
		return true;
	}

	void ZArray::Set(uc32 index, ZObject * value)
	{
		if (index >= array_->GetCapacity())
			Realloc(index);
		array_->Set(index, value);
		if (index >= size_)
			size_ = index + 1;
	}

	void ZArray::Push(ZObject * value)
	{
		if (size_ + 1 >= array_->GetCapacity())
			Realloc(size_ + 1);
		array_->Set(size_++, value);
	}

	bool ZArray::Pop(ZObject *& value)
	{
		if (size_ == 0) return false;
		value = array_->Get(size_ - 1);
		Realloc(--size_);
		return true;
	}

	void ZArray::ForEach(std::function<void(ZObject*)> iter)
	{
		for (uc32 i = 0; i < size_; ++i)
			iter(array_->Get(i));
	}

	void ZArray::Realloc(uc32 think)
	{
		if (think >= array_->GetCapacity())
		{
			auto targetCap = array_->GetCapacity() * 2;
			while (targetCap < think) targetCap *= 2;
			auto newArr = ZObjectPointerArray::New(targetCap);
			ZObjectPointerArray::CopyData(newArr, array_, size_);
			array_ = newArr;
		}
		else if (think < array_->GetCapacity() / 4)
		{
			auto newArr = ZObjectPointerArray::New(array_->GetCapacity() / 2);
			ZObjectPointerArray::CopyData(newArr, array_, size_);
			array_ = newArr;
		}
	}

}