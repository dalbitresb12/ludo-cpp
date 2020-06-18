@echo off

echo INFO: Testing main.cpp...
set "CHECK_TEST=" & for /F "skip=1 delims=" %%H in ('
    2^> nul CertUtil -hashfile main.cpp
') do if not defined CHECK_TEST set "CHECK_TEST=%%H"

if "%CHECK_TEST%"=="" (
    echo ERROR: Could not get hash
) else (
    echo SUCCESS: The hash is %CHECK_TEST%
)

echo INFO: Testing includes\dice.h...
set "CHECK_TEST=" & for /F "skip=1 delims=" %%H in ('
    2^> nul CertUtil -hashfile includes\dice.h
') do if not defined CHECK_TEST set "CHECK_TEST=%%H"

if "%CHECK_TEST%"=="" (
    echo ERROR: Could not get hash
) else (
    echo SUCCESS: The hash is %CHECK_TEST%
)

echo INFO: Testing includes\game.h...
set "CHECK_TEST=" & for /F "skip=1 delims=" %%H in ('
    2^> nul CertUtil -hashfile includes\game.h
') do if not defined CHECK_TEST set "CHECK_TEST=%%H"

if "%CHECK_TEST%"=="" (
    echo ERROR: Could not get hash
) else (
    echo SUCCESS: The hash is %CHECK_TEST%
)

echo INFO: Testing includes\menu.h...
set "CHECK_TEST=" & for /F "skip=1 delims=" %%H in ('
    2^> nul CertUtil -hashfile includes\menu.h
') do if not defined CHECK_TEST set "CHECK_TEST=%%H"

if "%CHECK_TEST%"=="" (
    echo ERROR: Could not get hash
) else (
    echo SUCCESS: The hash is %CHECK_TEST%
)

echo INFO: Testing includes\utils.h...
set "CHECK_TEST=" & for /F "skip=1 delims=" %%H in ('
    2^> nul CertUtil -hashfile includes\utils.h
') do if not defined CHECK_TEST set "CHECK_TEST=%%H"

if "%CHECK_TEST%"=="" (
    echo ERROR: Could not get hash
) else (
    echo SUCCESS: The hash is %CHECK_TEST%
)

pause