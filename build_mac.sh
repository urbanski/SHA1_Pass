# Static build on OSX 10.6

g++ -Os SHA1_Pass.cpp `/Users/dan/Downloads/wxWidgets-2.8.12/wx-config --static=yes --libs` \
`/Users/dan/Downloads/wxWidgets-2.8.12/wx-config --static=yes --cxxflags` \
-o SHA1_Pass \
/usr/lib/libcryptopp.a

strip SHA1_Pass

./upx --best SHA1_Pass
