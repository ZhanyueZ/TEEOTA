#!/bin/sh -

absolutpath() {
  echo "$(cd "$(dirname "$1")" && pwd)"
}
caller=$(basename $0)
callerpath=$(absolutpath $0)

if [ "$caller" = "postbuild.sh" ]; then
  export provisioning_dir=$(absolutpath "$callerpath/../../ROT_Provisioning/env.sh")
elif [ "$caller" = "prebuild.sh" ] || [ "$caller" = "env.sh" ] || [ "$caller" = "download.sh" ]; then
  export provisioning_dir=$(absolutpath "$callerpath/../ROT_Provisioning/env.sh")
else
  echo "postbuild and prebuild environment"
  exit 1
fi

source $provisioning_dir/env.sh
sm_ns_app_boot_path_project=$callerpath
