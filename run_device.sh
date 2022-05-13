#! /bin/bash

set -o errexit  # stop on first error
echo "Syntax check started for $0. On any syntax error script will exit"
bash -n $0 # check and exit for syntax errors in script.
echo "Syntax is OK."

if [ $# -eq 0 ]; then
    echo "                                 "
    echo "Usage: $0 <client name>          "
    exit 0
fi

BUILD_FOLDER=`pwd`/build

pushd ${BUILD_FOLDER}
    ./device/device -b 127.0.0.1 -t $1 -p 250
popd

