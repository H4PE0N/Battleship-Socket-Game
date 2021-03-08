
EXECUTABLE_PROGRAM := battleship

SOURCE_FOLDER := Source-Programs-Folder

OBJECT_FOLDER := Object-Programs-Folder

HEADER_FOLDER := Header-Programs-Folder

SOURCE_PROGRAMS := $(wildcard $(SOURCE_FOLDER)/*.c)

HEADER_PROGRAMS := $(wildcard $(HEADER_FOLDER)/*.h)

OBJECT_PROGRAMS := $(patsubst $(SOURCE_FOLDER)/%.c, \
	$(OBJECT_FOLDER)/%.o, $(SOURCE_PROGRAMS))

COMPILING_COMPILOR := gcc

COMPILING_FLAGS :=

$(EXECUTABLE_PROGRAM): $(OBJECT_PROGRAMS)
	$(COMPILING_COMPILOR) $(COMPILING_FLAGS) $^ -o $@

$(OBJECT_FOLDER)/%.o: $(SOURCE_FOLDER)/%.c \
	$(HEADER_FOLDER)/%.h
	$(COMPILING_COMPILOR) $(COMPILING_FLAGS) $< -c -o $@
