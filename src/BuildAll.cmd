@echo off


set BuiltInVsWhereExe="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined ProgramFiles(x86) ( set "BuiltInVsWhereExe="%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe"" )

if not exist %BuiltInVsWhereExe% (echo �밲װVS2017���߸��߰汾Ȼ�������& goto:eof )

for /f "tokens=*" %%i in ('%BuiltInVsWhereExe% -latest -prerelease -property installationPath') do ( set LatestVisualStudioRoot=%%i)



setlocal
call "%LatestVisualStudioRoot%\VC\Auxiliary\Build\vcvarsamd64_x86.bat"
call "%~dp0Build.cmd"
endlocal


setlocal
call "%LatestVisualStudioRoot%\VC\Auxiliary\Build\vcvars64.bat"
call "%~dp0Build.cmd"
endlocal


setlocal
call "%LatestVisualStudioRoot%\VC\Auxiliary\Build\vcvarsamd64_arm.bat"
call "%~dp0Build.cmd"
endlocal


setlocal
call "%LatestVisualStudioRoot%\VC\Auxiliary\Build\vcvarsamd64_arm64.bat"
call "%~dp0Build.cmd"
endlocal
