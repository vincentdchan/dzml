#pragma once
#include "dzml.h"

namespace dzml
{
	class Page
	{
	private:
		byte * data_;

	public:
		Page();
		Page(const Page&) = delete;
		Page(Page&&);

		inline bool CheckSafe(byte* ptr) const
		{
			return ptr >= data_ && ptr < data_ + PAGE_SIZE;
		}

		inline byte* GetData() const
		{
			return data_;
		}

		Page& operator=(const Page&) = delete;
		~Page();
	};
}
