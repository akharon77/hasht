CXX 		   := g++
CXX_FLAGS 	   := -O0 -ggdb3 -std=c++2a -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -pie -Wlarger-than=8192 -Wstack-usage=8192

PROGRAM_NAME   := hasht
PROGRAM_OUT    := $(addsuffix .out, $(PROGRAM_NAME))

 SOURCE_DIRS   := . hasht list test
INCLUDE_DIRS   := . hasht list test
INCLUDE_DIRS   := $(addprefix include/, $(INCLUDE_DIRS))

SOURCE_DIRS    := $(addprefix src/, $(SOURCE_DIRS))
SOURCE_FILES   := $(wildcard $(addsuffix /*.cpp, $(SOURCE_DIRS)))

OBJECT_FILES   := $(SOURCE_FILES:.cpp=.o)

BUILD_DIRS     := bin bin/obj dep
OBJECT_DIR     := bin/obj
DEP_DIR		   := dep

BUILD_DIRS_DEP := $(addsuffix /.dirstamp, $(BUILD_DIRS))

BUILD_LOG      := build.log

all: $(BUILD_DIRS_DEP) $(PROGRAM_OUT)

$(PROGRAM_OUT): $(OBJECT_FILES)
	$(CXX) $^ -o $@ $(CXX_FLAGS)

%.o: %.cpp $(BUILD_DIRS_DEP)
	@echo [$(shell date -Iseconds)] Compile $< > $(BUILD_LOG)
	$(CXX) $< -c $(CXX_FLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -MMD -o $(OBJECT_DIR)/$@
	mv $($@:.cpp=.d) dep/

%/.dirstamp:
	mkdir -p $(dir $@) && touch $@

sinclude $(DEP_DIR)/*.d

clean:
	rm -rf $(BUILD_DIRS)

