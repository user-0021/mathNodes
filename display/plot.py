import matplotlib.pyplot as plt
import math 
import numpy as np

isRunninng = True

def on_close(event):
    global isRunninng
    isRunninng = False

plt.figure().canvas.mpl_connect('close_event', on_close)
plt.draw()

xAxsis = []
yAxsis = []

while isRunninng:
    s = input().split()
    xAxsis.append(float(s[0]))
    yAxsis.append(float(s[1]))
    plt.plot(xAxsis,yAxsis)    
    plt.draw()
    plt.pause(10)
