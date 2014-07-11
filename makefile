OBJDIR := build

.PHONY: all
all: make_directories $(OBJDIR)/latest

$(OBJDIR)/latest: main.c
	gcc -o $(OBJDIR)/latest main.c

$(OBJDIR)/:
	mkdir -p $@


.PHONY: make_directories 
make_directories: $(OBJDIR)/

.PHONY: clean
clean:
	rm -rf $(OBJDIR)