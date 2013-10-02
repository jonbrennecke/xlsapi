PROJECT = xlsstream_mex

CC = gcc
CXX = g++
CFLAGS = -Wall -pedantic
CXXFLAGS = -fPIC
MATLABROOT = /usr/local/MATLAB/R2013a/
MEX = $(MATLABROOT)bin/mex
MATLAB = 
MEXFLAGS = -cxx
CXXOUT =  
MOUSE = mouse.cpp
XLSAPI = xlsapi.cpp xlsworksheet.cpp xlstable.cpp xlsrow.cpp xlscell.cpp sharedstrings.cpp
INCLPATH = ../
CXXFILES = $(XLSAPI)
CXXOUTFILES = $(subst .cpp,.o, $(XLSAPI))
OPATH = ./build/
OUTDIR = ./mex/
OLIST = $(addprefix $(OPATH),$(subst .cpp,.o, $(XLSAPI)))
MAIN = ./mex/xlsstream_mex.cpp
MAINOBJ = $(subst .cpp,.o,$(MAIN))

all: mex

$(CXXFILES):
	$(CXX) $(CXXFLAGS) -o $(addprefix $(OPATH),$(subst .cpp,.o, $@)) -c $(addprefix $(INCLPATH)xlsapi/, $@) 

main:
	$(CXX) $(CXXFLAGS) -o $(MAINOBJ) -c $(MAIN)

mex:$(CXXFILES) main
	$(MEX) $(MEXFLAGS) -lm $(addprefix $(OPATH),$(subst .cpp,.o, $(CXXFILES))) $(MAINOBJ) -outdir $(OUTDIR) -output $(PROJECT)


