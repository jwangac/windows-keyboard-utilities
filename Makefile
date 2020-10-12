CC := x86_64-w64-mingw32-gcc

FLAGS := -std=c99 -Wall -Wno-unused-function
FLAGS += -O3 -flto
FLAGS += -s -ffunction-sections -fdata-sections -Wl,-gc-sections

INCS := $(wildcard *.h)
SRCS := $(wildcard *.c)
EXES := $(patsubst %.c, %.exe, $(SRCS))

all: $(EXES)

%.exe: %.c $(INCS) Makefile
	@echo 'CC $<'
	@$(CC) $(FLAGS) -o $@ $<

clean:
	@rm -rf *.exe

format:
	@clang-format -style=file -i $(INCS) $(SRCS)
