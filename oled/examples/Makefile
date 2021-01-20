prefix := /usr/local

# The recommended compiler flags for the Raspberry Pi
CCFLAGS=-Ofast 
#CCFLAGS=

# define all programs
PROGRAMS = ssd1306_demo ssd1306_demo2 test
#PROGRAMS = ssd1306_demo2
SOURCES = ${PROGRAMS:=.cpp}

all: ${PROGRAMS}

${PROGRAMS}: ${SOURCES}
	g++ ${CCFLAGS} -Wall  -lssd1306 $@.cpp -o $@

clean:
	rm -rf $(PROGRAMS)

install: all
	test -d $(prefix) || mkdir $(prefix)
	test -d $(prefix)/bin || mkdir $(prefix)/bin
	for prog in $(PROGRAMS); do \
	  install -m 0755 $$prog $(prefix)/bin; \
	done

.PHONY: install



