
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += \
	-std=c++14

INCLUDEPATH += \
	include

SOURCES += \
	main.cpp

HEADERS += \
	include/static_if/static_if.hpp
