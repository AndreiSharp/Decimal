CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c11

NAME := s21_decimal

INCDIR := ./Headers
INC := $(INCDIR)/s21_arithmetic_function.h 
INC += $(INCDIR)/s21_comprasion_function.h  
INC += $(INCDIR)/s21_decimal.h 
INC += $(INCDIR)/s21_decimal_types.h 
INC += $(INCDIR)/s21_binary_function.h 
INC += $(INCDIR)/s21_convertation_function.h 
INC += $(INCDIR)/s21_decimal_function.h

DECDIR := ./Decimal
HELPDIR := $(DECDIR)/0_Help_function
ARITHMDIR := $(DECDIR)/1_Arithmetic
COMPDIR := $(DECDIR)/2_Comprasion_operators
CONVDIR := $(DECDIR)/3_Convertation_and_parsers
ANOTHERDIR := $(DECDIR)/4_Anouther_function

HELP = $(HELPDIR)/s21_arithmetic_function.c
HELP += $(HELPDIR)/s21_binary_function.c  
HELP += $(HELPDIR)/s21_comprasion_function.c
HELP += $(HELPDIR)/s21_decimal_function.c  

ARITH = $(ARITHMDIR)/s21_add.c 
ARITH += $(ARITHMDIR)/s21_div.c 
ARITH += $(ARITHMDIR)/s21_mul.c
ARITH += $(ARITHMDIR)/s21_sub.c

COMP = $(COMPDIR)/s21_is_equal.c            
COMP += $(COMPDIR)/s21_is_greater_or_equal.c 
COMP += $(COMPDIR)/s21_is_not_equal.c
COMP += $(COMPDIR)/s21_is_greater.c          
COMP += $(COMPDIR)/s21_is_less.c             
COMP += $(COMPDIR)/s21_is_less_or_equal.c

CONV = $(CONVDIR)/s21_from_decimal_to_float.c 
CONV += $(CONVDIR)/s21_from_decimal_to_int.c  
CONV += $(CONVDIR)/s21_from_float_to_decimal.c 
CONV += $(CONVDIR)/s21_from_int_to_decimal.c

ANOTHER = $(ANOTHERDIR)/s21_floor.c    
ANOTHER += $(ANOTHERDIR)/s21_negate.c   
ANOTHER += $(ANOTHERDIR)/s21_round.c    
ANOTHER += $(ANOTHERDIR)/s21_truncate.c

SOURCE := $(HELP) $(ARITH) $(COMP) $(CONV) $(ANOTHER)

TARGET := $(NAME).a

SRCEXT := .c
SRC := 
OBJDIR := ./Bin

all: clean $(TARGET)

obj_help: $(HELP)
	$(CC) $(CFLAGS) -c $^

obj_arith: $(ARITH)
	$(CC) $(CFLAGS) -c $^
 
obj_comp: $(COMP)
	$(CC) $(CFLAGS) -c $^

obj_conv: $(CONV)
	$(CC) $(CFLAGS) -c $^

obj_another: $(ANOTHER)
	$(CC) $(CFLAGS) -c $^

AR := ar
ARFLAGS := rc	
RLIB := ranlib

all: clean $(TARGET)

$(TARGET): obj_help obj_arith obj_comp obj_conv obj_another
	$(AR) $(ARFLAGS) $@ *.o
	$(RLIB) $@ 
	# @cp $@  lib$(TARGET)
	rm -f *.o

TSTDIR := ./Tests
TSTEXT := c
TST := $(shell find $(TSTDIR) -depth -name '*.$(TSTEXT)')
TESTER := test_$(NAME)

test: $(TST) $(TARGET)
	$(CC) $(CFLAGS) -lcheck $^ -o $(TESTER)
	./$(TESTER)

clean:
	rm -f *.o $(TARGET) $(TESTER) logs/*.log

.PHONY: clean all