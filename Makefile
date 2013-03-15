# Generic Makefile
# Author : Turpin Pierre
# Date : 22/11/2012

CXX = g++

SRCDIR = ./src
INCDIR = ./include
OBJDIR = ./build/obj
DEPDIR = ./build/dep
BINDIR = ./bin

WRNFLAGS = -pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -W -Wunused-parameter -ansi # -Weffc++ -Wshadow

CXXFLAGS.release = $(WRNFLAGS) -I$(INCDIR) -I./lib/SFML-2.0-rc/include -std=c++0x
LDFLAGS.release = -L./lib/SFML-2.0-rc/lib
LDLIBS.release = -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS.debug = $(WRNFLAGS) -I$(INCDIR) -I./lib/SFML-2.0-rc/include -std=c++0x
LDFLAGS.debug = -L./lib/SFML-2.0-rc/lib
LDLIBS.debug = -lsfml-graphics -lsfml-window -lsfml-system

PROD = release

CXXFLAGS = $(CXXFLAGS.$(PROD))
LDFLAGS = $(LDFLAGS.$(PROD))
LDLIBS = $(LDLIBS.$(PROD))
OUTPUT_OPTION = -MMD

REC_SRCDIR = $(shell find $(SRCDIR) -type d)
SOURCES = $(foreach dir,$(REC_SRCDIR), $(wildcard $(dir)/*.cpp))
OBJECTS = $(addsuffix .o, $(basename $(subst $(SRCDIR), $(OBJDIR), $(SOURCES))))
#OBJECTS = $(foreach dir, $(REC_SRCDIR),$(SOURCES: $(dir)/%.cpp=$(OBJDIR)/%.o)) 
DEPENDS = $(addsuffix .d, $(basename $(subst $(SRCDIR), $(DEPDIR), $(SOURCES))))

ECHO = @echo
RM = rm -f
MKDIR = mkdir -p

ALL = all
TEST = test
RUN = run
CLEAN = clean
MRPROPER = mrproper
TARGET = $(BINDIR)/EUSDAB

.PHONY: $(ALL) $(TEST) $(CLEAN) $(RUN) $(MRPROPER)

$(ALL): $(TARGET)

$(TEST):
	$(ECHO) $(SOURCES)
	$(ECHO) $(REC_SRCDIR)
	$(ECHO) $(OBJECTS)

$(RUN): $(TARGET)
	@export LD_LIBRARY_PATH=./lib/SFML-2.0-rc/lib && ./$(TARGET)

$(TARGET): $(OBJECTS)
	$(MKDIR) $(@D)
	$(LINK.cpp) $^ $(LDLIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(MKDIR) $(@D)
	$(MKDIR) $(dir $(DEPDIR)/$*.d)
	$(COMPILE.cpp) $< $(OUTPUT_OPTION) -MF $(DEPDIR)/$*.d -o $@

$(CLEAN):
	$(RM) $(OBJECTS) $(DEPENDS) $(TARGET)

$(MRPROPER): $(CLEAN)
	$(RM) $(TARGET)

-include $(DEPENDS)
