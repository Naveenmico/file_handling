# Makefile for Record Management System

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Target executable name
TARGET1 = student_record
TARGET2 = student_records.dat

# Source file
SRC = student_record.cpp

all: $(TARGET1)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET1) $(SRC)

clean:
	rm -f $(TARGET1) $(TARGET2)
	

