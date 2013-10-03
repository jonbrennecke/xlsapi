#########################################################
##
##
##
#########################################################

PROJECT = xlsrow_mex
CC = gcc
CXX = g++
CFLAGS = -Wall -pedantic
CXXFLAGS = -fPIC
MATLABROOT = /usr/local/MATLAB/R2013a/
MEX = $(MATLABROOT)bin/mex
MATLAB = 
MEXFLAGS = -cxx
CXXOUT = 
MOUSEDIR = ../mouse/
MOUSE = mouse.cpp
XLSAPI = xlsapi.cpp xlsworksheet.cpp xlstable.cpp xlsrow.cpp xlscell.cpp sharedstrings.cpp
INCLPATH = ../
CXXFILES = $(XLSAPI)
CXXOUTFILES = $(subst .cpp,.o, $(XLSAPI))
OPATH = ./build/
OUTDIR = ./mex/
OLIST = $(addprefix $(OPATH),$(subst .cpp,.o, $(XLSAPI)))
MAIN = ./mex/xlsrow_mex.cpp
MAINOBJ = $(subst .cpp,.o,$(MAIN))

all: mex

mouse: $(CXXFILES)
	$(CXX) $(CXXFLAGS) -o $(OPATH)$(subst .cpp,.o,$(MOUSE)) -c $(MOUSEDIR)$(MOUSE)

$(CXXFILES):
	$(CXX) $(CXXFLAGS) -o $(addprefix $(OPATH),$(subst .cpp,.o, $@)) -c $(addprefix $(INCLPATH)xlsapi/, $@) 

main: mouse
	$(CXX) $(CXXFLAGS) -o $(MAINOBJ) -c $(MAIN)

mex: main
	$(MEX) $(MEXFLAGS) -lm $(addprefix $(OPATH),$(subst .cpp,.o, $(CXXFILES))) $(OPATH)$(subst .cpp,.o,$(MOUSE)) $(MAINOBJ) -outdir $(OUTDIR) -output $(PROJECT)


