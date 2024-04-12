#!/bin/bash

#RED='\033[0;31m'
#GREEN='\033[0;32m'
#NC='\033[0m' # No Color

error_config()
{
  #printf "${RED}"
  echo "update_nsapp_setup script failed"
  echo "====="
  if [ -z $1 ]; then
  echo "===== Error occurred."
  else
  echo "===== Error occurred. ($1)"
  fi
  echo "====="
  exit 1
}

sucess_config()
{
  #printf "${GREEN}"
  echo "update_nsapp_setup script success"
  printf "${NO}"
  return 0
}

install_cube()
{
  echo "Please get latest version of STM32CubeProgrammer from st.com." 
  error_config "env"
}
#rebuild if 0
compare_date()
{
   if [ ! -e $1 ]; then
     return 0
   fi
   if [ ! -e $2 ]; then
     return 0
   fi
   if [ $(stat -c %Y $1) -le $(stat -c %Y $2) ]; then
      return 0
   else
      return 1
   fi
}

# $1 source
# $2 dest
# $3 new path
update_xml()
{
  if [ "$#" -ne 3 ]; then
    echo "Usage: %0 [source] [dest] [newLinkedXML], given :  $1 , $2, $3"
    error_config "xml arguments"
  fi
  source=$1
  dest=$2
  str=$3
  sed -n '/<McubootFormat>/,/<\/McubootFormat>/p' $source|sed -n '/<GlobalParam>/,/<\/GlobalParam>/p'|sed -n '/<LinkedXML>/','/<\/LinkedXML>/p'>./temp_xml
  ori=$(cat ./temp_xml | sed  's/.*<LinkedXML>\(.*\)<\/LinkedXML>/\1/g' | grep -v '</' | tr -d '\r')
  if [ ! -e $source ]; then
    error_config "xml $source"
  fi
  #transform path in motif
  reso=""
  local i=0
  while [ "$i" -le ${#ori} ]; do
	letter="${ori:$i:1}"
	case $letter in
		'/') reso=$reso"\\/";;
		*) reso=$reso$letter;;
	esac
	i=$(( i + 1 ))
  done
  ress=""
  i=0
  while [ "$i" -le ${#str} ]; do
	letter="${str:$i:1}"
	case $letter in
		'/') ress=$ress"\\/";;
		*) ress=$ress$letter;;
	esac
	i=$(( i + 1 ))
  done
  sed 's/<LinkedXML>'"$reso"'<\/LinkedXML>/<LinkedXML>'"$ress"'<\/LinkedXML>/g' $source | tr -d '\r' >$dest
}

