# Generic Makefile
# Author : Turpin Pierre
# Date : 22/11/2012

CXX=g++

SRCDIR=./src
INCDIR=./include
OBJDIR=./build/obj
DEPDIR=./build/dep
BINDIR=./bin

WRNFLAGS=-pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -W -Wunused-parameter -ansi # -Weffc++ -Wshadow

CXXFLAGS.release=$(WRNFLAGS) -I$(INCDIR) -I./lib/SFML-2.0-rc/include -std=c++0x
LDFLAGS.release=-L./lib/SFML-2.0-rc/lib
LDLIBS.release=-lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS.debug=$(WRNFLAGS) -I$(INCDIR) -I./lib/SFML-2.0-rc/include -std=c++0x
LDFLAGS.debug=-L./lib/SFML-2.0-rc/lib
LDLIBS.debug=-lsfml-graphics -lsfml-window -lsfml-system

PROD=release

CXXFLAGS=$(CXXFLAGS.$(PROD))
LDFLAGS=$(LDFLAGS.$(PROD))
LDLIBS=$(LDLIBS.$(PROD))
OUTPUT_OPTION=-MMD

SOURCES=$(wildcard $(SRCDIR)/*.cpp)
HEADERS=$(wildcard $(INCDIR)/*.h)
OBJECTS=$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPENDS=$(SOURCES:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)

ECHO=@echo
RM=rm -f

RUN=run
CLEAN=clean
MRPROPER=mrproper
TARGET=$(BINDIR)/EUSAB

all:$(TARGET)

.PHONY:all $(CLEAN) $(RUN) $(MRPROPER)

$(RUN):$(TARGET)
	export LD_LIBRARY_PATH=./lib/SFML-2.0-rc/lib && ./$(TARGET)

$(TARGET):$(OBJECTS)
	$(LINK.cpp) $^ $(LDLIBS) -o $@

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	$(COMPILE.cpp) $< $(OUTPUT_OPTION) -MF $(DEPDIR)/$*.d -o $@

$(CLEAN):
	$(RM) $(OBJECTS) $(DEPENDS)

$(MRPROPER):$(CLEAN)
	$(RM) $(TARGET)

-include $(DEPENDS)

