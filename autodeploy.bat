@echo off

set log_file=deploy.log
set current_datetime=%date% %time%
(
    echo Log started at: %current_datetime%
) > "%log_file%" 2>&1

echo check Python 
(
    echo Checking if Python is installed...
    python --version
    if %errorlevel% neq 0 (
        echo Python is not installed. Please install Python and try again.
        echo Press Enter to exit.
        pause >nul
        exit 
    ) else (
        echo Python is already installed.
    )
) >> "%log_file%" 2>&1

set file_path="pip_show_platformio_info.txt"
:: Check if PlatformIO is installed
echo check Platform IO
pip show platformio > %file_path% 2>&1
findstr /C:"WARNING: Package(s) not found" %file_path% > nul
if %errorlevel% neq 0 (          
    echo PlatformIO is already installed.
) else (
    echo PlatformIO is not installed. Proceeding with installation...
    pip install platformio
        if %errorlevel% neq 0 (
            echo Error during PlatformIO installation.
            echo Press Enter to exit.
            pause >nul
            exit 
    ) else (
        echo PlatformIO has been successfully installed.
        pip show platformio > %file_path% 2>&1
        type %file_path%
    )
)>> "%log_file%" 2>&1

:: Search the text file for the line containing "Location:"
for /f "delims=: tokens=1,*" %%A in ('findstr /n "Location:" "%file_path%"') do (
set "line_number=%%A"
set "location=%%B"
)

:: Remove leading and trailing spaces from the location
set "location=%location:~10%"

:: Remove "lib\site-packages" from the location and add "Scripts\platformio.exe"
set "platformio_exe_path=%location:lib\site-packages=Scripts\platformio.exe%"
echo %platformio_exe_path%

:: Check if the platformio.exe file exists
if exist "%platformio_exe_path%" (
echo Path to platformio.exe: %platformio_exe_path%
) else (
echo Unable to find platformio.exe file. Check the installation path.
echo Press Enter to exit.
pause >nul
exit
)

:: Path to the Arduino project
set project_path=.\

:: Arduino board type (e.g., uno, nano, etc.)
set board_type=nanoatmega328_oled

:: Port to which Arduino is connected
set port=arduino_port

echo Configuring Arduino project and uploading
(
:: Calling PlatformIO CLI to upload the project
%platformio_exe_path% run --target upload -d %project_path% -e %board_type%
)>> "%log_file%" 2>&1
:: Check if the operation was successful
if %errorlevel% neq 0 (
echo Error uploading the project.
echo Press Enter to exit.
pause >nul
exit
) else (
echo The project has been successfully uploaded to Arduino.
)

echo Press Enter to exit.
pause >nul