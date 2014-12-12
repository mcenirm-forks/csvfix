PRODUCT := alib.a
BINDIR := lib
SHELL := bash
INCDIR := inc
SRCDIR := src
EXPDIR := expat
OBJDIR := obj
CXX := g++
INCDIRS := -I$(INCDIR) -I$(EXPDIR)
CXXFLAGS := 

WINSPEC := $(SRCDIR)/a_db.cpp $(SRCDIR)/a_dir.cpp $(SRCDIR)/a_opsys.cpp $(SRCDIR)/a_winerr.cpp $(SRCDIR)/a_winenv.cpp
LINSPEC := $(SRCDIR)/a_linenv.cpp

ALLSRC := $(wildcard $(SRCDIR)/*.cpp)  
WINSRC := $(filter-out $(LINSPEC),$(ALLSRC))
LINSRC := $(filter-out $(WINSPEC),$(ALLSRC))
EXPSRC := $(wildcard $(EXPDIR)/*.cpp)

WINOBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(WINSRC))
LINOBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(LINSRC))
EXPOBJS := $(patsubst $(EXPDIR)/%.cpp,$(OBJDIR)/%.o,$(EXPSRC))
WINDEPS := $(patsubst $(OBJDIR)/%.o,$(OBJDIR)/%.d,$(WINOBJS))
LINDEPS := $(patsubst $(OBJDIR)/%.o,$(OBJDIR)/%.d,$(LINOBJS))
EXPDEPS := $(patsubst $(OBJDIR)/%.o,$(OBJDIR)/%.d,$(EXPOBJS))

win: $(WINOBJS) $(EXPOBJS) 
	ar rvs $(BINDIR)/$(PRODUCT) $^

lin: $(LINOBJS) $(EXPOBJS)
	ar rvs $(BINDIR)/$(PRODUCT) $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

$(OBJDIR)/%.o: $(EXPDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

# Clean the project by removing .o files, and executable.
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

$(OBJDIR)/%.d: $(EXPDIR)/%.cpp
	$(CXX) $(INCDIRS) -MM $< \
	  | tr '\\\n\r' ' ' \
	  | sed -e 's%^%$@ %' -e 's% % $(OBJDIR)/%'\
	  > $@

-include $(WINDEPS)
-include $(EXPDEPS)
-include $(LINDEPS)

# end

