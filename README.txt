
Compile Qt5
On the GameKiddy, you would want instead to disable OpenGL altogether.

./configure  -device-option CROSS_COMPILE="/opt/gcw0-toolchain/bin/mipsel-gcw0-linux-uclibc-"  -opensource -confirm-license -no-pch -opengl es2 -no-pch -no-xcb -skip wayland -skip webengine -nomake tests -nomake examples -eglfs -sysroot /opt/gcw0-toolchain/mipsel-gcw0-linux-uclibc/sysroot -device mipsel-gcw0-linux-uclibc-g++ -prefix /usr -no-glib -no-opengles3 -no-openssl -no-icu -no-dbus -release


Compile Qt5 Webkit
On the GameKiddy, make sure to explicitely disable WebGL.

cmake  -DPORT=Qt -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="/opt/gcw0-toolchain/usr/share/buildroot/toolchainfile.cmake" -DENABLE_WEBKIT2=OFF -DENABLE_DEVICE_ORIENTATION=OFF -DENABLE_GEOLOCATION=OFF -DUSE_GSTREAMER=OFF -DUSE_LIBHYPHEN=OFF -DENABLE_SPELLCHECK=OFF -DENABLE_API_TESTS=OFF -DENABLE_PRINT_SUPPORT=OFF -DENABLE_INSPECTOR_UI=OFF -DENABLE_JIT=OFF -DUSE_LIBHYPHEN=OFF -DENABLE_XSLT=OFF -DENABLE_DRAG_SUPPORT=OFF -DENABLE_QT_WEBCHANNEL=OFF ..
