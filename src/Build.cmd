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

goto:eof

:Buildx86
call:BuildObj YY_Guard.obj NTDDI_WINXP
goto:eof


:Buildx64
call:BuildObj YY_Guard.obj NTDDI_WS03SP1
goto:eof

:Buildarm
call:BuildObj YY_Guard.obj NTDDI_WIN8
goto:eof

:Buildarm64
call:BuildObj YY_Guard.obj NTDDI_WIN10_RS3
goto:eof