QT.gui_private.VERSION = 5.15.2
QT.gui_private.name = QtGui
QT.gui_private.module =
QT.gui_private.libs = $$QT_MODULE_LIB_BASE
QT.gui_private.includes = $$QT_MODULE_INCLUDE_BASE/QtGui/5.15.2 $$QT_MODULE_INCLUDE_BASE/QtGui/5.15.2/QtGui
QT.gui_private.frameworks =
QT.gui_private.depends = core_private gui
QT.gui_private.uses =
QT.gui_private.module_config = v2 internal_module
QT.gui_private.enabled_features = drm_atomic egl eglfs kms eglfs_egldevice eglfs_gbm evdev freetype system-freetype fontconfig gif harfbuzz ico imageio-text-loading jpeg linuxfb multiprocess png raster-64bit system-jpeg system-png tuiotouch vkgen vnc
QT.gui_private.disabled_features = xcb accessibility-atspi-bridge dxguid angle_d3d11_qdtd direct2d direct2d1_1 dxgi direct3d11 direct3d11_1 direct3d9 directfb dxgi1_2 egl_x11 eglfs_brcm eglfs_mali eglfs_openwfd eglfs_rcar eglfs_viv eglfs_viv_wl vsp2 eglfs_vsp2 xlib xcb-xlib eglfs_x11 integrityfb integrityhid libinput libinput-axis-api mtdev system-harfbuzz tslib xkbcommon xkbcommon-x11
QMAKE_INCDIR_OPENGL_ES2 = 
QMAKE_INCDIR_DRM = /opt/gcw0-toolchain/mipsel-gcw0-linux-uclibc/sysroot/usr/include/libdrm /opt/gcw0-toolchain/mipsel-gcw0-linux-uclibc/sysroot/usr/include/valgrind
QMAKE_DEFINES_EGL = EGL_NO_X11
QMAKE_INCDIR_EGL = /opt/gcw0-toolchain/mipsel-gcw0-linux-uclibc/sysroot/usr/include/libdrm /opt/gcw0-toolchain/mipsel-gcw0-linux-uclibc/sysroot/usr/include/valgrind
QMAKE_DEPENDS_FREETYPE_CC = ZLIB
QMAKE_DEPENDS_FREETYPE_LD = ZLIB
QMAKE_INCDIR_FREETYPE = /opt/gcw0-toolchain/mipsel-gcw0-linux-uclibc/sysroot/usr/include/freetype2 /opt/gcw0-toolchain/mipsel-gcw0-linux-uclibc/sysroot/usr/include/libpng16
QMAKE_DEPENDS_FONTCONFIG_CC = FREETYPE
QMAKE_DEPENDS_FONTCONFIG_LD = FREETYPE
QMAKE_INCDIR_FONTCONFIG = /opt/gcw0-toolchain/mipsel-gcw0-linux-uclibc/sysroot/usr/include/uuid
QMAKE_DEPENDS_LIBPNG_CC = ZLIB
QMAKE_DEPENDS_LIBPNG_LD = ZLIB
QMAKE_INCDIR_LIBPNG = /opt/gcw0-toolchain/mipsel-gcw0-linux-uclibc/sysroot/usr/include/libpng16
QMAKE_LIBS_OPENGL_ES2 = -lGLESv2
QMAKE_LIBS_DRM = -ldrm
QMAKE_LIBS_EGL = -lEGL
QMAKE_LIBS_GBM = -lgbm
QMAKE_LIBS_FREETYPE = -lfreetype
QMAKE_LIBS_FONTCONFIG = -lfontconfig
QMAKE_LIBS_LIBJPEG = -ljpeg
QMAKE_LIBS_LIBPNG = -lpng16