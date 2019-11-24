CC		:= g++

MAKEFLAGS := -k

CFLAGS := -O2 -Wall -Wno-parentheses

CPPFLAGS += \
	-Iinclude \
	-DAF_CAN=PF_CAN \
	-DPF_CAN=29 \
	-DSO_RXQ_OVFL=40 \
	-DSCM_TIMESTAMPING_OPT_STATS=54 \
	-D_FILE_OFFSET_BITS=64 \
	-D_GNU_SOURCE

C_FLAGS := -std=c++17 -Wall -Wextra -g

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
LIBS 	+= -lpthread
LIBRARIES	+= -lpthread

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif





all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)
