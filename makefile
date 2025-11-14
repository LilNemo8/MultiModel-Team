# ---- Compiler & Flags ----
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra \
            -Iclasses -Ideepseek -Ihelper \
            -MMD -MP

# ---- Directories ----
OBJ_DIR  := obj
TARGET   := main

# ---- Source Files ----
SOURCES := \
    main.cpp \
    classes/manager.cpp \
    classes/stock.cpp \
    deepseek/deepseek.cpp \
    helper/functions.cpp

# ---- Object + Dependency Files ----
OBJECTS := $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)
DEPS    := $(OBJECTS:.o=.d)

# ---- Default ----
all: $(TARGET)

# ---- Link Executable ----
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# ---- Compile Each .cpp Into obj/... ----
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- Run Program ----
.PHONY: run
run: $(TARGET)
	./$(TARGET)

# ---- Clean ----
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# ---- Auto Header Dependencies ----
-include $(DEPS)
