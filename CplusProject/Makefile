CXX		:= -c++

CXXFLAGS := -pedantic-errors -Wall -Wextra -pthread
LDFFLAGS := -L/usr/lib -lstd++ -lm
BUILD := ./build
OBJ_DIR := $(BUILD)/objects
APP_DIR := $(BUILD)/apps
TARGET := main
HEADER := include/lib.h
INCLUDE := -Iinclude/
SRC_DIR := ./src
SRC      := $(wildcard src/*.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)
.PHONY: all build clean debug release
build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
debug: CXXFLAGS += -DDEBUG -g
debug: all
release: CXXFLAGS += -O2
release: all
clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
