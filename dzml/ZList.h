#pragma once
#include "dzml.h"
#include "ZObjects.h"

namespace dzml
{

	class ZList;

	class ZListNode : public ZGCObject
	{
	public:

		static ZListNode * New(ZObject * obj, ZListNode * next = nullptr);

		ZObject * value_;
		ZObject * next_; // could be nil or ZListNode
	};

	class ZList : public ZGCObject
	{
	private:
		uc32 length_;
		ZListNode * begin_;

	public:

		// Create a list with a element
		static ZList* New(ZObject * ptr);
		static ZList* Cons(ZObject * newptr, ZList * another);

		void Initialize()
		{
			type_ = Type::List;
		}

		inline uc32 GetLength() const
		{
			return length_;
		}

		inline ZListNode * GetBeginNode()
		{
			return begin_;
		}

		inline ZObject * GetHead()
		{
			return begin_->value_;
		}

		/*
		 * Return a nil or a list;
		 */
		ZObject * GetTail();

	};

}
