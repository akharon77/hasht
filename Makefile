OPT_LVL			:= 5

CXX 		   	:= g++
CXX_FLAGS		:= -O2 -std=c++2a -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -pie -Wlarger-than=8192 -Wstack-usage=8192 -D_SPEED_TEST -D OPT_LVL=$(OPT_LVL) -msse4.2 -mavx512vl -mavx512bw -mlzcnt -masm=intel

PROGRAM_NAME	:= hasht_opt_$(OPT_LVL)
PROGRAM_OUT		:= $(addsuffix .out, $(PROGRAM_NAME))

INCLUDE_DIRS	:= include/

 SOURCE_DIR		:= src/
 SOURCE_DIRS	:= hasht/ list/ test/

BUILD_DIR		:= build/
BUILD_DIRS		:= obj/
BUILD_DIRS		:= $(BUILD_DIR) $(addprefix $(BUILD_DIR), $(BUILD_DIRS))

OBJ_DIR			:= $(BUILD_DIR)obj/

BUILD_DIRS_DEP	:= $(addsuffix .dirstamp, $(BUILD_DIRS) $(addprefix $(OBJ_DIR), $(SOURCE_DIRS)))

SOURCE_DIRS		:= $(SOURCE_DIR) $(addprefix $(SOURCE_DIR), $(SOURCE_DIRS))
SOURCE_FILES	:= $(wildcard $(addsuffix *.cpp, $(SOURCE_DIRS)))

DEP_FILES 		:= $(SOURCE_FILES:.cpp=.d)

OBJECT_FILES	:= $(patsubst src/%.cpp, $(OBJ_DIR)%.o, $(SOURCE_FILES))

BUILD_LOG		:= $(BUILD_DIR)build.log

all: $(BUILD_DIRS_DEP) $(PROGRAM_OUT)

ifeq ($(OPT_LVL), 5)
$(PROGRAM_OUT): $(OBJECT_FILES) $(OBJ_DIR)hasht/crc32.o
	@echo [$(shell date -Iseconds)] Build $@ | tee -a $(BUILD_LOG)
	@$(CXX) $^ -o $@ $(CXX_FLAGS) | tee -a $(BUILD_LOG)
else
$(PROGRAM_OUT): $(OBJECT_FILES)
	@echo [$(shell date -Iseconds)] Build $@ | tee -a $(BUILD_LOG)
	@$(CXX) $^ -o $@ $(CXX_FLAGS) | tee -a $(BUILD_LOG)
endif


ifeq ($(OPT_LVL), 5)
$(OBJ_DIR)hasht/crc32.o: $(SOURCE_DIR)hasht/crc32.s 
	nasm -f elf64 $< -o $@
endif

$(OBJ_DIR)%.o: $(SOURCE_DIR)%.cpp $(BUILD_DIRS_DEP)
	@echo [$(shell date -Iseconds)] Compile $< | tee -a $(BUILD_LOG)
	@$(CXX) $< -c $(CXX_FLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -o $@ -MMD | tee -a $(BUILD_LOG)

%/.dirstamp:
	@mkdir -p $(dir $@) && touch $@
	@echo [$(shell date -Iseconds)] Make dir $(dir $@) | tee -a $(BUILD_LOG)

sinclude $(DEP_FILES)

clean:
	@rm -rf $(BUILD_DIR) $(DEP_FILES) build.log

