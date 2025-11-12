# ---- compiler & flags ----
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iclasses -Ihelper -MMD -MP

# ---- folders ----
SRC_DIRS := . classes helper
OBJ_DIR  := obj
TARGET   := main

# ---- sources / objects / deps ----
SRCS := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.cpp))
OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# ---- default ----
all: $(TARGET)

# ---- link ----
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# ---- compile (auto-create obj subdirs) ----
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- phony helpers ----
.PHONY: clean run debug

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# include auto-generated dependency files
-include $(DEPS)
