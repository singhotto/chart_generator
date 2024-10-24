# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Directories
SRCDIR = .
UTILSDIR = utils
OBJDIR = obj

# Output executable
TARGET = main

# Source files
SRCS = $(SRCDIR)/main.cpp \
       $(UTILSDIR)/Chart.cc

# Object files
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

# Include directories (add more if needed)
INCLUDES = -I$(UTILSDIR)

# Linker flags
LDFLAGS = 

# Rules
all: $(TARGET)

# Rule to create the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Rule to create object files from source files
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJDIR) $(TARGET) *.bmp

# Phony targets
.PHONY: all clean
