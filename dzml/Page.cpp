#include "Page.h"

namespace dzml
{

	Page::Page()
	{
		data_ = new byte[PAGE_SIZE];
	}

	Page::Page(Page&& that)
	{
		data_ = that.data_;
		that.data_ = nullptr;
	}

	Page::~Page()
	{
		if (data_ != nullptr)
		{
			delete[] data_;
		}
	}

}