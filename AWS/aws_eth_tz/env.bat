@ECHO OFF
set provisioning_dir=%~dp0../ROT_Provisioning/
call %provisioning_dir%env.bat
set sm_ns_app_boot_path_project=%~dp0
set no_keil=1
set no_ewarm=1