TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS_RELEASE += -O3
SOURCES += \
        ai.cpp \
        main.cpp

HEADERS += \
    ai.h
