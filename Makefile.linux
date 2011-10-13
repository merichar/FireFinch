###########################################
# Simple Makefile for Finch
# To run for your program, just change TARGET
#
# Tom Lauwers, tlauwers@finchrobot.com
###########################################

#TARGET=CommandLineFinch
#TARGET=MyProgramName

all: build

CC=gcc
CXX=g++
COBJS=./hid-libusb.o
CPPOBJS=./Finch.o $(TARGET)
#CPPOBJS=./Finch/Finch.o $(TARGET).o
OBJS=$(COBJS) $(CPPOBJS) build
CFLAGS=-I./hidapi -g 
LIBS=`pkg-config libusb-1.0 --libs`


#Copypasta starts here
#CXX   = c++
CPPFLAGS +=     -fno-rtti              \
		-fno-exceptions        \
		-shared  

# Change this to point at your Gecko SDK directory. 
GECKO_SDK_PATH = /usr/lib/xulrunner-devel-6.0/sdk
IDL_PATH = /usr/include/xulrunner-6.0
# GCC only define which allows us to not have to #include mozilla-config 
# in every .cpp file.  If your not using GCC remove this line and add 
# #include "mozilla-config.h" to each of your .cpp files. 
GECKO_CONFIG_INCLUDE = -include mozilla-config.h 

GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR

#GECKO_INCLUDES = -I $(GECKO_SDK_PATH)/include -I $(IDL_PATH)
GECKO_INCLUDES = -I /usr/include/xulrunner-6.0
GECKO_LDFLAGS = -L$(GECKO_SDK_PATH)/lib -L$(GECKO_SDK_PATH)/bin -Wl,-rpath-link,$(GECKO_SDK_PATH)/bin -lxpcomglue_s -lxpcom -lnspr4 -L./ -lhidapi -lhidap32  


FILES = Finch.cpp FinchModule.cpp 

TARGET = Finch.so

#build:
build: 
	
	$(CXX) -Os $(CFLAGS)  -o $(TARGET) $(LIBS) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -I./ $(CPPFLAGS) $(CXXFLAGS) $(FILES) $(GECKO_LDFLAGS)

# chmod +x $(TARGET)
# strip $(TARGET)


.PHONY: clean


