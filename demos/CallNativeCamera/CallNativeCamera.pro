TEMPLATE = app

QT += qml quick widgets

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

SOURCES += main.cpp \
    src/callnativecamera.cpp \
    src/callnativecamera_p.cpp

HEADERS += \
    src/callnativecamera.h \
    src/callnativecamera_p.h

android {
    QT += androidextras
}

OTHER_FILES += *.md
