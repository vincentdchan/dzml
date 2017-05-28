#pragma once
#include "dzml.h"
#include "ZObjects.h"
#include "PageManager.h"
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

		std::unique_ptr<PageManager> young_space;
		std::unique_ptr<PageManager> swap_from_space;
		std::unique_ptr<PageManager> swap_to_space;
		std::unique_ptr<PageManager> old_space;

		uc32 allocatedSpace;

		ZObject nil_;

		static GC* one_;
	public:

		static GC* GetOne()
		{
			return one_;
		}

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
			return true;
		}

		ZObject * GetNil();

		inline uc32 GetAllocatedSpace() const
		{
			return allocatedSpace;
		}

		~GC();

	private:
		void SwapFromToSpace();
		byte* Alloc(uc32, bool gc);

	};
}
