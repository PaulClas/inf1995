
LIB_DIR = ../../lib_dir
MCU=atmega324pa
PROJECTNAME=robotbaby
PRJSRC= $(wildcard *.cpp)
INC=-I $(LIB_DIR)
LIBS=-L $(LIB_DIR) -l robotbaby
OPTLEVEL=s
AVRDUDE_PROGRAMMERID=usbasp
CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
REMOVE=rm -f
HEXFORMAT=ihex
CFLAGS=-I. -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall -DF_CPU=8000000

CXXFLAGS=-fno-exceptions     

LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

TRG=$(PROJECTNAME).out
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex
CFILES=$(filter %.c, $(PRJSRC))
CPPFILES=$(filter %.cpp, $(PRJSRC))

OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o) 

.PHONY: all install clean 

all: $(TRG)

$(TRG): $(OBJDEPS)
	cd $(LIB_DIR) ; make
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) -lm $(LIBS)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $<
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

-include *.d

%.hex: %.out
	$(OBJCOPY) -j .text -j .data \
		-O $(HEXFORMAT) $< $@

install: $(HEXROMTRG)				
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID)   \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

CLEAN: clean
	cd $(LIB_DIR) ; make clean

clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d

