CC=g++
CFLAGS=-c -Wall -Werror
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=chess

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
    @echo Compiling
	$(CC) $(CFLAGS) $< -o $@
clean:
    rm .f $(OBJECTS) $(EXECUTABLE)	