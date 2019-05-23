CC      =  gcc
CFLAGS  =  -Wall
CFLAGS += -Wextra
CFLAGS += -Wno-unused-parameter

LDFLAGS = -lpthread

INCLUDIR = -I inc

SRCDIR  = src
OBJDIR  = obj
BINDIR  = bin

EXEC  = main

.PHONY: all

all: $(EXEC)

main: $(OBJDIR)/main.o $(OBJDIR)/time_utils.o $(OBJDIR)/affinity.o

% :$(OBJDIR)/%.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< $(INCLUDIR) -o 	$@

mrproper: clean
	rm -f $(BINDIR)/*

clean:
	rm -f $(OBJDIR)/*.o
