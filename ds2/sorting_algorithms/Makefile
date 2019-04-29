#************************* INPUTS **********************************************

EXEC  = sorting_algorithms
_DEPS = sorting_algorithms.h
_OBJ  = sorting_algorithms.o
_MAIN = test_sorting_algorithms.o
LIB_NAME = utils

#************************** VARIABLES ******************************************

GD = gcc -ansi -pedantic-errors -Wall -Wextra -g -fPIC -I$(INC_DIR)
GC = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -fPIC -I$(INC_DIR)
GCC_FLAGS = -lm

MAIN_DIR = /home/rd58/git/ds
INC_DIR = $(MAIN_DIR)/include
LIB_DEBUG_DIR = $(MAIN_DIR)/lib/debug
LIB_RELEASE_DIR = $(MAIN_DIR)/lib/release
DEBUG_DIR = $(MAIN_DIR)/obj/debug
RELEASE_DIR = $(MAIN_DIR)/obj/release
DEBUG_BIN = $(MAIN_DIR)/bin/debug
RELEASE_BIN = $(MAIN_DIR)/bin/release
CLEAN_DIRS = $(DEBUG_DIR) $(RELEASE_DIR) $(DEBUG_BIN) $(RELEASE_BIN)

DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
BIN_D = $(patsubst %,$(DEBUG_BIN)/%,$(_OBJ)  $(_MAIN))
BIN_R = $(patsubst %,$(RELEASE_BIN)/%,$(_OBJ)  $(_MAIN))
OBJ_D = $(patsubst %,$(DEBUG_DIR)/%,$(_OBJ))
OBJ_R = $(patsubst %,$(RELEASE_DIR)/%,$(_OBJ))
MAIN_D = $(patsubst %,$(DEBUG_DIR)/%,$(_MAIN))
MAIN_R = $(patsubst %,$(RELEASE_DIR)/%,$(_MAIN))

#************************ MAKE *************************************************

.PHONY: debug
debug: include $(DEBUG_DIR)/$(EXEC)

$(DEBUG_DIR)/$(EXEC): $(MAIN_D) $(LIB_DEBUG_DIR)/lib$(LIB_NAME).a
	@$(GD) -o $@ $^ $(GCC_FLAGS)
	@ln -f -s $@ $(DEBUG_BIN) 2> /dev/null

$(LIB_DEBUG_DIR)/lib$(LIB_NAME).a: $(OBJ_D)
	@ar rcs $(LIB_DEBUG_DIR)/lib$(LIB_NAME).a $?

$(DEBUG_DIR)/%.o: %.c $(DEPS)
	@$(GD) -c -o $@ $<
	@ln -f -s $@ $(DEBUG_BIN) 2> /dev/null

.PHONY: release
release: include $(RELEASE_DIR)/$(EXEC)

$(RELEASE_DIR)/$(EXEC): $(MAIN_R) $(LIB_RELEASE_DIR)/lib$(LIB_NAME).a
	@$(GC) -o $@ $^ $(GCC_FLAGS)
	@ln -f -s $@ $(RELEASE_BIN) 2> /dev/null

$(LIB_RELEASE_DIR)/lib$(LIB_NAME).a: $(OBJ_R)
	@ar rcs $(LIB_RELEASE_DIR)/lib$(LIB_NAME).a $?

$(RELEASE_DIR)/%.o: %.c $(DEPS)
	@$(GC) -c -o $@ $<
	@ln -f -s $@ $(RELEASE_BIN) 2> /dev/null

.PHONY: include
include:
	@ln -f -s $$PWD/*.h $(INC_DIR) 2> /dev/null

#**************************** UTILITY FUNCTIONS ********************************

.PHONY: run
run:
	@$(DEBUG_DIR)/$(EXEC)

.PHONY: gdb
gdb:
	@cgdb $(DEBUG_DIR)/$(EXEC)

.PHONY: vlg
vlg:
	@valgrind --leak-check=yes --track-origins=yes $(DEBUG_DIR)/$(EXEC)

.PHONY: run_release
run_release:
	@$(RELEASE_DIR)/$(EXEC)

.PHONY: clean
clean:
	@for i in $(OBJ_D) $(OBJ_R) $(BIN_D) $(BIN_R) $(MAIN_D) $(MAIN_R); \
	do rm -f $$i; done
	@for i in $(CLEAN_DIRS); do rm -f $$i/$(EXEC); done
