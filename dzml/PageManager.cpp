#include "PageManager.h"
#include <cstring>

namespace dzml
{

	PageManager::PageItem::PageItem()
	{
		page_ = std::make_unique<Page>();
		ptr_ = page_->GetData();
		remained_space_ = PAGE_SIZE;
	}

	byte* PageManager::PageItem::MoveForward(uc32 size)
	{
		auto result = ptr_;
		ptr_ += size;
		remained_space_ -= size;
		return result;
	}

	PageManager::PageManager(uc32 page_size, bool extendable):
		extendable_(extendable)
	{
		for (uc32 i = 0; i < page_size; ++i)
		{
			pages_.push_back(PageItem());
		}
	}

	PageManager::PageItem *
		PageManager::FindFitPage(uc32 size)
	{
		for (PageItem & pageItem : pages_)
		{
			if (pageItem.remained_space_ >= size)
				return &pageItem;
		}
		return nullptr;
	}

	byte * PageManager::Alloc(uc32 size)
	{
		auto pageItem = FindFitPage(size);
		if (pageItem == nullptr)
		{
			if (extendable_)
			{
				auto current_size = pages_.size();
				for (auto i = 0; i < current_size; i++)
					pages_.push_back(PageItem());
				return Alloc(size);
			}
			else
				return nullptr;
		}
		else
			return pageItem->MoveForward(size);
	}

	void PageManager::AdjustSize()
	{
		for (uc32 i = pages_.size() / 4;
			i < pages_.size(); ++i)
		{
			// check if the space is never used
			if (pages_[i].remained_space_ != PAGE_SIZE)
				return;
		}
		pages_.resize(pages_.size() / 2);
	}

}