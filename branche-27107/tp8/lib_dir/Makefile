MCU=atmega324pa
PRJSRC= $(wildcard *.cpp)
OPTLEVEL=s
CC=avr-gcc
AR=avr-ar
ARFLAGS=-crs

REMOVE=rm -f
CFLAGS=-I. -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall -DF_CPU=8000000
CXXFLAGS=-fno-exceptions     

TRG=librobotbaby.a


OBJDEPS= $(PRJSRC:.cpp=.o)
	

.PHONY: all install clean 

all: $(TRG)

$(TRG): $(OBJDEPS)
	$(AR) $(ARFLAGS) $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $<
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

vars:
	@echo "PRJSRC = $(PRJSRC)"
	@echo "OBJDEPS = $(OBJDEPS)"

clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d
