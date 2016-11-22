#!/bin/sh
mkdir -p libsdl ;
cd libsdl ;
../SDL2-2.0.5/configure --prefix=`pwd`  ;
make ;
make install
