@echo off
if "%~1"=="" (
    echo Usage: %0 [xmlFile] [newLinkedXML]
    echo.
    echo Please provide the XML file and new LinkedXML value as arguments.
    exit /b 1
)

if "%~2"=="" (
    echo Usage: %0 [xmlFile] [newLinkedXML]
    echo.
    echo Please provide the new LinkedXML value as an argument.
    exit /b 1
)

set "xmlFile=%~1"
set "newLinkedXML=%~2"

powershell -NoProfile -ExecutionPolicy Bypass -Command "$xmlFile='%xmlFile%'; $newLinkedXML='%newLinkedXML%'; $xmlContent = [xml](Get-Content -Path $xmlFile); $node = $xmlContent.SelectSingleNode('//LinkedXML'); $node.'#text' = $newLinkedXML; $xmlContent.Save($xmlFile); Write-Host 'LinkedXML value updated successfully.'"