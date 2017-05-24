#include "PageSpace.h"
#include <cstring>

namespace dzml
{
	PageSpace::PageSpace(uc32 defaultPage)
	{
		for (uc32 i = 0; i < defaultPage; ++i)
		{
			auto _page = new Page();
			pages_.push_back(_page);
		}
	}

	PageSpace::PageSpace(PageSpace&& that)
	{
		pages_ = that.pages_;

		that.pages_.clear();
	}

	Page* PageSpace::AddPage()
	{
		auto _page = new Page();
		pages_.push_back(_page);
		return _page;
	}

	PageSpace::~PageSpace()
	{
		for (auto i = pages_.begin();
			i != pages_.end(); ++i)
		{
			delete *i;
		}
	}

	AllocatablePageSpace::AllocatablePageSpace(uc32 defaultPage):
		PageSpace(defaultPage)
	{
		page_index_ = 0;
		for (auto i = pages_.begin();
			i != pages_.end(); ++i)
		{
			page_pointers_.push_back((*i)->GetData());
		}
	}

	AllocatablePageSpace::AllocatablePageSpace(AllocatablePageSpace&& that)
	{
		PageSpace::PageSpace(std::move(that));
		page_pointers_ = that.page_pointers_;
		page_index_ = that.page_index_;
		that.page_index_ = 0;
	}

	byte* AllocatablePageSpace::Alloc(uc32 size, bool extend)
	{
		if (size >= PAGE_SIZE) return nullptr; // it's impossible

		auto page = pages_[page_index_];
		auto page_ptr = page_pointers_[page_index_];
		if (page->CheckSafe(page_ptr + size))
		{
			auto result = page_ptr;
			page_pointers_[page_index_] += size;
			return result;
		}
		else 
		{
			if (!extend) return nullptr;
			auto new_page_base = AddPage();
			++page_index_;
			page_pointers_.push_back(new_page_base->GetData());
			return Alloc(size); // alloc again
		}
	}

	byte* AllocatablePageSpace::Alloc(uc32 size, byte* src, bool extend)
	{
		auto result = Alloc(size, extend);
		memcpy(result, src, size);
		return result;
	}

	AllocatablePageSpace::~AllocatablePageSpace()
	{

	}

}