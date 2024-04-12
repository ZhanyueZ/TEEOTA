@ECHO OFF
call %~dp0is_config_new.bat %2
if %errorlevel%==0 (
    exit /b 0
)

call %~dp0../../env.bat

:: Environment variable for setting postbuild command with AppliCfg
set "projectdir=%~dp0..\"

:: Enable delayed expansion
setlocal EnableDelayedExpansion

:: Get compiler to update the right linker
IF "%~1"=="" (
    set "keil=1"
    set "iar=1"
    set "cubeide=1"
) ELSE (
    IF "%~1"=="IAR"  set "iar=1"
    IF "%~1"=="STM32CubeIDE" set "cubeide=1"
    IF "%~1"=="Keil" set "keil=1"
)

:start
if not !iar! equ 1 if not !cubeide! equ 1 if not !keil! equ 1 (
    echo Error: Unexpected IDE
    goto :error
)

goto exe:
goto py:
:exe
::line for Windows executable
set "applicfg=%cube_fw_path%\Utilities\PC_Software\ROT_AppliConfig\dist\AppliCfg.exe"
set "python="
if exist %applicfg% (

echo run config Appli with Windows executable
goto update
)
:py
::called if we just want to use AppliCfg python (think to comment "goto exe:")
set "applicfg=%cube_fw_path%\Utilities\PC_Software\ROT_AppliConfig\AppliCfg.py"
set "python=python "

:update
set "AppliCfg=%python%%applicfg%"

:: TPC file with flash layout config information
set general_cfg_file="%projectdir%Config/SM_Config_General.xml"

:: TPC xml sections to configure
set fw_size="Firmware area Size"
set rom_fixed="Rom fixed"
set fw_dwl_offset="Firmware download area offset"

set code_offset="NS appli primary offset"
set code_dwl_offset="NS appli secondary offset"
set code_size="NS appli size"
set reserved_offset="NS reserved area offset"
set reserved_size="NS reserved area size"

set code_offset_module_0="S Module 0 primary offset"
set code_dwl_offset_module_0="S Module 0 secondary offset"
set code_size_module_0="S Module 0 size"

set ram_s_ns_if_size="SRAM Secure/NonSecure interface area size"
set secure_sram_end_address="Secure SRAM End address"

set ns_reserved_area_offset="NS reserved area offset"
set ns_reserved_area_size="NS reserved area size"

:: Application files to configure
set icf_file="%sm_ns_app_boot_path_project%/EWARM/stm32h573xx_flash.icf"
set sct_file="%sm_ns_app_boot_path_project%/MDK-ARM/stm32h5xx_app.sct"
set ld_file="%sm_ns_app_boot_path_project%/STM32CubeIDE/STM32H573IIKXQ_FLASH.ld"
set code_image_file="%projectdir%Images\SM_Code_Image.xml"
set code_image_bin_file="%projectdir%Images\SM_Code_Image_bin.xml"

:: Sizes
set SECTOR_SIZE=0x2000
set MODULE_HEADER_SIZE=0x20
set TRAILER_MAX_SIZE=0x800

:: ================================================ Updating Application files ===============================================

:: Updating Linker files
if !iar!==1 (
%AppliCfg% linker -xml %general_cfg_file% -nxml %code_size% -n CODE_SIZE %icf_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %code_offset% -n CODE_OFFSET %icf_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %ram_s_ns_if_size% -n RAM_S_NS_IF_SIZE %icf_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %secure_sram_end_address% -n RAM_S_END -e "val1-0x10000000" %icf_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %ns_reserved_area_offset% -n RESERVED_AREA_OFFSET %icf_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %ns_reserved_area_size% -n RESERVED_AREA_SIZE %icf_file% --vb
if !errorlevel! neq 0 goto :error
)

if !keil!==1 (
%AppliCfg% definevalue -xml %general_cfg_file% -nxml %code_size% -n CODE_SIZE %sct_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% definevalue -xml %general_cfg_file% -nxml %code_offset% -n CODE_OFFSET %sct_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% definevalue -xml %general_cfg_file% -nxml %ram_s_ns_if_size% -n RAM_S_NS_IF_SIZE %sct_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% definevalue -xml %general_cfg_file% -nxml %secure_sram_end_address% -n RAM_S_END -e "val1-0x10000000" %sct_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% definevalue -xml %general_cfg_file% -nxml %ns_reserved_area_offset% -n RESERVED_AREA_OFFSET %sct_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% definevalue -xml %general_cfg_file% -nxml %ns_reserved_area_size% -n RESERVED_AREA_SIZE %sct_file% --vb
if !errorlevel! neq 0 goto :error
)

if !cubeide!==1 (
%AppliCfg% linker -xml %general_cfg_file% -nxml %code_size% -n CODE_SIZE %ld_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %code_offset% -n CODE_OFFSET %ld_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %ram_s_ns_if_size% -n RAM_S_NS_IF_SIZE %ld_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %secure_sram_end_address% -n RAM_S_END -e "val1-0x10000000" %ld_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %ns_reserved_area_offset% -n RESERVED_AREA_OFFSET %ld_file% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% linker -xml %general_cfg_file% -nxml %ns_reserved_area_size% -n RESERVED_AREA_SIZE %ld_file% --vb
if !errorlevel! neq 0 goto :error
)

:: ================================================ Images xml processing ===================================
:: Copy image xml of appli to project
set code_image_file_project=%sm_ns_app_boot_path_project%Images\SM_Code_Image.xml
set code_image_bin_file_project=%sm_ns_app_boot_path_project%Images\SM_Code_Image_bin.xml

echo %code_image_file% %code_image_file_project%

copy %code_image_file% %code_image_file_project%
copy %code_image_bin_file% %code_image_bin_file_project%

for %%I in ("%code_image_file_project%") do set image_dir_path=%%~dpI

for /f "delims=" %%a in ('%~dp0compute_rel_path.bat %~dp0..\Config %image_dir_path%') do set "resolvedPath=./%%a"

call %~dp0update_xml.bat %code_image_file_project% %resolvedPath%/SM_Config_Keys.xml
call %~dp0update_xml.bat %code_image_bin_file_project% %resolvedPath%/SM_Config_Keys.xml

:: Update TPC image xml of appli postbuild command
%AppliCfg% xmlval -xml %general_cfg_file% -nxml %code_size% -n %fw_size% -e "val1*%SECTOR_SIZE%" %code_image_file_project% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% xmlval -xml %general_cfg_file% -nxml %code_offset% -n %rom_fixed% -e "(val1*%SECTOR_SIZE%)+0x8000000" %code_image_file_project% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% xmlval -xml %general_cfg_file% -nxml %code_dwl_offset% -n %fw_dwl_offset% -e "(val1*%SECTOR_SIZE%)+0x8000000" %code_image_file_project% --vb
if !errorlevel! neq 0 goto :error

%AppliCfg% xmlval -xml %general_cfg_file% -nxml %code_size% -n %fw_size% -e "val1*%SECTOR_SIZE%" %code_image_bin_file_project% --vb
if !errorlevel! neq 0 goto :error
%AppliCfg% xmlval -xml %general_cfg_file% -nxml %code_offset% -n %rom_fixed% -e "(val1*%SECTOR_SIZE%)+0x8000000" %code_image_bin_file_project% --vb
if !errorlevel! neq 0 goto :error

:: ============================================================= End functions ===================================================
:: All the steps were executed correctly
echo        Successful application update according to flash layout
exit /b 0

:: Error when script is executed
:error
echo        Error, update_nsapp_setup.bat script aborted 
exit /b 1
