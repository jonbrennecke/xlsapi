PROJECT = xlsx
CC = gcc
CXX = g++
# CFLAGS = -Wall -pedantic
# CXXFLAGS = -Wall
XLSAPI = xlsapi.cpp xlsworksheet.cpp xlstable.cpp xlsrow.cpp xlscell.cpp sharedstrings.cpp
INCLPATH = ./includes/
FILES = $(addprefix $(INCLPATH)xlsapi/, $(XLSAPI))
OUT = -o $(PROJECT)
MAIN = test.cpp

all: 
	$(CXX) $(CXXFLAGS) $(FILES) $(MAIN) $(OUT)

run:
	./$(PROJECT)

