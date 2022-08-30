import numpy as np
import matplotlib.pyplot as plt

with open("./output.txt") as f:
  data = f.readlines()
  
  y = np.array([float(row.split()[0]) for row in data])
  x = np.linspace(0, 150, 150)
  
  plt.plot(x,y,color = "red", label = "plot foda")

  plt.show()
