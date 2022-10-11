# Directory Settings
BUILD_DIR := bin
SRC_DIR := src
OBJ_DIR := obj
INC_DIR := inc
DEP_DIR := obj

#EXTENSION
SRC_EXT 		:= c
INC_EXT 		:= h
OBJ_EXT 		:= o
DEP_EXT 		:= d

CXX := gcc		#compilator flag
# -Wall : turn on  most of the information
# -g : turn on debug info
CXXFLAGS := -Wall -g
LDFLAGS := -I$(INC_DIR)

# Files loading
FILES := $(wildcard $(SRC_DIR)/*.$(SRC_EXT)) # load all the *.c files
OBJECTS := $(FILES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.$(OBJ_EXT))	# convert all the *.c into .o object inside the ./obj/ directory
INCLUDES := $(wildcard $(INC_DIR)/*.$(INC_EXT))	# load all the header files
DEPS := $(FILES:%.$(SRC_EXT)=$(OBJ_DIR)/%.$(OBJ_EXT)) # convert all the *.c into .d dependancies inside the ./obj/ directory
EXEC := main # name of the executable generated

# main execution
all: $(BUILD_DIR)/$(EXEC)
	
# build the executable by linking the object and creating the bin directory if not already created
$(BUILD_DIR)/$(EXEC): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# build all the object and dependancies files from the *.c files
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) $(INCLUDES) | $(OBJ_DIR)
	$(CXX) -c $(CXXFLAGS) $(LDFLAGS) $< -o $@
	$(CXX) -MM $(CXXFLAGS) $(LDFLAGS) $< > $(DEP_DIR)/$*.$(DEP_EXT)

# create the directory build
$(BUILD_DIR):
	mkdir bin

# create the object build
$(OBJ_DIR):
	mkdir obj

# clean all the project
.PHONY: clean mrproper

clean:
	rm *.$(OBJ_EXT)

mrproper: clean
	rm $(EXEC)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJ_EXT)=.$(DEP_EXT))