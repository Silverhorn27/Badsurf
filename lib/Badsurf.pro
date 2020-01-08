CONFIG += c++2a

LIBS += -L/path/to/my/lib -lmylib

INCLUDEPATH += include

DEPENDPATH += include

PRE_TARGETDEPS += libbadsurf.so

SOURCES += \
	src/udev/device.cpp \
	src/udev/enumerate.cpp \
	src/udev/udev.cpp \
	src/ata.cpp \
	src/hpa_set.cpp \
	src/scsi.cpp \
	src/utils.cpp \
	src/read_test.cpp \
	src/procedure.cpp \
	src/smart_show.cpp \
	src/badsurflib.cpp \


HEADERS += \
	include/badsurflib/udev/device.cpp \
	include/badsurflib/udev/enumerate.cpp \
	include/badsurflib/udev/udev.cpp \
	include/badsurflib/ata.cpp \
	include/badsurflib/hpa_set.cpp \
	include/badsurflib/scsi.cpp \
	include/badsurflib/utils.cpp \
	include/badsurflib/read_test.cpp \
	include/badsurflib/procedure.cpp \
	include/badsurflib/smart_show.cpp \
	include/badsurflib/badsurflib.cpp \

TARGET = libbadsurf.so
