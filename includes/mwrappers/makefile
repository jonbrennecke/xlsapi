#==========================================================
# Makefile install script for GNU Make
# 
# code by Jon Brennecke 
# - brennecke.jonathan@wsu.edu
# - http://github.com/jonbrennecke
#==========================================================

PROJECT = mwrappers
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
MEXDIR = ./mexa64/
OLIST = $(addprefix $(OPATH),$(subst .cpp,.o, $(XLSAPI)))
MAIN = xlsstream xlsrow xlsworksheet mouse

all: $(MAIN)

mouse: $(CXXFILES)
	$(CXX) $(CXXFLAGS) -o $(OPATH)$(subst .cpp,.o,$(MOUSE)) -c $(MOUSEDIR)$(MOUSE)

$(CXXFILES):
	$(CXX) $(CXXFLAGS) -o $(addprefix $(OPATH),$(subst .cpp,.o, $@)) -c $(addprefix $(INCLPATH)xlsapi/, $@) 

$(MAIN): mouse
	$(CXX) $(CXXFLAGS) -o $(addprefix $(OPATH),$(addsuffix _mex.o, $@)) -c $(addprefix $(OUTDIR),$(addsuffix _mex.cpp, $@))
	$(MEX) $(MEXFLAGS) -lm $(addprefix $(OPATH),$(subst .cpp,.o, $(CXXFILES))) $(OPATH)$(subst .cpp,.o,$(MOUSE)) $(MAINOBJ) -outdir $(MEXDIR) -output $(addsuffix _mex, $@)
