from PIL import Image
import numpy as np
from io import StringIO

#data = np.genfromtxt("output.txt")
#print(data)

data = np.genfromtxt("output.txt", delimiter=',')
print(data)
# Convert to image and save
img = Image.fromarray(data, 'RGB')
img.save('result.png')

