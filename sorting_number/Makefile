CC = g++

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS = main.cpp externalSort.cpp
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

TRGT = $(BINDIR)/exe 
TRGT2 = sorted.txt

$(TRGT) : $(OBJS)
	$(CC) $^ -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) -c $< -Iinclude -o $@

clean:
	rm -rf $(OBJS) $(TRGT) $(TRGT2)
