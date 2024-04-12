@echo off
set filePath=%~dp0../Binary/SecureManagerPackage.sfi
set lastRunFile=%1

if not exist %filePath% (
    echo SFI doesn't exists, using default configuration
    exit /b 1
)

for /f %%i in ('powershell -ExecutionPolicy Bypass -File %~dp0is_config_new.ps1 -filePath %filePath% -lastRunFile %lastRunFile% 2^> error.log') do set result=%%i

REM Check the size of error.log
for %%F in (error.log) do (
    if %%~zF gtr 0 (
        echo Error while running is_config_new.ps1 script
        type error.log
        del error.log
        exit -1
    )
    del error.log
)

if %result% == 1 (
    echo Config is updated, project will be updated accordingly
) else (
    echo Config is not updated, no update needed on project
)

exit /b %result%