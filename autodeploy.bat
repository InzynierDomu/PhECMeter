@echo off

set log_file=deploy.log
(
    set current_datetime=%date% %time%
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
        exit /b %errorlevel%
    ) else (
        echo Python is already installed.
    )
) >> "%log_file%" 2>&1

set file_path="pip_show_platformio_info.txt"

echo check Platform IO
(
    :: Check if PlatformIO is installed
    echo Checking if PlatformIO is installed...
    pip show platformio > %file_path% 2>&1

    :: Display the content of the file
    echo Displaying the content of the file %file_path%:
    type %file_path%

    findstr /C:"WARNING: Package(s) not found" %file_path%
    if %errorlevel% equ 0 (
        echo PlatformIO is not installed. Proceeding with installation...
        pip install platformio
        if %errorlevel% neq 0 (
            echo Error during PlatformIO installation.
            echo Press Enter to exit.
            pause >nul
            exit /b %errorlevel%
        ) else (
            echo PlatformIO has been successfully installed.
        )
    ) else (
        echo PlatformIO is already installed.
    )
)>> "%log_file%" 2>&1

echo locate Platform IO
(
    :: Create a temporary file with the result of the pip show platformio command
    pip show platformio > %file_path% 2>&1

    :: Display the content of the file
    echo Displaying the content of the file %file_path%:
    type %file_path%

    for /f "delims=: tokens=1,2" %%A in ('findstr /n "Location: " "%file_path%"') do (
  set "line_number=%%A"
  set "location=%%B"
)

:: Remove leading and trailing spaces from the location (optional)
set "location=%location:~10%"

echo Everything after Location: %location% in line %line_number%

    :: Remove "lib\site-packages" from the location and add "Scripts\platformio.exe"
    set "platformio_exe_path=%location:lib\site-packages=Scripts\platformio.exe%"
    echo %platformio_exe_path%

    :: Check if the platformio.exe file exists
    if exist "%platformio_exe_path%" (
    echo Path to platformio.exe: %platformio_exe_path%
    ) else (
    echo Unable to find platformio.exe file. Check the installation path.
    exit
    )
)>> "%log_file%" 2>&1

echo Configuring Arduino project and uploading
(
    echo Setting the path to the Arduino project...
    set project_path=.\

    echo Setting the Arduino board type...
    set board_type=nanoatmega328_oled

    echo Setting the port to which Arduino is connected...
    set port=arduino_port

    echo Calling PlatformIO CLI to upload the project...
    %platformio_exe_path% run --target upload -d %project_path% -e %board_type%

    echo Checking if the operation was successful...
    if %errorlevel% neq 0 (
        echo Error uploading the project.
        exit /b %errorlevel%
    ) else (
        echo The project has been successfully uploaded to Arduino.
    )

    echo Log saved to %log_file%.
) >> "%log_file%" 2>&1

echo Press Enter to exit.
:: Wait for user to press Enter before exiting
pause >nul