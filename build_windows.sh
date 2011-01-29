#!/bin/sh

# Complie and link on Windows XP, Vista or 7 using mingw/msys:

# optional
windres gui.rc -o gui.o

g++ -static -Os gui.o `fltk-config --cxxflags` SHA1_Pass.cpp `fltk-config --ldflags`  -o SHA1_Pass.exe \
-IC:/msys/1.0/include/cryptopp/ \
c://MinGW/lib/libws2_32.a \
c://msys/1.0/lib/libcryptopp.a

# optional
strip -s SHA1_Pass.exe
upx SHA1_Pass.exe
