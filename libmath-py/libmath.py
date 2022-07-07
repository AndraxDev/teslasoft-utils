r"""
Name: libmath-py
Version: 1.0
Licenced under Apache 2.0
"""

# from os import system  # for debug
import sys

sys.setrecursionlimit(2000)  # Must be more than delta to avoid errors

delta = 100  # Iterations
const_exp = 2.718281828459045235360287471135266249775724709369995957496696762772407663035354759457138217852516642742747
const_pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148


def factorial(n):
    if n == 1:
        return float(n)
    elif n < 1:
        return float(0)
    else:
        return float(n * factorial(n - 1))


def power(x, y):
    return x ** y


def absolute(x):
    if x < 0:
        return -x
    else:
        return x


def square_root(x):
    return x ** 0.5


def root(x, y):
    return x ** (1 / y)


def radian(n):
    return (const_pi / 180) * n


def sine(x):
    cg = 0
    for i in range(delta):
        if i % 2 == 0:
            ph1 = x ** (i + 1)
            ph2 = factorial(i + 1)
            ph3 = ph1 / ph2
            if i % 4 == 0:
                cg += ph3
            else:
                cg -= ph3
    return cg


def cosine(x):
    return (1 - sine(x) ** 2) ** 0.5


# You need a powerful device to run this function. We recommend to use const_pi
def pi():
    cg = 0
    for i in range(delta):
        if i % 2 == 0:
            ph3 = 4 / (i + 1)
            if i % 4 == 0:
                cg += ph3
            else:
                cg -= ph3
    return cg


def tangent(x):
    return sine(x) / cosine(x)


def cotangent(x):
    return cosine(x) / sine(x)


def exponent(x):
    return const_exp ** x


def sigmoid(x):
    return 1 / (1 + exponent(-x))


def sigmoid_derivative(x):
    return x * (1 - x)

# For debug: print(str(sine(radian(45))))
# For debug: system("pause >nul")
