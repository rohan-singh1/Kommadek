QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    ../include \

INCLUDEPATH += $$PWD/src/

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/csvparser.cpp \
    src/kommatablemodel.cpp \
    src/csvexporter.cpp

HEADERS += \
    include/mainwindow.h \
    include/csvparser.h \
    include/kommatablemodel.h \
    include/csvexporter.h

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

macx:ICON = $${PWD}/resources/icons/macOS/Kommadek_RR.icns      # Rounded Rectangle Icon

# Alternative Icons
# macx:ICON = $${PWD}/resources/icons/macOS/Kommadek_Leaf.icns  # Leaf Shaped Icon
# macx:ICON = $${PWD}/resources/icons/macOS/Kommadek.icns       # Circular Icon


# Rohan was here!
