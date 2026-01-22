TARGET = cornelis
CC = gcc
CFLAGS = -Wall -Wextra -g 

SRCDIR = src
OBJDIR = obj

SOURCES = $(wildcard $(SRCDIR)/*.c)
# On transforme src/file.c en obj/file.o
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# La cible principale
all: $(TARGET)

# L'exécutable dépend des objets
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Chaque objet dépend de son .c ET du dossier obj
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour créer le dossier
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean