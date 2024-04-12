#!/bin/bash

if [ -z "$1" ]
then
    echo "Usage: $0 [xmlFile] [Name] [node]"
    echo ""
    echo -e "Example: ./read_xml.sh ../Config/SM_Config_General.xml \"Secure SRAM Start address\" \"Data\""
    echo ""
    echo "Please provide the XML file and new LinkedXML value as arguments."
    exit 1
fi

if [ -z "$2" ]
then
    echo "Usage: $0 [xmlFile] [Name] [node]"
    echo ""
    echo -e "Example: ./read_xml.sh ../Config/SM_Config_General.xml \"Secure SRAM Start address\" \"Data\""
    echo ""
    echo "Please provide the new LinkedXML value as an argument."
    exit 1
fi

if [ -z "$3" ]
then
    node=Param
else
    node="$3"
fi

xmlFile="$1"
name="$2"

paramlist=$(sed -n '/<'$node'>/,/<\/'$node'>/p' $xmlFile)
$line
$elem
for elem in $paramlist
do
  if [ "$elem" == '<'$node'>' ]; then
    # Start of a new line
    line=""
  elif [ "$elem" == '</'$node'>' ]; then
    # End of a line
    if [[ $line == *"<Name>$name</Name>"* ]]; then
      result=$(echo $line|sed  's/.*<Value>\(.*\)<\/Value>.*/\1/g')
      echo $result
      exit 1
    fi
  else
    # Adding the element after the current line
    line="$line $elem"
  fi

done
