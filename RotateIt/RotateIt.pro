# Add more folders to ship with the application, here
CONFIG(debug, debug|release) {
    folder_01.source = qml
    folder_01.target = qml
    DEPLOYMENTFOLDERS = folder_01
}

include(exiv2/exiv2.pri)

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

#QT += opengl

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

symbian {
    VERSION = 0.1.0
    TARGET.EPOCHEAPSIZE = 0x00001000 0x1FFFFFFF
    ICON = RotateIt.svg

    extended_version {
        TARGET.UID3 = 0xE39F1FBD
        TARGET = Rotate_It_Extended
        TARGET.CAPABILITY += WriteDeviceData \ # Use for LMGFetch (fetch files from gallery)

        # Use for LMGFetch (fetch files from gallery)
        LIBS += -lmgfetch -lbafl
        DEFINES += MG_FETCH_ENABLED
    }
    else {
        TARGET = Rotate_It
        TARGET.UID3 = 0xE39F1FBE
        DEFINES += MG_FETCH_DISABLED
    }

    TARGET.CAPABILITY += NetworkServices # Links in QML
    LIBS += -lhwrmvibraclient

    vendorinfo = \
        "%{\"Vitalii Shunkov\"}" \
        ":\"Vitalii Shunkov\""

    my_deployment.pkg_prerules = vendorinfo
    DEPLOYMENT += my_deployment
    DEPLOYMENT.display_name += Rotate It!

    SOURCES += src/Symbian/xqvibra_p.cpp \
        src/Symbian/xqvibra.cpp \

    HEADERS += src/Symbian/xqvibra_p.h \
        src/Symbian/xqvibra.h \
}

simulator {
    DEFINES += Q_OS_SYMBIAN_SIMULATOR
    DEFINES += MG_FETCH_DISABLED

    LIBS += -lpsapi -lws2_32 # For exiv2

    SOURCES += src/Symbian_simulator/emptyvibra.cpp
    HEADERS += src/Symbian_simulator/emptyvibra.h
}

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += src/vibra.cpp \
    src/settings.cpp \
    src/process.cpp \
    src/main.cpp \
    src/imageview.cpp \
    src/imagefetcher.cpp \
    src/engine.cpp \
    src/exiftools.cpp \
    src/rotator.cpp \
    src/resizer.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += src/vibra.h \
    src/settings.h \
    src/process.h \
    src/imageview.h \
    src/imagefetcher.h \
    src/engine.h \
    src/exiftools.h \
    src/rotator.h \
    src/resizer.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    exiv2/exiv2.pri
