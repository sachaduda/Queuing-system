QT -= gui
QT += core

CONFIG += c++11 console
CONFIG -= app_bundle
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


DEFINES += QT_DEPRECATED_WARNINGS
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        application.cpp \
        buffer.cpp \
        device.cpp \
        form.cpp \
        main.cpp \
        source.cpp \
        statistic.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    application.h \
    buffer.h \
    device.h \
    form.h \
    source.h \
    statistic.h \
    step.h

FORMS += \
    form.ui
