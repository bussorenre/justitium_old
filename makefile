#**********************************************************************

# makefile

# $Author$
# created at: Tue Jul  8 11:58:53 JST 2014

# Copyright (C) 2014-2015 Ryo Matsumoto
# respected	http://urin.github.io/posts/2013/simple-makefile-for-clang/

#**********************************************************************

# justitam user name
#USERNAME := justitium

# justitam
#GROUPNAME := justitium

CC       = gcc
CFLAGS   = -lpthread
LDFLAGS  =
LIBS     =
INCLUDE  = -I ./src
TARGET   = ./bin/justitium
OBJDIR   = ./obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR = .
endif
SOURCES  = $(wildcard *.c)
OBJECTS  = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))
DEPENDS  = $(OBJECTS:.o=.d)
RUNFLAGS = -d -p 9999

$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) -o $@ $^ $(LDFLAGS)


$(OBJDIR)/%.o: %.c
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

run: $(TARGET)
	$(TARGET) $(RUNFLAGS)


clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET)
	@rmdir --ignore-fail-on-non-empty `readlink -f $(OBJDIR)`

-include $(DEPENDS)