#include "GC.h"

namespace dzml
{

	GC::GC():
		allocatedSpace(0)
	{
		young_space = std::make_unique<AllocatablePageSpace>(YOUNG_GEN_PAGE_SIZE);
		swap_space = std::make_unique<AllocatablePageSpace>(1);
		old_space = std::make_unique<AllocatablePageSpace>(OLD_GEN_SPACE_SIZE);
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

	void GC::MinorGC()
	{

	}

	void GC::MajorGC()
	{

	}

	GC::~GC()
	{
	}

}