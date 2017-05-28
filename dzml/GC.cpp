#include "GC.h"

namespace dzml
{

	GC::GC():
		allocatedSpace(0)
	{
		young_space = std::make_unique<PageManager>(2, false);
		swap_from_space = std::make_unique<PageManager>(4, true);
		swap_to_space = std::make_unique<PageManager>(4, true);
		old_space = std::make_unique<PageManager>(4, true);

		one_ = this;
	}

	byte* GC::Alloc(uc32 length)
	{
		return Alloc(length, true);
	}

	byte* GC::Alloc(uc32 length, bool gc)
	{
		byte * result;
		if ((result = young_space->Alloc(length)) == nullptr)
		{
			// not enough space to alloc
			if (gc)
			{
				MinorGC();
				return Alloc(length, false);
			}
			return nullptr;
		}
		return result;
	}

	ZObject * GC::GetNil()
	{
		return &nil_;
	}

	void GC::MinorGC()
	{

	}

	void GC::MajorGC()
	{

	}

	void GC::SwapFromToSpace()
	{
		auto tmp = std::move(swap_from_space);
		swap_from_space = std::move(swap_to_space);
		swap_to_space = std::move(tmp);
	}

	GC::~GC()
	{
	}

}