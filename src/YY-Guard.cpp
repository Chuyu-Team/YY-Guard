#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#ifndef __YY_GUARD_MIN_SUPPORT

#if defined(_X86_) || defined(_M_IX86)
#define __YY_GUARD_MIN_SUPPORT NTDDI_WINXP
#elif defined(_AMD64_) || defined(_M_AMD64)
#define __YY_GUARD_MIN_SUPPORT NTDDI_WS03SP1
#elif defined(_ARM_) || defined(_M_ARM)
#define __YY_GUARD_MIN_SUPPORT NTDDI_WIN8
#elif defined(_ARM64_) || defined(_M_ARM64)
#define __YY_GUARD_MIN_SUPPORT NTDDI_WIN10_RS3
#else
#error 未知体系！
#endif

#endif


//当存在此宏时，我们尽量直接从导入 ntdll.lib
//#define __YY_GUADR_USING_NTDLL_LIB 1


namespace YY
{
	typedef _Return_type_success_(return >= 0) LONG NTSTATUS;

	typedef struct _UNICODE_STRING {
		USHORT Length;
		USHORT MaximumLength;
		PWSTR  Buffer;
	} UNICODE_STRING, * PUNICODE_STRING;
	typedef const UNICODE_STRING* PCUNICODE_STRING;

	EXTERN_C
	NTSYSAPI
	NTSTATUS
	NTAPI
	LdrLoadDll(
		IN PWCHAR               PathToFile OPTIONAL,
		IN ULONG                Flags OPTIONAL,
		IN PUNICODE_STRING      ModuleFileName,
		OUT HMODULE*            ModuleHandle
		);

	EXTERN_C
	DECLSPEC_IMPORT
	NTSTATUS
	NTAPI
	RtlWow64EnableFsRedirectionEx(
		_In_opt_ PVOID Wow64FsEnableRedirection,
		_Out_    PVOID* OldFsRedirectionLevel
		);

	EXTERN_C
	NTSYSAPI
	ULONG
	NTAPI
	RtlNtStatusToDosError(
		IN NTSTATUS status
		);


#if __YY_GUARD_MIN_SUPPORT < NTDDI_WIN8
	static DWORD SafeLoadStatus = 0;

	/*
	指示 DLL安全加载 是否可用，言下之意就是KB2533623是否安装了。
	Windows 8以及以上系统才原始支持此特性，而Windows 7以及老系统需要动态判断。
	*/
	static
	__forceinline
	BOOL
	__fastcall
	SafeLoadAvailable(
		)
	{
		/*
		这个函数无需保证线程安全。
		0 尚未初始化
		1，支持。
		-1，不支持。
		*/

		if (SafeLoadStatus == 0)
		{
			auto hKerner32 = GetModuleHandleW(L"kernel32");

			SafeLoadStatus = hKerner32 && GetProcAddress(hKerner32, "AddDllDirectory") ? 1 : -1;
		}


		return SafeLoadStatus == 1;
	}
#endif

//同理，以下变量也不用追求什么线程安全，多重复加载几次也没啥的。
#if defined(_X86_) || defined(_M_IX86)
#if __YY_GUARD_MIN_SUPPORT < NTDDI_WS03SP1 || !defined(__YY_GUADR_USING_NTDLL_LIB)
	static decltype(RtlWow64EnableFsRedirectionEx)* pRtlWow64EnableFsRedirectionEx = nullptr;
#endif
#endif

#ifndef __YY_GUADR_USING_NTDLL_LIB
	static decltype(LdrLoadDll)* pLdrLoadDll = nullptr;
	static decltype(RtlNtStatusToDosError)* pRtlNtStatusToDosError = nullptr;
#endif


