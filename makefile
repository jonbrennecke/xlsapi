PROJECT = xlsx
CC = gcc
CXX = g++
# CFLAGS = -Wall -pedantic
# CXXFLAGS = -Wall
MOUSE = mouse.cpp
XLSAPI = xlsapi.cpp xlsworksheet.cpp xlstable.cpp xlsrow.cpp xlscell.cpp sharedstrings.cpp
INCLPATH = ./includes/
FILES = $(addprefix $(INCLPATH)xlsapi/, $(XLSAPI))
FILES += $(addprefix $(INCLPATH)mouse/, $(MOUSE))
OUT = -o $(PROJECT)
MAIN = test.cpp

all: 
	$(CXX) $(CXXFLAGS) $(FILES) $(MAIN) $(OUT)

run:
	./$(PROJECT)

