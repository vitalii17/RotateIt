# Add more folders to ship with the application, here
folder_01.source = qml/RotateIt
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

#QT += opengl

symbian:TARGET.UID3 = 0xE39F1FBD

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

symbian {
    VERSION = 0.1.0
    TARGET.EPOCHEAPSIZE = 0x00001000 0x1FFFFFFF

    TARGET.CAPABILITY += WriteDeviceData \  # Use for LMGFetch (fetch files from gallery)
                         ReadUserData \     # Use for LMGFetch (fetch files from gallery)
                         NetworkServices    # Links in QML
    # Use for LMGFetch (fetch files from gallery)
    LIBS += -lmgfetch -lbafl -lhwrmvibraclient

    vendorinfo = \
        "%{\"Vitalii Shunkov\"}" \
        ":\"Vitalii Shunkov\""

    my_deployment.pkg_prerules = vendorinfo
    DEPLOYMENT += my_deployment
    DEPLOYMENT.display_name += Rotate It!
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
SOURCES += main.cpp \
    imageview.cpp \
    engine.cpp \
    imagefetcher.cpp \
    settings.cpp \
    xqvibra_p.cpp \
    xqvibra.cpp \
    vibra.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    imageview.h \
    engine.h \
    imagefetcher.h \
    settings.h \
    xqvibra_p.h \
    xqvibra.h \
    vibra.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    qml/main.qml \
    qml/CustomToolBar.qml \
    qml/CustomSlider.qml \
    qml/AboutPage.qml
