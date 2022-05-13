#! /bin/bash

set -o errexit  # stop on first error
echo "Syntax check started for $0. On any syntax error script will exit"
bash -n $0 # check and exit for syntax errors in script.
echo "Syntax is OK."

BUILD_FOLDER=`pwd`/build

valgrind --leak-check=full --show-reachable=yes ${BUILD_FOLDER}/device-gateway/device-gateway > mem-check-result.txt 2>&1


