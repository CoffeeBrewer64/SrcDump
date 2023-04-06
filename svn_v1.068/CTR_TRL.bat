@echo off

REM ************************************************************
REM * CTR SDK - Environment 
REM ************************************************************
REM *
REM * Please specify your installation paths here:
REM *
REM ************************************************************

set CTRSDK_ROOT=%cd%\env\SDK\CTR_SDK
set NW4C_ROOT=%cd%\env\NintendoWare\CTR
set CYGWIN_ROOT=D:\cygwin
set CTRSDK_RVCT_VER=41
SET PATH=%CTRSDK_ROOT%\tools\CommandLineTools;%PATH%;%
%CYGWIN_ROOT%\cygwin.bat
pause