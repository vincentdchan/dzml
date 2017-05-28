#pragma once
#include <cinttypes>

// 8k page
#define PAGE_SIZE (4* 1024 * 2)
#define YOUNG_GEN_PAGE_SIZE 1
#define OLD_GEN_SPACE_SIZE 2
#define OLD_AGE 3
#define ARRAY_DEFAULT_SIZE 32

typedef uint32_t uc32;
typedef uint16_t uc16;
typedef unsigned char byte;

#define DEF_CAST(TYPE) \
	static TYPE * Cast(ZObject* ptr) \
	{ \
		return reinterpret_cast<TYPE *> (ptr); \
	}
