@echo off
setlocal

pushd "%~dp0.."

if "%Platform%"=="" set Platform=x86

set AdditionalOptions=/O1 /Os /Oi /GS- /Z7 /MT /Zl /c /D "NDEBUG"

call:Build%Platform%


popd

goto:eof

:: BuildObj YY_Thunks_for_Vista.obj NTDDI_WIN6
:BuildObj
mkdir "objs\\%Platform%"
cl %AdditionalOptions% /Fo"objs\\%Platform%\\%1"  /D "__YY_GUARD_MIN_SUPPORT=%2" "%~dp0delayhlp.cpp"

LibMaker.exe FixObj "%~dp0..\\objs\\%Platform%\\%1" /WeakExternFix:__pfnDliNotifyHook2=%PointType%
LibMaker.exe FixObj "%~dp0..\\objs\\%Platform%\\%1" /WeakExternFix:__pfnDliFailureHook2=%PointType%

echo "objs\\%Platform%\\%1"
goto:eof

:: BuildLIB YY_Thunks_for_Vista.lib NTDDI_WIN6
:BuildLIB
mkdir "Out\\%Platform%"
mkdir "Libs\\%Platform%"

del "Out\\%Platform%\\*" /q /s

cl %AdditionalOptions% /D "__YY_GUADD_BUILD_LIBS" /D "__YY_GUARD_MIN_SUPPORT=%2" /Fo"Out\\%Platform%\\delayhlp.obj"  "%~dp0delayhlp.cpp"
cl %AdditionalOptions% /Fo"Out\\%Platform%\\pfnDliFailureHook2.obj"  "%~dp0pfnDliFailureHook2.c"
cl %AdditionalOptions% /Fo"Out\\%Platform%\\pfnDliNotifyHook2.obj"  "%~dp0pfnDliNotifyHook2.c"

lib "Out\%Platform%\*.obj" /out:"Libs\%Platform%\%1"

cl %AdditionalOptions% /D "__YY_GUARD_MIN_SUPPORT=%2" /Fo"Out\\%Platform%\\YY-Guard.obj"  "%~dp0YY-Guard.cpp"

lib "Out\%Platform%\YY-Guard.obj" /out:"Libs\%Platform%\YY-Guard.lib"

echo "Libs\%Platform%\%1"

goto:eof

:Buildx86
set PointType=4
set AdditionalOptions=%AdditionalOptions% /arch:IA32

call:BuildObj YY_Guard.obj NTDDI_WINXP
call:BuildLIB delayimp.lib NTDDI_WINXP
goto:eof


:Buildx64
set PointType=8
call:BuildObj YY_Guard.obj NTDDI_WS03SP1
call:BuildLIB delayimp.lib NTDDI_WS03SP1
goto:eof

:Buildarm
set PointType=4
call:BuildObj YY_Guard.obj NTDDI_WIN8
call:BuildLIB delayimp.lib NTDDI_WIN8
goto:eof

:Buildarm64
set PointType=8
call:BuildObj YY_Guard.obj NTDDI_WIN10_RS3
call:BuildLIB delayimp.lib NTDDI_WIN10_RS3
goto:eof