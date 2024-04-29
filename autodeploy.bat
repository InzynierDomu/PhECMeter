
@echo off

:: Check if PlatformIO is installed
pip show platformio > nul 2>&1
if %errorlevel% neq 0 (
echo PlatformIO is not installed. Proceeding with installation...
pip install platformio
if %errorlevel% neq 0 (
echo Error during PlatformIO installation.
exit /b %errorlevel%
) else (
echo PlatformIO has been successfully installed.
)
) else (
echo PlatformIO is already installed.
)

:: Create a temporary file with the result of the pip show platformio command
pip show platformio > pip_show_platformio_info.txt

:: Set the default location of the text file
set file_path="pip_show_platformio_info.txt"

:: Search the text file for the line containing "Location:"
for /f "delims=: tokens=1,*" %%A in ('findstr /n "Location:" "%file_path%"') do (
set "line_number=%%A"
set "location=%%B"
)

:: Remove leading and trailing spaces from the location
set "location=%location:~10%"

:: Output everything after "Location:"
echo Everything after "Location:" in line %line_number%: %location%

:: Remove "lib\site-packages" from the location and add "Scripts\platformio.exe"
set "platformio_exe_path=%location:lib\site-packages=Scripts\platformio.exe%"
echo %platformio_exe_path%

:: Check if the platformio.exe file exists
if exist "%platformio_exe_path%" (
echo Path to platformio.exe: %platformio_exe_path%
) else (
echo Unable to find platformio.exe file. Check the installation path.
)

:: Path to the Arduino project
set project_path=.\

:: Arduino board type (e.g., uno, nano, etc.)
set board_type=nanoatmega328_oled

:: Port to which Arduino is connected
set port=arduino_port

:: Calling PlatformIO CLI to upload the project
%platformio_exe_path% run --target upload -d %project_path% -e %board_type%

:: Check if the operation was successful
if %errorlevel% neq 0 (
echo Error uploading the project.
exit /b %errorlevel%
) else (
echo The project has been successfully uploaded to Arduino.
)