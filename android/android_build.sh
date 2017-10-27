#!/bin/bash
export ANDROID_COMPILER_VERSION=4.9
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export QT_ANDROID_ANT=/usr/bin/ant
export ANDROID_NDK=/home/mishka/.android/android-ndk-r14b
export ANDROID_SDK=/home/mishka/.android/sdk/
export ANDROID_API_LEVEL=16
export CMAKE_PREFIX_PATH=/opt/Qt/5.9.1/android_armv7/lib/cmake

# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
cd $(dirname "$SCRIPT")

mkdir -p ../build_android
cd ../build_android
cmake .. -DCMAKE_TOOLCHAIN_FILE=../3rdparty/qt-android-cmake/toolchain/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release
make -j5

#$ANDROID_SDK/platform-tools/adb install -r ./bin/QtApp-debug.apk

