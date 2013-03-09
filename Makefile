# Generic Makefile
# Author : Turpin Pierre
# Date : 22/11/2012

CXX=g++

SRCDIR=./src
INCDIR=./include
OBJDIR=./build/obj
DEPDIR=./build/dep
BINDIR=./bin

WRNFLAGS=-pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wshadow -Weffc++ -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -W -Wunused-parameter -ansi

CXXFLAGS.release=$(WRNFLAGS) -I./lib/SFML-2.0-rc/lib
LDFLAGS.release=-L$(INCDIR) -L./lib/SFML-2.0-rc/include
LDLIBS.release=-lsfml_system lsfml-window -lsfml-graphics

CXXFLAGS.debug=$(WRNFLAGS) -I./lib/SFML-2.0-rc/lib
LDFLAGS.debug=-L$(INCDIR) -L./lib/SFML-2.0-rc/include
LDLIBS.debug=-lsfml_system lsfml-window -lsfml-graphics

PROD=release

CXXFLAGS=$(CXXFLAGS.$(PROD))
LDFLAGS=$(LDFLAGS.$(PROD))
LDLIBS=$(LDLIBS.$(PROD))
OUTPUT_OPTION=-MMD -MF $(DEPDIR)

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
	./$(TARGET)

$(TARGET):$(OBJECTS)
	$(LINK.cpp) -o $^ $(LDLIBS)

$(CLEAN):
	$(RM) $(OBJECTS) $(DEPENDS)

$(MRPROPER):$(CLEAN)
	$(RM) $(TARGET)

-include $(DEPENDS)

