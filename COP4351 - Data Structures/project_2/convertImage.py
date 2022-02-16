import matplotlib.pyplot as plt
from numpy import genfromtxt

my_data = genfromtxt('nn_result_1.txt', delimiter=',')
#this makes an array from a file
plt.imshow(my_data, cmap="gray")
#this makes a image with the gray color-map which only takes in one parameter per pixel
plt.show()