realpath_to() {
    local common path up
    common=${1%/} path=${2%/}/
    while test "${path#"$common"/}" = "$path"; do
        common=${common%/*} up=../$up
    done
    path=$up${path#"$common"/}; path=${path%/}
    printf %s "${path:-.}"
}
##########################
#  update_nsapp_setup.sh
##########################
if [ $# -ne 2 ]; then
  error_config "app arguments"
fi

if [ -z AppliCfg ]; then
  error_config AppliCfg
fi

# Get compiler to update the right linkerfile file
compiler=$1
outputfile=$2

case $compiler in
  "iar" | "IAR")
    linkerfile="$sm_ns_app_boot_path_project/EWARM/stm32h573xx_flash.icf";;
  "keil"|"Keil")
    linkerfile="$sm_ns_app_boot_path_project/MDK-ARM/stm32h5xx_app.sct";;
  "STM32CubeIDE"|"cubeide"|"CUBE_IDE")
    linkerfile="$sm_ns_app_boot_path_project/STM32CubeIDE/STM32H573IIKXQ_FLASH.ld";;
  *)
    error_config Unexpected_IDE
        ;;
esac

if [ -e $provisioning_dir/SM/Binary/SecureManagerPackage.sfi ]; then
  compare_date $outputfile $provisioning_dir/SM/Binary/SecureManagerPackage.sfi
  todate=$?
else
  todate=0
fi

if [ $todate -eq 0 ]; then
  fw_size="Firmware area Size"
  rom_fixed="Rom fixed"
  fw_dwl_offset="Firmware download area offset"

  code_offset="NS appli primary offset"
  code_dwl_offset="NS appli secondary offset"
  code_size="NS appli size"
  reserved_offset="NS reserved area offset"
  reserved_size="NS reserved area size"

  code_offset_module_0="S Module 0 primary offset"
  code_dwl_offset_module_0="S Module 0 secondary offset"
  code_size_module_0="S Module 0 size"

  ram_s_ns_if_size="SRAM Secure/NonSecure interface area size"
  secure_sram_end_address="Secure SRAM End address"

  ns_reserved_area_offset="NS reserved area offset"
  ns_reserved_area_size="NS reserved area size"

  if [ -z $xml_config_gen ]; then
     xml_config_gen="$provisioning_dir/SM/Config/SM_Config_General.xml"
  fi
  
  # Application files to configure
  code_image_file="$provisioning_dir/SM/Images/SM_Code_Image.xml"
  code_image_bin_file="$provisioning_dir/SM/Images/SM_Code_Image_bin.xml"

  # Sizes
  SECTOR_SIZE=0x2000
  MODULE_HEADER_SIZE=0x20
  TRAILER_MAX_SIZE=0x800

  # ================================================ Updating Application files ===============================================

  # Update TPC image xml of appli postbuild command
  echo $AppliCfg xmlval -xml $xml_config_gen -nxml "$code_size" -n "$fw_size" -e "val1*$SECTOR_SIZE" $code_image_file --vb
  $AppliCfg xmlval -xml $xml_config_gen -nxml "$code_size" -n "$fw_size" -e "val1*$SECTOR_SIZE" $code_image_file --vb
  if [ $? -ne 0 ]; then error_config 'img1'; fi
  $AppliCfg xmlval -xml $xml_config_gen -nxml "$code_offset" -n "$rom_fixed" -e "(val1*$SECTOR_SIZE)+0x8000000" $code_image_file --vb
  if [ $? -ne 0 ]; then error_config 'img1a'; fi
  $AppliCfg xmlval -xml $xml_config_gen -nxml "$code_dwl_offset" -n "$fw_dwl_offset" -e "(val1*$SECTOR_SIZE)+0x8000000" $code_image_file --vb
  if [ $? -ne 0 ]; then error_config 'img1b'; fi

  $AppliCfg xmlval -xml $xml_config_gen -nxml "$code_size" -n "$fw_size" -e "val1*$SECTOR_SIZE" $code_image_bin_file --vb
  if [ $? -ne 0 ]; then error_config 'img2'; fi
  $AppliCfg xmlval -xml $xml_config_gen -nxml "$code_offset" -n "$rom_fixed" -e "(val1*$SECTOR_SIZE)+0x8000000" $code_image_bin_file --vb
  if [ $? -ne 0 ]; then error_config 'img2a'; fi

  #Updating Linker files
  case $compiler in
    "iar" | "IAR")
    $AppliCfg linker -xml $xml_config_gen -nxml "$code_size" -n CODE_SIZE $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'iar1'; fi
    $AppliCfg linker -xml $xml_config_gen -nxml "$code_offset" -n CODE_OFFSET $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'iar2'; fi
    $AppliCfg linker -xml $xml_config_gen -nxml "$ram_s_ns_if_size" -n RAM_S_NS_IF_SIZE $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'iar3'; fi
    $AppliCfg linker -xml $xml_config_gen -nxml "$secure_sram_end_address" -n RAM_S_END -e "val1-0x10000000" $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'iar4'; fi
    $AppliCfg linker -xml $xml_config_gen -nxml "$ns_reserved_area_offset" -n RESERVED_AREA_OFFSET $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'iar5'; fi
    $AppliCfg linker -xml $xml_config_gen -nxml "$ns_reserved_area_size" -n RESERVED_AREA_SIZE $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'iar6'; fi
    ;;
    "keil"|"Keil")
    $AppliCfg definevalue -xml $xml_config_gen -nxml "$code_size" -n CODE_SIZE $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'keil1'; fi
    $AppliCfg definevalue -xml ]xml_config_gen -nxml "$code_offset" -n CODE_OFFSET $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'keil2'; fi
    $AppliCfg definevalue -xml $xml_config_gen -nxml "$ram_s_ns_if_size" -n RAM_S_NS_IF_SIZE $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'keil3'; fi
    $AppliCfg definevalue -xml ]xml_config_gen -nxml "$secure_sram_end_address" -n RAM_S_END -e "val1-0x10000000" $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'keil4'; fi
    $AppliCfg definevalue -xml $xml_config_gen -nxml "$ns_reserved_area_offset" -n RESERVED_AREA_OFFSET $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'keil5'; fi
    $AppliCfg definevalue -xml $xml_config_gen -nxml "$ns_reserved_area_size" -n RESERVED_AREA_SIZE $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'keil6'; fi
    ;;
    "STM32CubeIDE"|"cubeide")
    $AppliCfg linker -xml $xml_config_gen -nxml "$code_size" -n CODE_SIZE $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'cube1'; fi
    $AppliCfg linker -xml $xml_config_gen -nxml "$code_offset" -n CODE_OFFSET $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'cube2'; fi
    $AppliCfg linker -xml $xml_config_gen -nxml "$ram_s_ns_if_size" -n RAM_S_NS_IF_SIZE $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'cube3'; fi
    $AppliCfg linker -xml $xml_config_gen -nxml "$secure_sram_end_address" -n RAM_S_END -e "val1-0x10000000" $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'cube4'; fi
    $AppliCfg linker -xml $xml_config_gen -nxml "$ns_reserved_area_offset" -n RESERVED_AREA_OFFSET $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'cube5'; fi
    $AppliCfg linker -xml $xml_config_gen -nxml "$ns_reserved_area_size" -n RESERVED_AREA_SIZE $linkerfile --vb
    if [ $? -ne 0 ]; then error_config 'cube6'; fi
    ;;
  esac

  # ================================================ Specific update for SMAK_Appli example ===================================
  code_image_file_project=$sm_ns_app_boot_path_project/Images/SM_Code_Image.xml
  code_image_bin_file_project=$sm_ns_app_boot_path_project/Images/SM_Code_Image_bin.xml

  echo copy xml files to project
  compute_rel_path=$(realpath_to "$sm_ns_app_boot_path_project/Images/" "$provisioning_dir/SM/Config/")
  
  update_xml $code_image_file $code_image_file_project "$compute_rel_path/SM_Config_Keys.xml"
  update_xml $code_image_bin_file $code_image_bin_file_project "$compute_rel_path/SM_Config_Keys.xml"
fi
sucess_config
