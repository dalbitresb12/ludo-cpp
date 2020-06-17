@echo off

goto MAIN

:CHECKFILES
SET UNFOUND=false
echo INFO: Checking existance of project files...

if exist main.cpp (
    echo SUCCESS: main.cpp found
) else (
    set UNFOUND=true
    echo ERROR: main.cpp not found!
)

if exist includes\dice.h (
    echo SUCCESS: includes\dice.h found
) else (
    set UNFOUND=true
    echo ERROR: includes\dice.h not found!
)

if exist includes\game.h (
    echo SUCCESS: includes\game.h found
) else (
    set UNFOUND=true
    echo ERROR: includes\game.h not found!
)

if exist includes\menu.h (
    echo SUCCESS: includes\menu.h found
) else (
    set UNFOUND=true
    echo ERROR: includes\menu.h not found!
)

if exist includes\utils.h (
    echo SUCCESS: includes\utils.h found
) else (
    set UNFOUND=true
    echo ERROR: includes\utils.h not found!
)

if "%UNFOUND%"=="true" (
    echo ERROR: @@@@@@@ MISSING FILES! @@@@@@@
    echo ERROR: The project has some files that are missing.
    echo ERROR: You MUST redownload the project from GitHub:
    echo ERROR: https://github.com/dalbitresb12/ludo-cpp
    echo ERROR: Cannot continue with compilation.
    echo ERROR: @@@@@@@ MISSING FILES! @@@@@@@
    pause
    exit 1
) else (
    echo SUCCESS: All files were found
)
goto CHECKSUMS
exit 0

:CHECKSUMS
set UNMATCH=false
set MAIN_MD5=643c0b391b8b2dc1d17cfabb4676a11a
set DICEH_MD5=89dfcdf596ffd2af97708d7c368eb10e
set GAMEH_MD5=47abe520524ce0b0ee7be1b305034145
set MENUH_MD5=1c0c7631d71985f27e1610e621aedcad
set UTILSH_MD5=acd1c4ac26d55eee9eb6edad95fbca1c

echo INFO: Checking project integrity...

