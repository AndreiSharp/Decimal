CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c11

NAME := s21_decimal
TARGET := $(NAME).a

SRCDIR := ./another/ 
SRCDIR += ./arithmetic
SRCDIR += ./binary
SRCDIR += ./comprasion
SRCDIR += ./convertation
SRCDIR += ./helper
SRCEXT := c
SRC := $(shell find $(SRCDIR) -depth -name '*.$(SRCEXT)')

HDEXT := h
HEADERS := $(shell find ./include -depth -name '*.$(HDEXT)')

OBJEXT := o
OBJECT := $(shell find . -name '*.$(OBJEXT)')

TSTDIR := ./test
TSTEXT := $(SRCEXT)
TST := $(shell find $(TSTDIR) -depth -name '*.$(TSTEXT)')
TESTER := test_$(NAME)

LFLAGS := -lcheck

GCOV = gcovr
GCOVFLAGS = -fprofile-arcs -ftest-coverage --coverage
REPORT = report.html

FORMATER := clang-format
STYLE := '{BasedOnStyle: Google}'

RM := rm

all: clean $(TARGET)

$(TARGET): $(SRC)
	$(CC) -c $(CFLAGS) $(SRC)
	ar rc $(OBJECT)
	ranlib 	$(TARGET) $(OBJECT)
	cp $(TARGET) lib$(TARGET)

test: $(TST) $(TARGET)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(TESTER) $(TST) -L. -l$(TARGET) 
	./$(TESTER)

gcov_report:
	
style: clean
	$(FORMATER) -i -style=$(STYLE) $(SRC) $(HEADERS) $(TST)

style_check: clean
	$(FORMATER) -n -style=$(STYLE) $(SRC) $(HEADERS) $(TST)

clean:
	$(RM) -f $(TARGET)
	$(RM) -f $(TESTER)
	$(RM) -f $(OBJECT)
