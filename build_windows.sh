# Static Build on Windows XP, Vista or 7

# Some Windows Specific Items
windres gui.rc -o gui.o

g++ -static -Os gui.o SHA1_Pass.cpp `wx-config --static=yes --libs` `wx-config --static=yes --cxxflags` -o SHA1_Pass.exe \
-IC:/mingw/msys/1.0/include/cryptopp/ \
c://mingw/msys/1.0/lib/libcryptopp.a

strip SHA1_Pass.exe

upx --best SHA1_Pass.exe