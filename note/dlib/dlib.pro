TEMPLATE = app
CONFIG += console
CONFIG -= qt
QMAKE_CXXFLAGS +=  -std=c++11

SOURCES += main.cpp \
    DException.cpp \
    Alloc.cpp

HEADERS += \
    Alloc.h \
    DObject.h \
    DException.h \
    DList.h \
    DSingleLinkList.h \
    DDualLinkList.h \
    DString.h \
    DVector.h \
    DArray.h \
    DStack.h \
    DQueue.h \
    Config.h \
    DGenTree.h \
    DSharedPointer.h \
    DBinTree.h \
    DHTTPServer.h

