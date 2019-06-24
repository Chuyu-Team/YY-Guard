#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef __YY_GUARD_INCLUDE
#define __YY_GUARD_INCLUDE

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>







EXTERN_C_START

//C API

/*
Unicode版，优先从System32目录加载依赖项

如果 lpLibFileName 是一个相对路径，那么此函数会从 System32 加载 dll 以及相关依赖项。
如果 lpLibFileName 是一个绝对路径，那么此函数会从 调用者传入的绝对路径加载 dll，但是相关依赖项依然只从 System32加载。


示例：

背景知识：wimgapi.dll依赖 version.dll，具体自行去System32，用Depend工具查看wimgapi.dll的导入表。


//从 C:\Windows\System32 目录加载 wimgapi.dll 以及它的依赖项，比如 version.dll。如果不用 YY_LoadLibraryFormSystem32W，那么极有可能发生 wimgapi.dll 或者 version.dll 劫持。
YY_LoadLibraryFormSystem32W(L"wimgapi.dll");


//从 D:\Dism++ 目录加载 wimgapi.dll，但是从 System32 加载它的依赖项，比如 version.dll。如果不用 YY_LoadLibraryFormSystem32W，那么极有可能发生version.dll 劫持。
YY_LoadLibraryFormSystem32W(L"D:\\Dism++\\wimgapi.dll");
*/
HMODULE
__fastcall
YY_LoadLibraryFormSystem32W(
	LPCWSTR lpLibFileName
	);


//ANSI版，优先从System32目录加载依赖项，使用方式同 YY_LoadLibraryFormSystem32W
HMODULE
__fastcall
YY_LoadLibraryFormSystem32A(
	LPCSTR lpLibFileName
	);


EXTERN_C_END




#ifdef __cplusplus

//C++ API

namespace YY
{
	//Unicode版，优先从System32目录加载依赖项，使用方式同 YY_LoadLibraryFormSystem32W
	__inline
	HMODULE
	__fastcall
	LoadLibraryFormSystem32(
		LPCWSTR lpLibFileName
		)
	{
		return YY_LoadLibraryFormSystem32W(lpLibFileName);
	}


	//ANSI版，优先从System32目录加载依赖项，使用方式同 YY_LoadLibraryFormSystem32W
	__inline
	HMODULE
	__fastcall
	LoadLibraryFormSystem32(
		LPCSTR lpLibFileName
		)
	{
		return YY_LoadLibraryFormSystem32A(lpLibFileName);
	}
}

#endif //!__cplusplus

#endif //!__YY_GUARD_INCLUDE