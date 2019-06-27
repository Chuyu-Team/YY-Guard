@echo off
setlocal

pushd "%~dp0.."

if "%Platform%"=="" set Platform=x86


call:Build%Platform%


popd

goto:eof

:: BuildObj YY_Thunks_for_Vista.obj NTDDI_WIN6
:BuildObj
cl /O1 /Os /Oi /GS- /arch:IA32 /Z7 /MT /Fo"objs\\%Platform%\\%1" /Zl /c /D "NDEBUG" /D "__YY_GUARD_MIN_SUPPORT=%2" "%~dp0delayhlp.cpp"

LibMaker.exe FixObj "%~dp0..\\objs\\%Platform%\\%1" /WeakExternFix:__pfnDliNotifyHook2=%PointType%
LibMaker.exe FixObj "%~dp0..\\objs\\%Platform%\\%1" /WeakExternFix:__pfnDliFailureHook2=%PointType%

goto:eof

:Buildx86
set PointType=4
call:BuildObj YY_Guard.obj NTDDI_WINXP
goto:eof


:Buildx64
set PointType=8
call:BuildObj YY_Guard.obj NTDDI_WS03SP1
goto:eof

:Buildarm
set PointType=4
call:BuildObj YY_Guard.obj NTDDI_WIN8
goto:eof

:Buildarm64
set PointType=8
call:BuildObj YY_Guard.obj NTDDI_WIN10_RS3
goto:eof