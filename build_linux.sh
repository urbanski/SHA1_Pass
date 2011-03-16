#!/bin/sh

# Use FLTK 1.3 (not 1.1) otherwise copy and paste may be cumbersome

# Ubuntu x6
g++ -Os -Wall `fltk-config --cxxflags` SHA1_Pass.cpp `fltk-config --ldstaticflags` -o SHA1_Pass-Linux \
/usr/lib/libfltk.a \
/usr/lib/libcrypto++.a

strip SHA1_Pass-Linux
upx SHA1_Pass-Linux

# ------------------------------------------------------------------------------------------------------------------

# Centos5.5 VM
#~ g++ -Os -Wall `fltk-config --cxxflags` SHA1_Pass.cpp `fltk-config --ldstaticflags` -o SHA1_Pass-Centos-Fedora-Redhat \
#~ /usr/local/lib/libfltk.a \
#~ /usr/lib/libcryptopp.a

#~ strip SHA1_Pass-Centos-Fedora-Redhat
#~ upx SHA1_Pass-Centos-Fedora-Redhat

# ------------------------------------------------------------------------------------------------------------------

# Mac OS X 10.6
#~ g++ -Os -Wall `fltk-config --cxxflags` SHA1_Pass.cpp `fltk-config --ldstaticflags` -o SHA1_Pass-Mac-OSX-10.6 \
#~ /usr/local/lib/libfltk.a \
#~ /usr/lib/libcryptopp.a

#~ strip SHA1_Pass-Mac-OSX-10.6
#~ ./upx SHA1_Pass-Mac-OSX-10.6




