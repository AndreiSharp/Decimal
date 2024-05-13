from decimal import *

def to_s21_decimal(a):
    print(a)
    print(a.as_tuple())
    mantis = ""
    for x in a.as_tuple().digits:
        mantis += str(x)
    print(mantis)
    mantis = bin(int(mantis))[2:]
    mantis = "0" * (96 - len(mantis)) + mantis 
    print(mantis)
    print("BLOCKS")
    print(mantis[0:32] + '\n' + mantis[32:64] + '\n' + mantis[64:96])
    print("EXPONENT")
    print(abs(a.as_tuple().exponent))
    print("SIGN")
    print(a.as_tuple().sign)
    print()

getcontext().Emin = -28
getcontext().Emax = 28

a = Decimal(12323.231)
b = Decimal(222.02)
c = a + b

to_s21_decimal(a)
to_s21_decimal(b)
to_s21_decimal(c)
