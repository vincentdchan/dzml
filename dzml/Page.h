#pragma once
#include "dzml.h"

namespace dzml
{
	/**
	 * the size of a page is fixed, defined
	 * at compile time.
	 */
	class Page
	{
	private:
		byte * data_;

	public:
		Page();
		Page(const Page&) = delete;
		Page(Page&&);

		/**
		 * Check if the pointer is in the page.
		 */
		inline bool CheckSafe(byte* ptr) const
		{
			return ptr >= data_ && ptr < data_ + PAGE_SIZE;
		}

		inline byte* GetData() const
		{
			return data_;
		}

		inline byte&
			operator[](uc32 index)
		{
			return data_[index];
		}

		Page& operator=(const Page&) = delete;
		~Page();
	};

}
