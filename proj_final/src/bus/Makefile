CC      := g++
CCFLAGS := -lsystemc -Wall

INCS := -I$$SYSTEMC_HOME/include -I/simple_bus
LIBS := -L$$SYSTEMC_HOME/lib-linux64
FILES := *.cpp simple_bus/*.cpp

all: main.cpp
	$(CC) $(INCS) $(LIBS) -Wl,-rpath=$$SYSTEMC_HOME/lib-linux64 $(CCFLAGS) -o main $(FILES)

clean:
	rm -rf main traces.vcd
