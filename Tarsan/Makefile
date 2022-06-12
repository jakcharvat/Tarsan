# I spent hours with like 5 iterations of my Makefile trying to get it to work.
# It didn't.
# So I borrowed and slightly tweaked a Makefile from here, and it works much better than any of my attempts.
# https://gist.github.com/maxtruxa/4b3929e118914ccef057f8a05c614b0f

#BIN := quizzy
BIN := charvj12
TESTBIN := tarsanTests

# borrowed from https://stackoverflow.com/a/18258352/9020201
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCS := $(call rwildcard,src/tarsan,*.cpp)
TEST_SRCS := $(call rwildcard,src/tests,*.cpp)
MAIN_SRC := src/main.cpp
TEST_SRC := src/test.cpp
ALL_SRCS := $(SRCS) $(MAIN_SRC) $(TEST_SRC)

DIST_FILES := src examples assets Doxyfile Makefile prohlaseni.txt zadani.txt
DIST_DIR := charvj12
DIST_FILE := charvj12.zip

OBJDIR := .o
DEPDIR := .d

todir = $(patsubst %,$(1)/%$(2),$(basename $(3)))
toobj = $(call todir,$(OBJDIR),.o,$(1))
todep = $(call todir,$(DEPDIR),.d,$(1))

OBJS := $(call toobj,$(SRCS))
TEST_OBJS := $(call toobj,$(TEST_SRCS))
MAIN_OBJ := $(call toobj,$(MAIN_SRC))
TEST_OBJ := $(call toobj,$(TEST_SRC))
ALL_OBJS := $(OBJS) $(TEST_OBJS) $(MAIN_OBJ) $(TEST_OBJ)

DEPS := $(call todep,$(SRCS))
TEST_DEPS := $(call todep,$(TEST_SRCS))
MAIN_DEP := $(call todep,$(MAIN_SRC))
TEST_DEP := $(call todep,$(TEST_SRC))
ALL_DEPS := $(DEPS) $(TEST_DEPS) $(MAIN_DEP) $(TEST_DEP)

LOGFILE := console.log

$(shell mkdir -p $(dir $(ALL_OBJS)) >/dev/null)
$(shell mkdir -p $(dir $(ALL_DEPS)) >/dev/null)

ifdef __APPLE__
#CXX := g++-11
#LD := g++-11

CXX := g++
LD := g++


CXXFLAGS += -I/opt/homebrew/opt/ncurses/include
LDFLAGS += -L/opt/homebrew/opt/ncurses/lib
else
CXX := g++
LD := g++
endif

CXXFLAGS := -std=c++17 -g -Wall -Wextra -pedantic -fsanitize=address
DEPFLAGS := -MT $@ -MD -MP -MF $(DEPDIR)/$*.Td
LDFLAGS += -lform -lmenu -lncurses -fsanitize=address

#COMPILE.cpp := $(CXX) $(DEPFLAGS) $(CXXFLAGS) -c -o $@
COMPILE.cpp = $(CXX) $(CXXFLAGS) -c -o $@
LINK.o = $(LD) $(LDFLAGS) -o $@
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d


all: $(BIN) doc

run: $(BIN)
	./$(BIN)

compile: $(BIN)

test: testSet $(TESTBIN)
	./$(TESTBIN)

doc: $(ALL_SRCS) Doxyfile
	doxygen

.PHONY: testSet
testSet:
	$(eval TEST = -D __TEST__)

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) $(DEPDIR) $(BIN) $(TESTBIN) doc $(DIST_DIR) charvj12* $(LOGFILE)

$(BIN): $(OBJS) $(MAIN_OBJ)
	mkdir -p $(dir $(BIN))
	echo "Linking objects..."
	$(LINK.o) $^
	echo "Done"

$(TESTBIN): $(OBJS) $(TEST_OBJS) $(TEST_OBJ)
	@echo "Linking objects..."
	@$(LINK.o) $^
	@echo "Done"

$(OBJDIR)/%.o: %.cpp
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.d
	echo "Building $@... "
	$(COMPILE.cpp) $< $(TEST)
#	$(POSTCOMPILE)

dist: clean $(ALL_SRCS) $(DIST_FILES)
	mkdir -p $(DIST_DIR)
	cp -r $(DIST_FILES) $(DIST_DIR)
	zip -r $(DIST_FILE) $(DIST_DIR)

examples:
	mkdir examples

.PRECIOUS: $(DEPDIR)/%.d
$(DEPDIR)/%.d: ;

-include $(ALL_DEPS)
