# Static build on Debian mini i686 and on Ubuntu x6 AMD64

g++ -Os SHA1_Pass.cpp `/home/brad/Downloads/wxWidgets-2.8.12/wx-config --static=yes --libs` \
`/home/brad/Downloads/wxWidgets-2.8.12/wx-config --static=yes --cxxflags` \
-o SHA1_Pass \
/usr/lib/libcryptopp.a

strip --strip-all --remove-section=.comment --remove-section=.note SHA1_Pass

# Breaks statically linked binaries sometimes ???
upx --best SHA1_Pass
