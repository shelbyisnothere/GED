#
# made by shelby on 11/19/2020
#	makefile for root n approximation
#

# Compiler
CXX = g++
# Preprocessor flags
CPPFLAGS = -I ~/include -std=c++11
# Compiler flags
CXXFLAGS = -Wall -O3 -DNDEBUG
# Linker flags
LDFLAGS = -L ~/lib
# Library flags
LDLIBS = -lsdsl -ldivsufsort -ldivsufsort64 -lboost_serialization

# Project name
PROJECTNAME = RootNApproximation

# Executable name
EXEC = rnapprox

SRCS = $(wildcard *.cpp)
HEADERS = $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SRCS))

# Default target
all: $(EXEC)

# Clean up files
clean:
	rm -f $(OBJS) $(EXEC) *~ #* *.d

# Create dependency files
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's, \($*\).0[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Link files
$(EXEC): $(OBJS)
#	$(CXX) -static -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS) $(LDLIBS)

Makefile: $(SRCS: .cpp = .d)

backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

-include $(SRCS:.cpp=.d)