	extern "C"
	HMODULE
	__fastcall
	YY_LoadLibraryFormSystem32W(
		LPCWSTR lpLibFileName
		)
	{
#if __YY_GUARD_MIN_SUPPORT >= NTDDI_WIN8
		//Windows 8以及更高平台直接支持 LOAD_LIBRARY_SEARCH_SYSTEM32
		return LoadLibraryExW(lpLibFileName, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
#else
		//我们引入 SafeLoadAvailable 动态判断是因为联想一键影音，会导致老系统 LoadLibraryExW 错误代码 变成 ERROR_ACCESS_DENIED，而不是预期的ERROR_INVALID_PARAMETER。
		if (SafeLoadAvailable())
		{
			//如果支持安全加载，那么直接用就可以了。
			return LoadLibraryExW(lpLibFileName, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
		}

		if (lpLibFileName == nullptr || *lpLibFileName == L'\0')
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return nullptr;
		}

#ifdef __YY_GUADR_USING_NTDLL_LIB
	#if __YY_GUARD_MIN_SUPPORT < NTDDI_WS03SP1
		if (pRtlWow64EnableFsRedirectionEx == nullptr)
		{
			if (auto hNtdll = GetModuleHandleW(L"ntdll"))
			{
				const auto pRtlWow64EnableFsRedirectionExTemp = (decltype(RtlWow64EnableFsRedirectionEx)*)GetProcAddress(hNtdll, "RtlWow64EnableFsRedirectionEx");
				pRtlWow64EnableFsRedirectionEx = pRtlWow64EnableFsRedirectionExTemp ? pRtlWow64EnableFsRedirectionExTemp : (decltype(RtlWow64EnableFsRedirectionEx)*)INVALID_HANDLE_VALUE;
			}
			else
			{
				pRtlWow64EnableFsRedirectionEx = (decltype(RtlWow64EnableFsRedirectionEx)*)INVALID_HANDLE_VALUE;
			}
		}
	#endif
#else
		if (pLdrLoadDll == nullptr
#if defined(_X86_) || defined(_M_IX86)
			|| pRtlWow64EnableFsRedirectionEx == nullptr
#endif
			|| pRtlNtStatusToDosError == nullptr)
		{
			if (auto hNtdll = GetModuleHandleW(L"ntdll"))
			{
#if defined(_X86_) || defined(_M_IX86)
				const auto pRtlWow64EnableFsRedirectionExTemp = (decltype(RtlWow64EnableFsRedirectionEx)*)GetProcAddress(hNtdll, "RtlWow64EnableFsRedirectionEx");
				pRtlWow64EnableFsRedirectionEx = pRtlWow64EnableFsRedirectionExTemp ? pRtlWow64EnableFsRedirectionExTemp : (decltype(RtlWow64EnableFsRedirectionEx)*)INVALID_HANDLE_VALUE;
#endif

				const auto pLdrLoadDllTmp = (decltype(LdrLoadDll)*)GetProcAddress(hNtdll,"LdrLoadDll");
				pLdrLoadDll = pLdrLoadDllTmp ? pLdrLoadDllTmp : (decltype(LdrLoadDll)*)INVALID_HANDLE_VALUE;

				const auto pRtlNtStatusToDosErrorTmp = (decltype(RtlNtStatusToDosError)*)GetProcAddress(hNtdll, "RtlNtStatusToDosError");
				pRtlNtStatusToDosError = pRtlNtStatusToDosErrorTmp ? pRtlNtStatusToDosErrorTmp : (decltype(RtlNtStatusToDosError)*)INVALID_HANDLE_VALUE;
			}
			else
			{
#if defined(_X86_) || defined(_M_IX86)
				pRtlWow64EnableFsRedirectionEx = (decltype(RtlWow64EnableFsRedirectionEx)*)INVALID_HANDLE_VALUE;
#endif
				pLdrLoadDll = (decltype(LdrLoadDll)*)INVALID_HANDLE_VALUE;
				pRtlNtStatusToDosError = (decltype(RtlNtStatusToDosError)*)INVALID_HANDLE_VALUE;
			}
		}
		
		if (pLdrLoadDll == INVALID_HANDLE_VALUE)
		{
			//为什么 LdrLoadDll 会不存在？
			return LoadLibraryExW(lpLibFileName, nullptr, 0);
		}
#endif

		UNICODE_STRING ModuleFileName;
		ModuleFileName.Buffer = (PWSTR)lpLibFileName;

		for (; *lpLibFileName; ++lpLibFileName);

		ModuleFileName.Length = (lpLibFileName - ModuleFileName.Buffer) * sizeof(lpLibFileName[0]);
		ModuleFileName.MaximumLength = ModuleFileName.Length + sizeof(lpLibFileName[0]);

		WCHAR szSystem32Path[512];

		auto cchResult = GetSystemDirectoryW(szSystem32Path, __crt_countof(szSystem32Path));

		if (cchResult == 0 || cchResult >= __crt_countof(szSystem32Path))
		{
			//失败或者缓冲区不足则不处理（因为很显然 512 大小都不够？开玩笑……）
			SetLastError(ERROR_FUNCTION_FAILED);
			return nullptr;
		}

#if defined(_X86_) || defined(_M_IX86)
		PVOID OldFsRedirectionLevel;

		/*
		Windows 7 RTM以其以前版本 LoadLibrary内部默认不会关闭重定向。
		为了防止某些线程在关闭重定向的情况下调用API，依然能正常加载相关dll，因此我们在此处恢复重定向。
		*/
		#if defined(__YY_GUADR_USING_NTDLL_LIB) && __YY_GUARD_MIN_SUPPORT >= NTDDI_WS03SP1
		const auto Status = RtlWow64EnableFsRedirectionEx(nullptr, &OldFsRedirectionLevel);
		#else
		const auto Status = pRtlWow64EnableFsRedirectionEx != INVALID_HANDLE_VALUE ? pRtlWow64EnableFsRedirectionEx(nullptr, &OldFsRedirectionLevel) : STATUS_INVALID_PARAMETER;
		#endif
#endif
		

		HMODULE hModule = nullptr;
		const auto LoadDllStatus = pLdrLoadDll(szSystem32Path, 0, &ModuleFileName, &hModule);

#if defined(_X86_) || defined(_M_IX86)
		//将重定向恢复到以前的状态。
		#if defined(__YY_GUADR_USING_NTDLL_LIB) && __YY_GUARD_MIN_SUPPORT >= NTDDI_WS03SP1
		if (Status >= 0)
			RtlWow64EnableFsRedirectionEx(OldFsRedirectionLevel, &OldFsRedirectionLevel)
		#else
		if (Status >= 0 && pRtlWow64EnableFsRedirectionEx)
			pRtlWow64EnableFsRedirectionEx(OldFsRedirectionLevel, &OldFsRedirectionLevel);
		#endif
#endif

		if (LoadDllStatus < 0)
		{
#ifdef __YY_GUADR_USING_NTDLL_LIB
			SetLastError(RtlNtStatusToDosError(LoadDllStatus));
#else
			SetLastError(pRtlNtStatusToDosError != INVALID_HANDLE_VALUE ? pRtlNtStatusToDosError(LoadDllStatus) : LoadDllStatus);
#endif
		}

		return hModule;
#endif
	}


	extern "C"
	HMODULE
	__fastcall
	YY_LoadLibraryFormSystem32A(
		LPCSTR lpLibFileName
		)
	{
#if __YY_GUARD_MIN_SUPPORT >= NTDDI_WIN8
		//Windows 8以及更高平台直接支持 LOAD_LIBRARY_SEARCH_SYSTEM32
		return LoadLibraryExA(lpLibFileName, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
#else
		if (lpLibFileName == nullptr || *lpLibFileName == '\0')
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return nullptr;
		}

		WCHAR szLibFileNameBuffer[512];

		*szLibFileNameBuffer = L'\0';
		auto cchResult = MultiByteToWideChar(AreFileApisANSI() ? CP_THREAD_ACP : CP_OEMCP, MB_ERR_INVALID_CHARS, lpLibFileName, -1, szLibFileNameBuffer, __crt_countof(szLibFileNameBuffer));

		if (cchResult == 0)
		{
			return nullptr;
		}

		return YY_LoadLibraryFormSystem32W(szLibFileNameBuffer);
#endif
	}

	#pragma section(".CRT$XIB",long, read)

	typedef int(__cdecl* _PIFV)(void);


	static int __cdecl InitDefaultDllDirectories()
	{
		//重新调整dll默认搜索路径，把LOAD_LIBRARY_SEARCH_APPLICATION_DIR移除，减少运行时劫持。
#if __YY_GUARD_MIN_SUPPORT >= NTDDI_WIN8
		auto pSetDefaultDllDirectories = SetDefaultDllDirectories;
#else
		auto pSetDefaultDllDirectories = (decltype(SetDefaultDllDirectories)*)GetProcAddress(GetModuleHandleW(L"kernel32"), "SetDefaultDllDirectories");
		if (!pSetDefaultDllDirectories)
		{
			return 0;
		}
#endif

		pSetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32 | LOAD_LIBRARY_SEARCH_USER_DIRS);

		return 0;
	}


	EXTERN_C void* __cdecl YY_GUARD_InitDefaultDllDirectories()
	{
		__declspec(allocate(".CRT$XIB")) static _PIFV InitFV = InitDefaultDllDirectories;

		return &InitFV;
	}
}


