import numpy as np
import numpy.linalg as la

def y(w0, w1, x):
    return (w1*x)+w0

def ys(w0, w1, xs):
    tab = []
    for i in range(len(xs)):
        tab.append(y(w0, w1, xs[i]))
    return tab

def calc_w0(x, t, n, w0, w1):
    s = 0
    for j in range(n):
        s += t[j]-y(w0, w1, x[j])
    return s/n

def calc_w1(x, t, n, w0, w1):
    s = 0
    for j in range(n):
        s += (t[j]-y(w0, w1, x[j]))*x[j]
    return s/n

def descente_gradient_mono(x, t, w0, w1, seuil, lr=0.01):
    n = len(x)
    #dw = seuil+1
    max_iter = 5000
    j = 0
    while j < max_iter:
        for i in range(n):
            dw = lr*calc_w0(x, t, n, w0, w1)
            w0 += dw
            dw = lr*calc_w1(x, t, n, w0, w1)
            w1 += dw
        j += 1
    return [w0, w1]

def cost(x, t, w0, w1):
    c = 0
    for i in range(len(x)):
        c += 0.5*((t[i]-y(w0, w1, x[i]))**2)
    return c/len(x)

def calc_wi(x, t, ws):
    s = 0
    return 0

def descente_gradient_multi(x, t, w, seuil, lr=0.01):
    n = len(x)
    max_iter = 1000
    j = 0
    cost = 0
    while j<max_iter:
        for i in range(len(x)):
            dw = lr*calc_wi(x, t, w[i])
        j += 1
    return 0
