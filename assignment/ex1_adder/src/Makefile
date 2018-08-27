CC      := g++
CCFLAGS := -lsystemc -Wall -Wparentheses 

INCS := -I$$SYSTEMC_HOME/include 
LIBS := -L$$SYSTEMC_HOME/lib-linux64
FILES := *.cpp

all: main.cpp
	$(CC) $(INCS) $(LIBS) -Wl,-rpath=$$SYSTEMC_HOME/lib-linux64 $(CCFLAGS) -o main $(FILES)

clean:
	rm -rf main
