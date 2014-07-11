#**********************************************************************

# makefile

# $Author$
# created at: Tue Jul  8 11:58:53 JST 2014

# Copyright (C) 2014-2015 Ryo Matsumoto

#**********************************************************************



# build target directory
OBJDIR := build

# justitam user name
USERNAME := justitam

# justitam
GROUPNAME := justitam



#################################################
.PHONY: install
install: all
	

.PHONY: run
run: all
	./$(OBJDIR)/latest

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