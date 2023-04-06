/**
 * @file trlType.h
 * @author Chentian
 * @date 2011.09.06
 * @brief TRL Emulate - Type define
 */
#pragma once

#ifdef TRL_PLATFORM_CTR
	#include <nn.h>
#endif

#ifdef TRL_PLATFORM_PC
	#include <windows.h>
	#define s8	signed char
	#define s16	signed short
	#define	s32	signed int
	#define s64	signed long long int

	#define u8	unsigned char
	#define u16	unsigned short
	#define u32	unsigned int
	#define u64	unsigned long long int

	#define f32	float
	#define f64	double
#endif
