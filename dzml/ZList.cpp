#include "ZList.h"
#include "GC.h"

namespace dzml
{

	ZListNode * ZListNode::New(ZObject * obj, ZListNode * next)
	{
		ZListNode * This = nullptr;
		GC::GetOne()->MakeGCObject<ZListNode>(&This);
		This->value_ = obj;
		This->next_ = next == nullptr ? GC::GetOne()->GetNil() : next;
		return This;
	}

	ZList* ZList::New(ZObject * ptr)
	{
		byte * bytes = GC::GetOne()->Alloc(sizeof (ZList));
		ZList * This = reinterpret_cast<ZList*>(bytes);
		This->Initialize();
		This->length_ = 1;

		ZListNode * node = ZListNode::New(ptr);
		This->begin_ = node;
		return This;
	}

	ZList * ZList::Cons(ZObject * newptr, ZList * another)
	{
		ZList * This;
		GC::GetOne()->MakeGCObject<ZList>(&This);
		This->length_ = another->length_ + 1;

		auto node = ZListNode::New(newptr, another->begin_);
		This->begin_ = node;
		return This;
	}

	ZObject * ZList::GetTail()
	{
		if (length_ <= 1)
		{
			return GC::GetOne()->GetNil();
		}
		else
		{
			ZList * Tail;
			GC::GetOne()->MakeGCObject<ZList>(&Tail);
			Tail->length_ = length_ - 1;
			Tail->begin_ = reinterpret_cast<ZListNode*>(begin_->next_);
			return Tail;
		}
	}

}
