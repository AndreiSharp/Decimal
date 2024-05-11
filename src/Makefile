NAME := s21_decimal

# ----------------- compiler -----------------  
CC ?= gcc
CFLAGS ?= -Wall -Werror -Wextra

# ----------------- includes -----------------  
INCDIR := ./include
INC := s21_decimal.h s21_decimal_another.h s21_decimal_arithmetic.h s21_decimal_binary.h s21_decimal_comprasion.h s21_decimal_convertation.h s21_decimal_help.h s21_decimal_types.h 

# ----------------- C files -------------------
BINDIR := ./binary
HELPDIR := ./helper
CONVDIR := ./convertation
ARITHMDIR := ./arithmetic
COMPDIR := ./comprasion
ANOTHERDIR := ./another

BIN := $(BINDIR)/s21_binary_function.c

HELP := 

CONV := $(CONVDIR)/s21_from_decimal_to_float.c
CONV += $(CONVDIR)/s21_from_decimal_to_int.c 
CONV += $(CONVDIR)/s21_from_float_to_decimal.c
CONV += $(CONVDIR)/s21_from_int_to_decimal.c

ARITHM := $(ARITHMDIR)/s21_add.c
ARITHM += $(ARITHMDIR)/s21_mul.c
ARITHM += $(ARITHMDIR)/s21_div.c
ARITHM += $(ARITHMDIR)/s21_sub.c

ANOTHER := $(ANOTHERDIR)/s21_floor.c
ANOTHER += $(ANOTHERDIR)/s21_negate.c
ANOTHER += $(ANOTHERDIR)/s21_round.c
ANOTHER += $(ANOTHERDIR)/s21_truncate.c

COMP := $(COMPDIR)/s21_is_equal.c 
COMP += $(COMPDIR)/s21_is_greater.c 
COMP += $(COMPDIR)/s21_is_greater_or_equal.c 
COMP += $(COMPDIR)/s21_is_less.c 
COMP += $(COMPDIR)/s21_is_less_or_equal.c 
COMP += $(COMPDIR)/s21_is_not_equal.c

# ----------------- objects -----------------  
OBJS_BIN = $(patsubst %.c, %.o, $(BIN))
OBJS_HELP = $(patsubst %.c, %.o, $(HELP))
OBJS_CONV = $(patsubst %.c, %.o, $(CONV))
OBJS_ARITHM = $(patsubst %.c, %.o, $(ARITHM))
OBJS_ANOTHER = $(patsubst %.c, %.o, $(ANOTHER))
OBJS_COMP = $(patsubst %.c, %.o, $(COMP))

# ----------------- tests -----------------
TSTDIR := ./test
TSTEXT := $(SRCEXT)
TST := $(shell find $(TSTDIR) -depth -name '*.$(TSTEXT)')
TESTER := test_$(NAME)


# ---------------- targets -----------------
$(OBJS_BIN): $(BIN)
	$(CC) -c $^ -o $@
$(OBJS_HELP): $(HELP)
	$(CC) -c $^ -o $@
$(OBJS_ARITHM): $(ARITHM)
	$(CC) -c $^ -o $@
$(OBJS_CONV): $(CONV)
	$(CC) -c $^ -o $@
$(OBJS_COMP): $(COMP)
	$(CC) -c $^ -o $@
$(OBJS_ANOTHER): $(ANOTHER) 
	$(CC) -c $^ -o $@

$(NAME).a: $(OBJS_BIN) $(OBJS_HELP) $(OBJS_ARITHM) $(OBJS_CONV) $(OBJS_COMP) $(OBJS_ANOTHER)
	$(CC)


clean:

.PHONY all clean test
