#pragma once
#include "dzml.h"
#include "Page.h"
#include <vector>

namespace dzml
{

	class PageSpace
	{
	protected:
		std::vector<Page*> pages_;

		Page* AddPage();

	public:
		PageSpace(uc32 defaultPage = 0);
		PageSpace(const PageSpace&) = delete;
		PageSpace(PageSpace&&);

		PageSpace& operator=(const PageSpace&) = delete;

		virtual ~PageSpace();
	};

	class AllocatablePageSpace final : public PageSpace
	{
	private:
		std::vector<byte*> page_pointers_;
		uc32 page_index_;

	public:

		AllocatablePageSpace(uc32 defaultPage = 0);
		AllocatablePageSpace(const AllocatablePageSpace&) = delete;
		AllocatablePageSpace(AllocatablePageSpace&&);

		byte * Alloc(uc32 size, bool extend = false);
		byte * Alloc(uc32 size, byte * src, bool extend = false);

		AllocatablePageSpace& operator=(const AllocatablePageSpace&) = delete;

		virtual ~AllocatablePageSpace();

	};

}
