CC = cc
CFLAGS = -Wall -std=c99 -I/usr/local/include -Isrc
LDFLAGS = -L/usr/local/lib -lcheck -lm -lsubunit
OBJDIR = dist
OBJS = $(addprefix $(OBJDIR)/,lib.o test.o)

.PHONY: all clean

all: check

check: $(OBJS)
	$(CC) -o $(OBJDIR)/$@ $^ $(LDFLAGS)

$(OBJDIR)/lib.o: src/lib.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/test.o: test/test.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

compile: main.bin test.bin

test.bin: test/test.c | $(OBJDIR)
	$(CC) $(C_OPTS) $< -fprofile-instr-generate -fcoverage-mapping -o $(OBJDIR)/$@ -lcheck

test: clean prep compile
	LLVM_PROFILE_FILE="$(OBJDIR)/test.profraw" $(OBJDIR)/test.bin
	llvm-profdata merge -sparse $(OBJDIR)/test.profraw -o $(OBJDIR)/test.profdata
	llvm-cov report $(OBJDIR)/test.bin -instr-profile=$(OBJDIR)/test.profdata src/*.c
	llvm-cov show $(OBJDIR)/test.bin -instr-profile=$(OBJDIR)/test.profdata src/*.c --format html > $(OBJDIR)/coverage.html
clean:
	rm -rf $(OBJDIR)/*.o
doxygen:
	doxygen
