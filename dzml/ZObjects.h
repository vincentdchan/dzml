#pragma once
#include "dzml.h"
#include <cinttypes>

#define DISABLE_STD(NAME) \
	NAME() = delete; \
	NAME(const NAME&) = delete; \
	NAME& operator=(const NAME&) = delete; \
	~NAME() = delete;

#define GC_FORWARDED_MASK  0x1
#define GC_REMEMBERED_MASK  0x2
#define GC_GLOBAL_MASK 0x4
#define GC_MUTATABLE_MASK 0x8

namespace dzml
{
	class ZObject
	{
	public:

		enum class Type : int8_t
		{
			Nil,
			Integer,
			Float,
			Double,
		};

	protected:

		Type type_;

	public:

		void Initialize();

		inline Type GetType() const
		{
			return type_;
		}

		inline bool isNil() const
		{
			return type_ == Type::Nil;
		}

		inline bool isGCObject() const
		{
			return static_cast<uint8_t>(type_) >= static_cast<uint8_t>(Type::Integer);
		}

		ZIntegerObject* toInt();
		ZFloatObject* toFloat();
		ZDoubleObject* toDouble();

		DISABLE_STD(ZObject)

	};

	class ZGCObject : public ZObject
	{
	private:

		/**
		 * All GCObject has a flag byte
		 * 00000000
		 * | AGE  |   0  | MUTATABLE | GLOBAL | Remembered | Forwarded |
		 * | 3bit | 1bit |    1bit   |   1bit |     1bit   |     1bit  |
		 * 
		 * if a ZGCObject is mutatable, then it means that the old
		 * generation could point to the new gen object. Hence, when
		 * the pointers update in the old generation mutatable object,
		 * the GC should log it in the remembered set.
		 * Otherwise, if an object is immutable and it's in the old
		 * generation area, it wouldn't point to the young generation
		 * object forever.
		 *
		 * If an object is global, then it will be global forever,
		 * so we wouldn't collect it.
		 */
		byte flag;
		ZGCObject * forwarding;

	public:

		void Initialize();

		inline bool IsForwarded() const
		{
			return (flag & GC_FORWARDED_MASK) != 0;
		}

		inline bool IsRemembered() const
		{
			return (flag & GC_REMEMBERED_MASK) != 0;
		}

		inline bool IsGlobal() const
		{
			return (flag & GC_GLOBAL_MASK) != 0;
		}

		inline bool IsMutatable() const
		{
			return (flag & GC_MUTATABLE_MASK) != 0;
		}

		inline void SetForwarded(bool bl)
		{
			if (bl)
				flag |= GC_FORWARDED_MASK;
			else
				flag &= (!GC_FORWARDED_MASK);
		}

		inline void SetRemembered(bool bl)
		{
			if (bl)
				flag |= GC_REMEMBERED_MASK;
			else
				flag &= (!GC_REMEMBERED_MASK);
		}

		inline void SetMutatable(bool bl)
		{
			if (bl)
				flag != GC_MUTATABLE_MASK;
			else
				flag &= (!GC_MUTATABLE_MASK);
		}

		inline void SetGlobal(bool bl)
		{
			if (bl)
				flag != GC_GLOBAL_MASK;
			else
				flag &= (!GC_GLOBAL_MASK);
		}

		inline byte GetAge() const
		{
			return flag >> 5;
		}

		inline void SetAge(byte age)
		{
			byte left_bits = flag & 0xF;
			flag = (age << 5) & left_bits;
		}

		inline void IncAge()
		{
			SetAge(GetAge() + 1);
		}

		DISABLE_STD(ZGCObject)
	};

}
