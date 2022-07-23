import random as rd
import numpy as np
import matplotlib.pyplot as plt
from algo import *

x = [0.1, 0.2, 0.3, 0.3, 0.5, 0.4]
t = [3.5, 5.2, 4.5, 5.3, 6.5, 4.1]
z = [3.0, 4.0, 4.8, 5.3, 6.9, 6.1]

w0 = rd.random()
w1 = rd.random()
res = descente_gradient_mono(x, t, w0, w1, 0.01)
y = ys(res[0], res[1], x)
c = cost(x, t, res[0], res[1])
print("w0 = ", res[0])
print("w1 = ", res[1])
print("cost = ", c)

plt.figure("Descente du gradient")
plt.xlabel("x")
#plt.ylabel("y")
plt.plot(x, t, "ob", label="t")
plt.plot(x, y, "r", label="y")
plt.grid()
plt.show()

####################################################

w0 = rd.random()
w1 = rd.random()
res = descente_gradient_mono(x, z, w0, w1, 0.01, lr=0.01)
y = ys(res[0], res[1], x)
c = cost(x, t, res[0], res[1])
print("w0 = ", res[0])
print("w1 = ", res[1])
print("cost = ", c)

plt.figure("Descente du gradient")
plt.xlabel("x")
#plt.ylabel("y")
plt.plot(x, z, "ob", label="t")
plt.plot(x, y, "r", label="y")
plt.grid()
plt.show()

####################################################

w0 = 0.9
w = [1.3, 0.2]
a = np.array([[0.5, 3.0], [0.4, 3.0], [0.4, 4.0], [2.3, 5.0], [2.1, 5.0], [2.2, 4.5]])
t = np.array([1, 1, 1, -1, -1, -1])
plt.plot(a[0:3, 0], a[0:3, 1], 'ro')
plt.plot(a[3:6, 0], a[3:6, 1], 'bo')
x2 = -a[:,0]*(w[0]/w[1]) - (w0/w[1])
plt.plot(a[:,0], x2, 'r')
plt.show()

# import pandas
