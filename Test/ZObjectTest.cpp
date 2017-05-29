#include "stdafx.h"
#include <boost/test/unit_test.hpp>
#include "dzml.h"
#include "ZObjects.h"

using namespace dzml;

#define SET_AND_CHECK(FIELD, VALUE) \
	gcobj->Set##FIELD(VALUE); \
	BOOST_CHECK_EQUAL(gcobj->Get##FIELD(), VALUE);

#define SET_AND_CHECK_BOOL(FIELD, VALUE) \
	gcobj->Set##FIELD(VALUE); \
	BOOST_CHECK_EQUAL(gcobj->Is##FIELD(), VALUE);

BOOST_AUTO_TEST_CASE(PropertyCheck)
{
	byte * space_ = new byte[sizeof(ZGCObject)];
	auto gcobj = reinterpret_cast<ZGCObject *>(space_);
	gcobj->Initialize();

	SET_AND_CHECK(Age, 0);
	SET_AND_CHECK(Age, 1);
	gcobj->SetAge(1);
	gcobj->IncAge();
	BOOST_CHECK_EQUAL(gcobj->GetAge(), 2);

	SET_AND_CHECK_BOOL(Large, true);
	SET_AND_CHECK_BOOL(Large, false);

	SET_AND_CHECK_BOOL(Mutable, true);
	SET_AND_CHECK_BOOL(Mutable, false);

	SET_AND_CHECK_BOOL(Global, true);
	SET_AND_CHECK_BOOL(Global, false);

	SET_AND_CHECK_BOOL(Remembered, true);
	SET_AND_CHECK_BOOL(Remembered, false);

	SET_AND_CHECK_BOOL(Forwarded, true);
	SET_AND_CHECK_BOOL(Forwarded, false);

	SET_AND_CHECK_BOOL(Marked, true);
	SET_AND_CHECK_BOOL(Marked, false);
	delete[] space_;
}
