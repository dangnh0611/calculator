QT += widgets
CONFIG += c++11
SOURCES += \
        main.cpp \
        class.cpp
HEADERS += \
        class.h
QMAKE_LFLAGS += -no-pie

RESOURCES += \
    res.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

