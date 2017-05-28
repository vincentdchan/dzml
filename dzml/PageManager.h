#pragma once
#include "dzml.h"
#include "Page.h"
#include <vector>
#include <memory>
#include <functional>

namespace dzml
{

	class PageManager
	{
	public:

		class PageItem
		{
		public:
			std::unique_ptr<Page> page_;
			byte * ptr_;
			uc32 remained_space_;

			PageItem();

			/**
			 * return the current pointer
			 * and move the pointer forward
			 */
			byte * MoveForward(uc32 size);

		};

	private:
		bool extendable_;
		std::vector<PageItem> pages_;
		PageItem * FindFitPage(uc32);

	public:
		PageManager(uc32 page_size=1, bool extendable = true);
		byte * Alloc(uc32 size);

		/**
		 * After MajorGC, if more than 3/4 spaces is never
		 * used, then shrink the size to 1/2
		 */
		void AdjustSize();

		inline uc32 Size() const
		{
			return static_cast<uc32>(pages_.size());
		}

	};

}
