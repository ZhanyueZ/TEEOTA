@echo off

if "%~1"=="" (
    echo Usage: %0 [xmlFile] [Name] [node]
    echo.
    echo Example: ./read_xml.bat ../Config/SM_Config_General.xml ^"Secure SRAM Start address^" ^"Data^"
    echo.
    echo Please provide the XML file and new LinkedXML value as arguments.
    exit /b 1
)

if "%~2"=="" (
    echo Usage: %0 [xmlFile] [Name] [node]
    echo.
    echo Example: ./read_xml.bat ../Config/SM_Config_General.xml ^"Secure SRAM Start address^" ^"Data^"
    echo.
    echo Please provide the new LinkedXML value as an argument.
    exit /b 1
)

if "%~3"=="" (
    set node=Param
) else (
    set "node=%~3"
)

set "xmlFile=%~1"
set "xPath=//%node%[Name='%~2']/Value"

powershell -Command ^
  "$xml=[xml](Get-Content '%xmlFile%'); $value=$xml.SelectSingleNode(\"%xPath%\"); Write-Output $value.InnerText"
