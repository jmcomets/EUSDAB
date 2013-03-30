CXX = g++
LD = g++

ROOTDIR = ./
SRCDIR  = ./src
INCDIR  = ./include
OBJDIR  = ./build/obj
DEPDIR  = ./build/dep
BINDIR  = ./bin
LIBDIRS  = ../../lib ../../include

INCFLAGS = -I$(INCDIR) -I$(LIBDIR)
WRNFLAGS = -ansi -pedantic -W -Wall -Wextra -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline
CXXFLAGS = $(WRNFLAGS) $(INCFLAGS) -std=c++0x
LDFLAGS =
LDLIBS =

SOURCES = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.cpp))
OBJECTS = $(addsuffix .o, $(basename $(subst $(SRCDIR), $(OBJDIR), $(SOURCES))))
DEPENDS = $(addsuffix .d, $(basename $(subst $(SRCDIR), $(DEPDIR), $(SOURCES))))

ECHO = @echo
RM = @rm -f
MKDIR = @mkdir -p

ALL = all
CLEAN = clean
MRPROPER = mrproper
TARGET = $(ROOTDIR)/EUSDAB

.PHONY: $(ALL) $(CLEAN) $(MRPROPER)

$(ALL): $(TARGET)

$(TARGET): $(OBJECTS)
	$(MKDIR) $(@D)
	$(LD) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(MKDIR) $(@D)
	$(MKDIR) $(dir $(DEPDIR)/$*.d)
	$(CXX) $(CXXFLAGS) -c $< -MMD -MF $(DEPDIR)/$*.d -o $@

$(CLEAN):
	$(RM) $(OBJECTS) $(DEPENDS)

$(MRPROPER): $(CLEAN)
	$(RM) $(TARGET)

-include $(DEPENDS)
