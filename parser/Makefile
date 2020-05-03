CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = 
OBJFILES = productions.o parser.o
TARGET = parser

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
