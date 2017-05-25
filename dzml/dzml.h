#pragma once
#include <cinttypes>

// 8k page
#define PAGE_SIZE (4* 1024 * 2)
#define YOUNG_GEN_PAGE_SIZE 1
#define OLD_GEN_SPACE_SIZE 2
#define OLD_AGE 3

typedef uint32_t uc32;
typedef unsigned char byte;

namespace dzml
{

	class ZObject;
	class ZGCObject;
	class ZIntegerObject;
	class ZFloatObject;
	class ZDoubleObject;

}
