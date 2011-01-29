#!/bin/sh

# Ubuntu Linux
g++ -Os -Wall `fltk-config --cxxflags` SHA1_Pass.cpp `fltk-config --ldstaticflags` -o SHA1_Pass \
/usr/lib/libfltk.a \
/usr/lib/libfltk_forms.a \
/usr/lib/libfltk_gl.a \
/usr/lib/libfltk_images.a \
/usr/lib/libcrypto++.a

# Optional
strip SHA1_Pass-Debian-Mint-Ubuntu
upx SHA1_Pass-Debian-Mint-Ubuntu





