CC=g++
CFLAGS=-c -Wall -Werror

chessviz: main.o
      $(CC) $(CFLAGS) -o $@ $^

main.o: main.cpp
      $(CC) -c $(CFLAGS) -o $@ $<

clean: 
      rm -rf *.o chessviz