echo INFO: Testing main.cpp...
set "CHECK_TEST=" & for /F "skip=1 delims=" %%H in ('
    2^> nul CertUtil -hashfile main.cpp MD5
') do if not defined CHECK_TEST set "CHECK_TEST=%%H"

if "%CHECK_TEST%"=="" (
    echo WARN: Could not check hashes on main.cpp
    echo WARN: Continuing anyways
) else (
    if "%MAIN_MD5%"=="%CHECK_TEST%" (
        echo SUCCESS: main.cpp hashes match
    ) else (
        set UNMATCH=true
        echo WARN: main.cpp hashes differ!
    )
)

echo INFO: Testing includes\dice.h...
set "CHECK_TEST=" & for /F "skip=1 delims=" %%H in ('
    2^> nul CertUtil -hashfile includes\dice.h MD5
') do if not defined CHECK_TEST set "CHECK_TEST=%%H"

if "%CHECK_TEST%"=="" (
    echo WARN: Could not check hashes on includes\dice.h
    echo WARN: Continuing anyways
) else (
    if "%DICEH_MD5%"=="%CHECK_TEST%" (
        echo SUCCESS: includes\dice.h hashes match
    ) else (
        set UNMATCH=true
        echo WARN: includes\dice.h hashes differ!
    )
)

echo INFO: Testing includes\game.h...
set "CHECK_TEST=" & for /F "skip=1 delims=" %%H in ('
    2^> nul CertUtil -hashfile includes\game.h MD5
') do if not defined CHECK_TEST set "CHECK_TEST=%%H"

if "%CHECK_TEST%"=="" (
    echo WARN: Could not check hashes on includes\game.h
    echo WARN: Continuing anyways
) else (
    if "%GAMEH_MD5%"=="%CHECK_TEST%" (
        echo SUCCESS: includes\game.h hashes match
    ) else (
        set UNMATCH=true
        echo WARN: includes\game.h hashes differ!
    )
)

echo INFO: Testing includes\menu.h...
set "CHECK_TEST=" & for /F "skip=1 delims=" %%H in ('
    2^> nul CertUtil -hashfile includes\menu.h MD5
') do if not defined CHECK_TEST set "CHECK_TEST=%%H"

if "%CHECK_TEST%"=="" (
    echo WARN: Could not check hashes on includes\menu.h
    echo WARN: Continuing anyways
) else (
    if "%MENUH_MD5%"=="%CHECK_TEST%" (
        echo SUCCESS: includes\menu.h hashes match
    ) else (
        set UNMATCH=true
        echo WARN: includes\menu.h hashes differ!
    )
)

echo INFO: Testing includes\utils.h...
set "CHECK_TEST=" & for /F "skip=1 delims=" %%H in ('
    2^> nul CertUtil -hashfile includes\utils.h MD5
') do if not defined CHECK_TEST set "CHECK_TEST=%%H"

if "%CHECK_TEST%"=="" (
    echo WARN: Could not check hashes on includes\utils.h
    echo WARN: Continuing anyways
) else (
    if "%UTILSH_MD5%"=="%CHECK_TEST%" (
        echo SUCCESS: includes\utils.h hashes match
    ) else (
        set UNMATCH=true
        echo WARN: includes\utils.h hashes differ!
    )
)

if "%UNMATCH%"=="true" (
    echo WARN: @@@@@@@ HASHES DIFFER! @@@@@@@
    echo WARN: The project has some files that have been modified.
    echo WARN: It is not guaranteed that compilation will work.
    echo WARN: You should redownload the project from GitHub:
    echo WARN: https://github.com/dalbitresb12/ludo-cpp
    echo WARN: Continuing anyways.
    echo WARN: @@@@@@@ HASHES DIFFER! @@@@@@@
) else (
    echo SUCCESS: All hashes match
)
goto BUILD
exit 0

:BUILD

echo INFO: Starting build...
echo INFO: Set forced includes path to includes\
echo INFO: Set object output path to build\obj\
echo INFO: Set output file to build\main.exe
echo INFO: Set main.cpp as entry file
echo.
cl.exe /clr /Fe /I includes\ /Fo:build\obj\ main.cpp /link user32.lib /out:build\main.exe
echo.
if exist "build\main.exe" (
    echo SUCCESS: Compilation output saved to build\main.exe
) else (
    echo ERROR: Compilation failed
    echo ERROR: Check the output for more details
)
pause
exit 0

:MAIN

echo  __       __  __  ____    _____      
echo /\ \     /\ \/\ \/\  _`\ /\  __`\    
echo \ \ \    \ \ \ \ \ \ \/\ \ \ \/\ \   
echo  \ \ \  __\ \ \ \ \ \ \ \ \ \ \ \ \  
echo   \ \ \L\ \\ \ \_\ \ \ \_\ \ \ \_\ \ 
echo    \ \____/ \ \_____\ \____/\ \_____\
echo     \/___/   \/_____/\/___/  \/_____/
echo.

echo WAIT: Searching for Visual Studio 2019 Build Tools...

for /r "C:\Program Files (x86)\Microsoft Visual Studio\2019\" %%a in (*) do if "%%~nxa"=="VsDevCmd.bat" set p="%%~dpa"

if defined p (
    echo SUCCESS: Visual Studio 2019 Build Tools found
    echo INFO: Using Build Tools on %p%\VsDevCmd.bat
    echo.
    call %p%\VsDevCmd.bat
    echo.
    echo INFO: Starting prechecks...
    if exist "build\main.exe" (
        echo INFO: Cleaning build\ folder...
        del "build\" /s /f /q   
    )
    if not exist "build\" (
        echo INFO: Creating missing folders...
        mkdir build
        mkdir build\obj
    )
    goto CHECKFILES
) else (
    echo ERROR: Build Tools were not found
    echo ERROR: It is mandatory to download the latest version of C++/CLI build tools.
    echo ERROR: Please install them using the following link:
    echo ERROR: https://visualstudio.microsoft.com/visual-cpp-build-tools/
    pause
    exit 1
)