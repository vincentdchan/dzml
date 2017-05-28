#include "stdafx.h"
#include <boost/test/unit_test.hpp>
#include "PageManager.h"

using namespace dzml;

BOOST_AUTO_TEST_CASE(PateItem)
{
	typedef PageManager::PageItem PageItem;

	PageItem pageItem;

	BOOST_CHECK_EQUAL(pageItem.page_->GetData(), pageItem.ptr_);
	BOOST_CHECK_EQUAL(pageItem.remained_space_, PAGE_SIZE);

	auto tmp = pageItem.page_->GetData();
	BOOST_CHECK_EQUAL(tmp, pageItem.MoveForward(16));
	BOOST_CHECK_EQUAL(pageItem.ptr_, (tmp + 16));
}

BOOST_AUTO_TEST_CASE(NotExtend)
{
	PageManager pageManager(2, false);
	BOOST_CHECK_EQUAL(pageManager.Size(), 2);

	auto ptr1 = pageManager.Alloc(PAGE_SIZE - 1);
	auto ptr2 = pageManager.Alloc(PAGE_SIZE - 1);
	auto ptr3 = pageManager.Alloc(PAGE_SIZE - 1);

	BOOST_CHECK(ptr1 != nullptr);
	*ptr1 = '0'; // write to the alloc page
	BOOST_CHECK(ptr2 != nullptr);
	*ptr2 = '0';
	BOOST_CHECK_EQUAL(ptr3, nullptr);
}

BOOST_AUTO_TEST_CASE(Extend)
{
	PageManager pageManager(2, true);

	auto ptr1 = pageManager.Alloc(PAGE_SIZE - 1);
	auto ptr2 = pageManager.Alloc(PAGE_SIZE - 1);
	auto ptr3 = pageManager.Alloc(PAGE_SIZE - 1);

	BOOST_CHECK(ptr1 != nullptr);
	*ptr1 = '0'; // write to the alloc page
	BOOST_CHECK(ptr2 != nullptr);
	*ptr2 = '0';
	BOOST_CHECK(ptr3 != nullptr);
	*ptr3 = '0';
	BOOST_CHECK_EQUAL(pageManager.Size(), 4);
}

BOOST_AUTO_TEST_CASE(AdjustSize)
{
	PageManager pageManager(4, true);

	auto ptr1 = pageManager.Alloc(PAGE_SIZE - 1);

	BOOST_CHECK(ptr1 != nullptr);
	*ptr1 = '0'; // write to the alloc page

	pageManager.AdjustSize();
	BOOST_CHECK_EQUAL(pageManager.Size(), 2);
}
