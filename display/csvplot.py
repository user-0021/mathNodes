import matplotlib.pyplot as plt
import pandas as pd

isRunninng = True

def on_close(event):
    global isRunninng
    isRunninng = False

plt.figure().canvas.mpl_connect('close_event', on_close)

xAxsis = []
yAxsis = []

inputFilePath = input()

while isRunninng:
	input_csv = pd.read_csv(inputFilePath)
	for key in input_csv.keys():
		if key != input_csv.keys()[0]:
			plt.plot(input_csv[input_csv.keys()[0]],input_csv[key],color = 'r')
	
	plt.draw()
	plt.pause(1)

