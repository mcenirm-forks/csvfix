PRODUCT := csvfix
BINDIR := bin
WINOUT := $(BINDIR)/$(PRODUCT).exe
LINOUT := $(BINDIR)/$(PRODUCT)

SHELL := bash

INCDIR := inc
SRCDIR := src
OBJDIR := obj
CXX := g++
INCDIRS := -I$(INCDIR) -I../alib/inc
CXXFLAGS := -std=c++0x 

ALIB = ../alib/lib/alib.a
WINLIBS = ../alib/lib/alib.a -lodbc32 
LINLIBS = ../alib/lib/alib.a 

WINSPEC :=  $(SRCDIR)/csved_odbc.o $(SRCDIR)/csved_call.o
ALLSRC := $(wildcard $(SRCDIR)/*.cpp)  
WINSRC := $(ALLSRC)
LINSRC := $(filter-out $(WINSPEC),$(ALLSRC))

WINOBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(WINSRC))
LINOBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(LINSRC))
WINDEPS := $(patsubst $(OBJDIR)/%.o,$(OBJDIR)/%.d,$(WINOBJS))
LINDEPS := $(patsubst $(OBJDIR)/%.o,$(OBJDIR)/%.d,$(LINOBJS))

.PHONY: null
null:
	@echo "must use 'make win', 'make lin' or 'make clean'"


$(WINOUT): $(WINOBJS) $(ALIB)
	$(CXX) -o $@ $^ $(WINLIBS)
	strip $(WINOUT)

$(LINOUT): $(LINOBJS) $(ALIB)
	$(CXX) -o $@ $^ $(LINLIBS)
	strip $(LINOUT)

win: 
	$(MAKE) $(WINOUT)

lin: 
	$(MAKE) $(LINOUT)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/$(PRODUCT)

# Remove any dependency files and rebuild all dependencies
depends:
	rm -f $(OBJDIR)/*.d
	$(MAKE) $(DEPFILES)

$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
	$(CXX) $(INCDIRS) -MM $< \
	  | tr '\\\n\r' ' ' \
	  | sed -e 's%^%$@ %' -e 's% % $(OBJDIR)/%'\
	  > $@

-include $(WINDEPS)
-include $(LINDEPS)

# end

