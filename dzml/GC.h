#pragma once
#include "dzml.h"
#include "ZObjects.h"
#include "PageSpace.h"
#include <memory>

namespace dzml
{
	/**
	* Generational GC
	* Young gen: 1 page
	* Swap Page: 1 page
	* Old Page: 2 page
	*/
	class GC final
	{
	private:

		std::unique_ptr<AllocatablePageSpace> young_space;
		std::unique_ptr<AllocatablePageSpace> swap_space;
		std::unique_ptr<AllocatablePageSpace> old_space;

		uc32 allocatedSpace;
	public:

		static const uc32 PageSize = 0xFFF; // 4k

		GC();
		GC(const GC&) = delete;
		GC& operator=(const GC&) = delete;

		void MinorGC();
		void MajorGC();

		byte* Alloc(uc32);

		/**
		* use the Alloc method to allocate
		* the memory
		* then call the initialize method
		*/
		template<class T>
		bool MakeGCObject(T** ptr)
		{
			byte* base = Alloc(sizeof(T));
			if (base == nullptr) // allocation failed
				return false;
			auto gco = reinterpret_cast<T*>(base);
			gco->Initialize();
			*ptr = gco;
		}

		inline uc32 GetAllocatedSpace() const
		{
			return allocatedSpace;
		}

		~GC();

	private:
		byte* Alloc(uc32, bool gc);

	};
}
