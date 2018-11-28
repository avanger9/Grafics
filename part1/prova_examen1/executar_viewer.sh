#!/bin/bash

drt=$1
if [ ! -d drt ]; then
	mkdir $1
fi

cd $1
/assig/grau-g/viewer