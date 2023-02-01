# Makefile

BINDIR := bin
LIBDIR := lib

CCFLAGS := -pedantic 

CC := g++ -std=c++20

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

.PHONY: all clean lib

lib: $(LIBDIR)/libFC.a

$(LIBDIR)/libFC.a: $(OBJ)
	@echo make lib...
	ar ruv $@ $^
	ranlib $@
    
%.exe: $(BINDIR)/%.o $(LIBDIR)/libFC.a
	@echo compiling and linking...
	$(CC) -I src $< -o $(BINDIR)/$@ -L lib -l FC

bin/%.exe: $(BINDIR)/%.o $(LIBDIR)/libFC.a 
	@echo compiling and linking... 
	$(CC) -I src -L lib $< -o $@ -l FC

$(BINDIR)/%.o: %.C | $(INC)
	@echo compiling... $<
	$(CC) -I src -c $< -o $@


######### clean

tilde := $(wildcard */*~) $(wildcard *~)
exe := $(wildcard */*.exe) $(wildcard *.exe)
obj := $(wildcard */*.o) $(wildcard *.o) $(wildcard */*.so) $(wildcard */*.pcm) $(wildcard */*.d)

clean:
	@echo cleaning dir...
	rm -f $(exe) $(obj) $(tilde)

#CC := g++
#CCFLAGS:= -std=c++11 -Wall -g
#ROOT_FLAGS := $(shell root-config --cflags)
#ROOT_LIBS := $(shell root-config --libs)
#INCLUDE := -I src/ -I $(shell root-config --libdir)
#NAME := p31
#
#SRC1 := $(notdir $(wildcard main/$(NAME).C)) 
#
#EXE_1 := $(SRC1:.C=.exe)
#EXE := $(addprefix bin/, $(EXE_1))
#
##para ficar com nome do exe diferente do .o, variavel nome
#
#SRC2 := $(notdir $(wildcard src/*.C src/*.h))
#
#OBJS := $(SRC2:.C=.o)
#
#PROTECT := $(notdir $(EXE:.exe=.o)) 
#VPATH := src/  main/
#
#.PRECIOUS: $(OBJS) $(PROTECT)
#
#all: $(EXE) 
#
#bin/%.exe: bin/%.o $(OBJS)
#	@echo "Compiling $^  [$@]"
#	@$(CC) $(CCFLAGS) $(ROOT_FLAGS) $^  -o $@ $(INCLUDE) $(ROOT_LIBS)
#
#bin/%.o: %.C
#	@echo "Compiling $^  [$@]"
#	@$(CC) -c $(CCFLAGS) $(ROOT_FLAGS) $^ $(INCLUDE) -o $@
#
#bin/%.o: %.cpp
#	@echo "Compiling $^  [$@]"
#	@$(CC) -c $(CCFLAGS) $(ROOT_FLAGS) $^ $(INCLUDE) -o $@
#
#bin/%.o: %.cc
#	@echo "Compiling $^  [$@]"
#	@$(CC) -c $(CCFLAGS) $(ROOT_FLAGS) $^ $(INCLUDE) -o $@
#
#
#clean:
#	rm -fv bin/*.o bin/*.exe
#
#run:
#	bin/$(NAME).exe
#
#test:
#	@echo "Testing..."
#	@echo "\nEXE:"
#	@echo $(EXE) 
#	@echo "\nOBJS:"
#	@echo $(OBJS)
#	@echo "\nPROTECT:"
#	@echo $(PROTECT)	
