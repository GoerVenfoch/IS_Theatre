QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../Theatre
SOURCES +=  tst_testperformance.cpp \
    ../Theatre/performance.cpp

HEADERS += \
    ../Theatre/performance.h
