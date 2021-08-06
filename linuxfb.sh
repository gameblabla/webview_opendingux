#!/bin/sh
export PATH=$PATH:"$PWD/bin"
export QT_QPA_EGLFS_DEPTH=16 
export LD_LIBRARY_PATH="$PWD/lib":$LD_LIBRARY_PATH
export LD_LIBRARY_PATH="$PWD/lib/gstreamer-1.0":$LD_LIBRARY_PATH
export QT_QPA_PLATFORM_PLUGIN_PATH=$PWD/lib/plugins/platforms
export QT_PLUGIN_PATH=$PWD/lib/plugins
export GST_PLUGIN_PATH="$PWD/lib/gstreamer-1.0"
export QT_QPA_EGLFS_ALWAYS_SET_MODE=1
#Eglfs is also an option but slower
export QT_QPA_PLATFORM=linuxfb
export QT_QPA_FB_FORCE_FULLSCREEN=1
export GST_PLUGIN_SCANNER="$PWD/bin/gst-plugin-scanner"
#export QT_QPA_EGLFS_KMS_CONFIG=./file.json
./webview.elf "$1"
