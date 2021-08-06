host_build {
    QT_CPU_FEATURES.x86_64 = mmx sse sse2
} else {
    QT_CPU_FEATURES.mips = 
}
QT.global_private.enabled_features = alloca_h alloca dlopen gui libudev network posix_fallocate reduce_exports relocatable sql system-zlib testlib widgets xml
QT.global_private.disabled_features = sse2 alloca_malloc_h android-style-assets avx2 private_tests dbus dbus-linked gc_binaries intelcet reduce_relocations release_tools stack-protector-strong zstd
PKG_CONFIG_EXECUTABLE = /bin/pkg-config
QMAKE_LIBS_LIBDL = 
QMAKE_LIBS_LIBUDEV = -ludev
QT_COORD_TYPE = double
QMAKE_LIBS_ZLIB = -lz
CONFIG -= precompile_header
CONFIG += cross_compile compile_examples enable_new_dtags largefile
QT_BUILD_PARTS += libs
QT_HOST_CFLAGS_DBUS += -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include
