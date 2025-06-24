#define WIN32_LEAN_AND_MEAN


#define UMDF_USING_NTSTATUS

#include <ntstatus.h>
#include <Windows.h>

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;


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

	typedef struct _UNICODE_STRING {
		USHORT Length;
		USHORT MaximumLength;
		PWSTR  Buffer;
	} UNICODE_STRING, * PUNICODE_STRING;
	typedef const UNICODE_STRING* PCUNICODE_STRING;

	typedef struct PEB_LDR_DATA* PPEB_LDR_DATA;

	typedef struct RTL_USER_PROCESS_PARAMETERS* PRTL_USER_PROCESS_PARAMETERS;

	typedef struct _PEB
	{
		BOOLEAN InheritedAddressSpace;
		BOOLEAN ReadImageFileExecOptions;
		BOOLEAN BeingDebugged;
		union
		{
			BOOLEAN BitField;
			struct
			{
				BOOLEAN ImageUsesLargePages : 1;
				BOOLEAN IsProtectedProcess : 1;
				BOOLEAN IsImageDynamicallyRelocated : 1;
				BOOLEAN SkipPatchingUser32Forwarders : 1;
				BOOLEAN IsPackagedProcess : 1;
				BOOLEAN IsAppContainer : 1;
				BOOLEAN IsProtectedProcessLight : 1;
				BOOLEAN IsLongPathAwareProcess : 1;
			};
		};

		HANDLE Mutant;

		PVOID ImageBaseAddress;
		PPEB_LDR_DATA Ldr;
		PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
		PVOID SubSystemData;
		PVOID ProcessHeap;
		PRTL_CRITICAL_SECTION FastPebLock;
		PVOID AtlThunkSListPtr;
		PVOID IFEOKey;
		union
		{
			ULONG CrossProcessFlags;
			struct
			{
				ULONG ProcessInJob : 1;
				ULONG ProcessInitializing : 1;
				ULONG ProcessUsingVEH : 1;
				ULONG ProcessUsingVCH : 1;
				ULONG ProcessUsingFTH : 1;
				ULONG ReservedBits0 : 27;
			};
		};
		union
		{
			PVOID KernelCallbackTable;
			PVOID UserSharedInfoPtr;
		};
		ULONG SystemReserved[1];
		ULONG AtlThunkSListPtr32;
		PVOID ApiSetMap;
		ULONG TlsExpansionCounter;
		PVOID TlsBitmap;
		ULONG TlsBitmapBits[2];
		PVOID ReadOnlySharedMemoryBase;
		PVOID HotpatchInformation;
		PVOID* ReadOnlyStaticServerData;
		PVOID AnsiCodePageData;
		PVOID OemCodePageData;
		PVOID UnicodeCaseTableData;

		ULONG NumberOfProcessors;
		ULONG NtGlobalFlag;

		LARGE_INTEGER CriticalSectionTimeout;
		SIZE_T HeapSegmentReserve;
		SIZE_T HeapSegmentCommit;
		SIZE_T HeapDeCommitTotalFreeThreshold;
		SIZE_T HeapDeCommitFreeBlockThreshold;

		ULONG NumberOfHeaps;
		ULONG MaximumNumberOfHeaps;
		PVOID* ProcessHeaps;

		PVOID GdiSharedHandleTable;
		PVOID ProcessStarterHelper;
		ULONG GdiDCAttributeList;

		PRTL_CRITICAL_SECTION LoaderLock;

		ULONG OSMajorVersion;
		ULONG OSMinorVersion;
		USHORT OSBuildNumber;
		USHORT OSCSDVersion;
		ULONG OSPlatformId;
		ULONG ImageSubsystem;
		ULONG ImageSubsystemMajorVersion;
		ULONG ImageSubsystemMinorVersion;
		ULONG_PTR ActiveProcessAffinityMask;
#ifdef _AMD64_
		ULONG GdiHandleBuffer[60];
#else
		ULONG GdiHandleBuffer[34];
#endif
		PVOID PostProcessInitRoutine;

		PVOID TlsExpansionBitmap;
		ULONG TlsExpansionBitmapBits[32];

		ULONG SessionId;

		ULARGE_INTEGER AppCompatFlags;
		ULARGE_INTEGER AppCompatFlagsUser;
		PVOID pShimData;
		PVOID AppCompatInfo;

		UNICODE_STRING CSDVersion;

		PVOID ActivationContextData;
		PVOID ProcessAssemblyStorageMap;
		PVOID SystemDefaultActivationContextData;
		PVOID SystemAssemblyStorageMap;

		SIZE_T MinimumStackCommit;

		PVOID* FlsCallback;
		LIST_ENTRY FlsListHead;
		PVOID FlsBitmap;
		ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
		ULONG FlsHighIndex;

		PVOID WerRegistrationData;
		PVOID WerShipAssertPtr;
		PVOID pContextData;
		PVOID pImageHeaderHash;
		union
		{
			ULONG TracingFlags;
			struct
			{
				ULONG HeapTracingEnabled : 1;
				ULONG CritSecTracingEnabled : 1;
				ULONG LibLoaderTracingEnabled : 1;
				ULONG SpareTracingBits : 29;
			};
		};
		ULONGLONG CsrServerReadOnlySharedMemoryBase;
		PVOID TppWorkerpListLock;
		LIST_ENTRY TppWorkerpList;
		PVOID WaitOnAddressHashTable[128];
	} PEB, * PPEB;

	typedef struct _CLIENT_ID {
		HANDLE UniqueProcess;
		HANDLE UniqueThread;
	} CLIENT_ID, * PCLIENT_ID;

	typedef struct _GDI_TEB_BATCH
	{
		ULONG Offset;
		HDC hdc;
		ULONG buffer[310];
	} GDI_TEB_BATCH;

	typedef struct TEB_ACTIVE_FRAME* PTEB_ACTIVE_FRAME;

	typedef struct _TEB
	{
		NT_TIB NtTib;

		PVOID EnvironmentPointer;
		CLIENT_ID ClientId;
		PVOID ActiveRpcHandle;
		PVOID ThreadLocalStoragePointer;
		PPEB ProcessEnvironmentBlock;

		ULONG LastErrorValue;
		ULONG CountOfOwnedCriticalSections;
		PVOID CsrClientThread;
		PVOID Win32ThreadInfo;
		ULONG User32Reserved[26];
		ULONG UserReserved[5];
		PVOID WOW32Reserved;
		LCID CurrentLocale;
		ULONG FpSoftwareStatusRegister;
		PVOID ReservedForDebuggerInstrumentation[16];
		PVOID SystemReserved1[37];
		UCHAR WorkingOnBehalfTicket[8];
		NTSTATUS ExceptionCode;

		PVOID ActivationContextStackPointer;
		ULONG_PTR InstrumentationCallbackSp;
		ULONG_PTR InstrumentationCallbackPreviousPc;
		ULONG_PTR InstrumentationCallbackPreviousSp;
		ULONG TxFsContext;

		BOOLEAN InstrumentationCallbackDisabled;
		GDI_TEB_BATCH GdiTebBatch;
		CLIENT_ID RealClientId;
		HANDLE GdiCachedProcessHandle;
		ULONG GdiClientPID;
		ULONG GdiClientTID;
		PVOID GdiThreadLocalInfo;
		ULONG_PTR Win32ClientInfo[62];
		PVOID glDispatchTable[233];
		ULONG_PTR glReserved1[29];
		PVOID glReserved2;
		PVOID glSectionInfo;
		PVOID glSection;
		PVOID glTable;
		PVOID glCurrentRC;
		PVOID glContext;

		NTSTATUS LastStatusValue;
		UNICODE_STRING StaticUnicodeString;
		WCHAR StaticUnicodeBuffer[261];

		PVOID DeallocationStack;
		PVOID TlsSlots[64];
		LIST_ENTRY TlsLinks;

		PVOID Vdm;
		PVOID ReservedForNtRpc;
		PVOID DbgSsReserved[2];

		ULONG HardErrorMode;
#ifdef _WIN64
		PVOID Instrumentation[11];
#else
		PVOID Instrumentation[9];
#endif
		GUID ActivityId;

		PVOID SubProcessTag;
		PVOID PerflibData;
		PVOID EtwTraceData;
		PVOID WinSockData;
		ULONG GdiBatchCount;

		union
		{
			PROCESSOR_NUMBER CurrentIdealProcessor;
			ULONG IdealProcessorValue;
			struct
			{
				UCHAR ReservedPad0;
				UCHAR ReservedPad1;
				UCHAR ReservedPad2;
				UCHAR IdealProcessor;
			};
		};

		ULONG GuaranteedStackBytes;
		PVOID ReservedForPerf;
		PVOID ReservedForOle;
		ULONG WaitingOnLoaderLock;
		PVOID SavedPriorityState;
		ULONG_PTR ReservedForCodeCoverage;
		PVOID ThreadPoolData;
		PVOID* TlsExpansionSlots;
#ifdef _WIN64
		PVOID DeallocationBStore;
		PVOID BStoreLimit;
#endif
		ULONG MuiGeneration;
		ULONG IsImpersonating;
		PVOID NlsCache;
		PVOID pShimData;
		USHORT HeapVirtualAffinity;
		USHORT LowFragHeapDataSlot;
		HANDLE CurrentTransactionHandle;
		PTEB_ACTIVE_FRAME ActiveFrame;
		PVOID FlsData;

		PVOID PreferredLanguages;
		PVOID UserPrefLanguages;
		PVOID MergedPrefLanguages;
		ULONG MuiImpersonation;

		union
		{
			USHORT CrossTebFlags;
			USHORT SpareCrossTebBits : 16;
		};
		union
		{
			USHORT SameTebFlags;
			struct
			{
				USHORT SafeThunkCall : 1;
				USHORT InDebugPrint : 1;
				USHORT HasFiberData : 1;
				USHORT SkipThreadAttach : 1;
				USHORT WerInShipAssertCode : 1;
				USHORT RanProcessInit : 1;
				USHORT ClonedThread : 1;
				USHORT SuppressDebugMsg : 1;
				USHORT DisableUserStackWalk : 1;
				USHORT RtlExceptionAttached : 1;
				USHORT InitialThread : 1;
				USHORT SessionAware : 1;
				USHORT LoadOwner : 1;
				USHORT LoaderWorker : 1;
				USHORT SpareSameTebBits : 2;
			};
		};

		PVOID TxnScopeEnterCallback;
		PVOID TxnScopeExitCallback;
		PVOID TxnScopeContext;
		ULONG LockCount;
		LONG WowTebOffset;
		PVOID ResourceRetValue;
		PVOID ReservedForWdf;
		ULONGLONG ReservedForCrt;
		GUID EffectiveContainerId;
	} TEB, * PTEB;

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

	static __forceinline constexpr UINT64 __fastcall MakeVersion(_In_ UINT16 _uMajor, _In_ UINT16 _uMinor, UINT16 _uBuild = 0, UINT16 _uRevision = 0)
	{
		UINT64 _uVersion = UINT64(_uMajor) << 48;
		_uVersion |= UINT64(_uMinor) << 32;
		_uVersion |= UINT64(_uBuild) << 16;
		_uVersion |= _uRevision;
		return _uVersion;
	}

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
		if (Status >= 0 && pRtlWow64EnableFsRedirectionEx != INVALID_HANDLE_VALUE)
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
		const auto _pPeb = ((YY::TEB*)NtCurrentTeb())->ProcessEnvironmentBlock;

		// Windows 7以下系统，即使安装了KB2533623补丁支持SetDefaultDllDirectories函数了，但是微软的LoadLibraryEx存在Bug
		// 配置SetDefaultDllDirectories后会导致LoadLibraryEx出现无效的参数组合，错误代码为ERROR_INVALID_PARAMETER。典型了gdiplus就会加载失败。
		// 所以，为了避免Windows 7等老系统出现问题，干脆就不启用这个特性了。
		if (MakeVersion(_pPeb->OSMajorVersion, _pPeb->OSMinorVersion) < MakeVersion(6, 2))
		{
			return 0;
		}

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


