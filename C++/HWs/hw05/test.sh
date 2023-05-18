#!/bin/bash

unzip $1
dir=`basename $1 .zip`
cd dir
qmake
make
debug/hw05
