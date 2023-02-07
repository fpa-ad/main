# Makefile

BINDIR := bin
LIBDIR := lib

PYBINDDIR := extern/pybind11/include

CCFLAGS := -pedantic

CC := g++ -std=c++20 -fPIC

# src/ (declarcaoes de funcoes, de classes + codigo)
# main/ (programas principais)
# bin/ (temporarios, .o, .exe)
# lib/ (bibliotecas) biblioteca FC

# making library
# - static: .a
# - shareable: .so

VPATH = main:src

SRC := $(wildcard src/*.C)
OBJ := $(patsubst %.C, $(BINDIR)/%.o, $(notdir $(SRC)))
INC := $(wildcard src/*.h)

P := $(shell echo `python3-config --extension-suffix`)

.PHONY: all clean lib

lib: $(LIBDIR)/libFC.a

$(LIBDIR)/libFC.a: $(OBJ)
	@echo make lib...
	ar ruv $@ $^
	ranlib $@
    
%.exe: $(BINDIR)/%.o $(LIBDIR)/libFC.a
	@echo compiling and linking...
	$(CC) -I src -I /usr/include/python3.8 -I extern/pybind11/include -I /usr/include/python3.10 -I PYBINDDIR $< -o $(BINDIR)/$@ -L lib -l FC

bin/%.exe: $(BINDIR)/%.o $(LIBDIR)/libFC.a 
	@echo compiling and linking... 
	$(CC) -I src -I extern/pybind11/include -I /usr/include/python3.8 -I /usr/include/python3.10 -I PYBINDDIR -L lib $< -o $@ -l FC

$(BINDIR)/%.o: %.C | $(INC)
	@echo compiling... $<
	$(CC) -I src -I extern/pybind11/include -I /usr/include/python3.8 -I /usr/include/python3.10 -I PYBINDDIR -c $< -o $@

libfc: lib
	g++ -O3 -Wall -shared -std=c++20 -fPIC -I extern/pybind11/include -I /usr/include/python3.8 -I /usr/include/python3.10 -I PYBINDDIR -I src python/wrapper.cpp -o python/libFCpython$(P) -L lib -l FC -Wl,-rpath,.

test: libfc
	python3 python/main.py

######### clean

tilde := $(wildcard */*~) $(wildcard *~)
exe := $(wildcard */*.exe) $(wildcard *.exe)
obj := $(wildcard */*.o) $(wildcard *.o) $(wildcard */*.so) $(wildcard */*.pcm) $(wildcard */*.d)

clean:
	@echo cleaning dir...
	rm -f $(exe) $(obj) $(tilde)
	rm -r output/*
