import numpy as np
import matplotlib.pyplot as plt
import random as rd
#import pandas

"""
data structure
larg des cépals, larg des , long des , classe (1 ou -1)
5.1, 3.5, 1.4, 0.2, 1
"""

def extract_infos(fname):
    a1 = []
    b1 = []
    c1 = []
    a2 = []
    b2 = []
    c2 = []
    file = open(fname, 'r')
    for l in file.readlines():
        tab = l.split(',')
        if (tab[3]=='1'):
            a1.append(int(tab[0]))
            b1.append(int(tab[1]))
            c1.append(int(tab[2]))
        elif (tab[3]=='-1'):
            a2.append(int(tab[0]))
            b2.append(int(tab[1]))
            c2.append(int(tab[2]))
    file.close()
    return [a1, b1, c1, a2, b2, c2]

def perceptron(c1, c2, seuil):
    w = rd.random()
    max_iter = 1000
    card = 0
    j = 0
    while (card>seuil) and (j < max_iter):
        dw = 0
        card = 0
        for i in range(len(c1)):
            if ll:
                card += 1
                dw +=
        j += 1
    return 0
