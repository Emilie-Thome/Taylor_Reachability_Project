# Directories
FILIBHOME = lib/filibsrc
FADBADHOME = lib/FADBAD++
PYTHON3HOME = /usr/include/python3.8
NUMPYHOME = /home/emilie/.local/lib/python3.8/site-packages/numpy/core/include
MATPLOTHOME = lib/matplotlib-cpp-master
SOURCE_PATH = src
INCLUDE_PATH = include
EXAMPLE_PATH = examples

# Setings
CXX = g++ 
MAX_ORDER = 40
LIBS = -lprim -lstdc++ -lpython3.8
CURRENT_DIR = $(shell pwd)
CXXFLAGS = -Wno-sign-compare -Wno-misleading-indentation -Wno-parentheses -Wno-unknown-pragmas -Wno-deprecated \
	 -ggdb -Wall -frounding-math -DMAXORDER=$(MAX_ORDER) -I. -I$(FILIBHOME) -I$(FADBADHOME) -I/usr/local/include \
	 -I$(CURRENT_DIR)/aaflib-0.1 -fpermissive -std=c++11 -I$(INCLUDE_PATH) 
CXXFLAGS_plot = -std=c++11 -I$(PYTHON3HOME) -I$(NUMPYHOME) -I$(MATPLOTHOME)
LDFLAGS  +=  -L/usr/local/lib -L$(CURRENT_DIR)/aaflib-0.1 -L$(FILIBHOME)/libprim/.libs/

# Files
SOURCES_utils = $(wildcard $(SOURCE_PATH)/*.cpp)
INCLUDES = $(wildcard $(INCLUDE_PATH)/*.h) $(MATPLOTHOME)/matplotlibcpp.h
SOURCES = $(wildcard $(EXAMPLE_PATH)/*.cpp)
OBJECTS_utils = $(SOURCES_utils:$(SOURCE_PATH)/%.cpp=$(SOURCE_PATH)/%.o)
OBJECTS = $(SOURCES:$(EXAMPLE_PATH)/%.cpp=$(EXAMPLE_PATH)/%.o)

# Commands
all: $(SOURCES:$(EXAMPLE_PATH)/%.cpp=%)

test_continuous : $(EXAMPLE_PATH)/test_continuous.o $(OBJECTS_utils)
	$(CXX) $(LDFLAGS) $(EXAMPLE_PATH)/$@.o $(OBJECTS_utils) $(LIBS) -o $(EXAMPLE_PATH)/$@
	@echo "Linking complete!"

test_hybrid : $(EXAMPLE_PATH)/test_hybrid.o $(OBJECTS_utils)
	$(CXX) $(LDFLAGS) $(EXAMPLE_PATH)/$@.o $(OBJECTS_utils) $(LIBS) -o $(EXAMPLE_PATH)/$@
	@echo "Linking complete!"
	
$(EXAMPLE_PATH)/%.o: $(EXAMPLE_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_plot) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(SOURCE_PATH)/%.o: $(SOURCE_PATH)/%.cpp 
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_plot) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(OBJECTS_utils) *.o
	@echo "Cleanup complete!"