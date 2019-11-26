#---------
#
# CppUTest Examples Makefile
#
#----------

#Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE = @
endif

#--- Inputs ----#
COMPONENT_NAME = CanTest
# Sustituir por directorio de cpputest
CPPUTEST_HOME = ~/work/cpputest
CPPUTEST_CFLAGS += -std=c99
CPPUTEST_PEDANTIC_ERRORS = N
CPPUTEST_WARNINGFLAGS = -Wall

CPPUTEST_USE_EXTENSIONS = Y
CPPUTEST_USE_GCOV = Y
CPP_PLATFORM = Gcc

#SRC_DIRS =\
#	../../src/UI

SRC_FILES = ../../src/cansend.c

TEST_SRC_DIRS =\
	./\
	./mocks

INCLUDE_DIRS =\
  .\
  ../../include\
  $(CPPUTEST_HOME)/include

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
