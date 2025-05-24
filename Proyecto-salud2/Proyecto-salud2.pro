QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core gui widgets
INCLUDEPATH += build-Proyecto-salud2-Desktop-Debug

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CSVExporter.cpp \
    DatabaseManager.cpp \
    HealthAnalyzer.cpp \
    User.cpp \
    datos.cpp \
    healthrecord.cpp \
    main.cpp \
    mainwindow.cpp \
    registro.cpp

HEADERS += \
    CSVExporter.h \
    DatabaseManager.h \
    HealthAnalyzer.h \
    User.h \
    datos.h \
    healthrecord.h \
    mainwindow.h \
    registro.h

FORMS += \
    datos.ui \
    mainwindow.ui \
    registro.ui

TRANSLATIONS += \
    Proyecto-salud2_es_CO.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
