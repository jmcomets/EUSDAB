# Generic Makefile written for EUSDAB
# 
# Author: Turpin Pierre / Comets Jean-Marie
# Date: 31/03/2013

# Compiler
CXX = g++
LD  = g++

# Target [release, debug]
PROD = debug

# Main directories
RTDIR  = .
SRCDIR = $(RTDIR)/src
INCDIR = $(RTDIR)/include
BLDDIR = $(RTDIR)/build
BINDIR = $(RTDIR)/bin
LIBDIR = $(RTDIR)/lib
OBJDIR = $(BLDDIR)/obj
DEPDIR = $(BLDDIR)/dep

# SFML
SFML_RTDIR  = $(LIBDIR)/SFML-2.0-rc
SFML_INCDIR = $(SFML_RTDIR)/include
SFML_LIBDIR = $(SFML_RTDIR)/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Various flags
CPPFLAGS = -pedantic -std=c++0x
WRNFLAGS = -W -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -Wunused-parameter -Weffc++

# Path flags (headers/libs)
INCDIRS  = $(INCDIR) $(SFML_INCDIR)
LIBDIRS  = $(LIBDIR) $(SFML_LIBDIR)
INCFLAGS = $(foreach dir, $(INCDIRS), -I$(dir))
LIBFLAGS = $(foreach dir, $(LIBDIRS), -L$(dir))

# Release
CXXFLAGS.release = $(CPPFLAGS) $(INCFLAGS)
LDFLAGS.release = $(LIBFLAGS)
LDLIBS.release = $(SFML_LIBS)

# Debug
CXXFLAGS.debug = $(CPPFLAGS) $(INCFLAGS) $(WRNFLAGS)
LDFLAGS.debug = $(LIBFLAGS)
LDLIBS.debug = $(SFML_LIBS)

# Final flags
CXXFLAGS = $(CXXFLAGS.$(PROD))
LDFLAGS  = $(LDFLAGS.$(PROD))
LDLIBS   = $(LDLIBS.$(PROD))

# Dependancy lookup
OUTPUT_OPTION = -MMD

REC_INCDIR = $(shell find $(INCDIR) -type d)
REC_SRCDIR = $(shell find $(SRCDIR) -type d)
HEADERS    = $(foreach dir, $(REC_INCDIR), $(wildcard $(dir)/*.h))
SOURCES    = $(foreach dir, $(REC_SRCDIR), $(wildcard $(dir)/*.cpp))
OBJECTS    = $(addsuffix .o, $(basename $(subst $(SRCDIR), $(OBJDIR), $(SOURCES))))
DEPENDS    = $(addsuffix .d, $(basename $(subst $(SRCDIR), $(DEPDIR), $(SOURCES))))

ECHO  = @echo
RM    = @rm -rf
MKDIR = @mkdir -p
CTAGS = @ctags -R --sort=yes --c++-kinds=+px-d --fields=+iaS --extra=+q

ALL      = all
RUN      = run
CLEAN    = clean
MRPROPER = mrproper

# File targets
TAGS   = $(RTDIR)/tags
TARGET = $(BINDIR)/EUSDAB

.PHONY: $(ALL) $(CLEAN) $(RUN) $(MRPROPER)

$(ALL): $(TARGET) $(TAGS)

$(TAGS): $(HEADERS) $(SOURCES)
	$(CTAGS) $(INCDIR) $(SRCDIR) $(SFML_INCDIR)

$(RUN): $(TARGET)
	@export LD_LIBRARY_PATH=$(SFML_LIBDIR) && ./$(TARGET)

$(TARGET): $(OBJECTS)
	$(MKDIR) $(@D)
	$(LINK.cpp) $^ $(LDLIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(MKDIR) $(@D)
	$(MKDIR) $(dir $(DEPDIR)/$*.d)
	$(COMPILE.cpp) $< $(OUTPUT_OPTION) -MF $(DEPDIR)/$*.d -o $@

$(CLEAN):
	$(RM) $(BLDDIR) $(DEPDIR) $(OBJDIR)

$(MRPROPER): $(CLEAN)
	$(RM) $(BINDIR) $(TARGET) $(TAGS)

-include $(DEPENDS)
