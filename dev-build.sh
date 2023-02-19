#!/bin/bash

if [ "$YOTTA_GITHUB_AUTHTOKEN" == "" ]; then
  echo "YOTTA_GITHUB_AUTHTOKEN not set"
  exit 1
fi;

export PXT_NODOCKER=1

pxt build --local

cp  ./built/binary.hex /media/sf_Downloads/