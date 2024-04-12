@echo off
set "path1=%~1"
set "path2=%~2"

powershell -Command "& {$root='%path2%';$current='%path1%';$tmp=Get-Location;Set-Location $root; $resolvedPath = Resolve-Path -relative $current;Set-Location $tmp;$resolvedPath.Replace('\', '/')}"