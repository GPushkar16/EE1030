import sys                                  
sys.path.insert(0, '/home/matgeo/codes/CoordGeo/line')    
import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

from funcs import line_gen
from conicsfuncs import *
from trianglefuncs import *
import params
A = np.array([2,1])
B = np.array([-1, 0.25])
import matplotlib.pyplot as plt

# Initialize lists for x and y coordinates
x_vals = []
y_vals = []

# Read points from the file
with open("parabola_points.txt", "r") as file:
    for line in file:
        x, y = map(float, line.split())
        x_vals.append(x)
        y_vals.append(y)

# Plot the points
plt.plot(x_vals, y_vals, label="$x^2 = 4y$")
plt.xlabel('x')
plt.ylabel('y')
plt.title('Parabola: $x^2 = 4y$')

# use set_position
ax = plt.gca()
ax.spines['top'].set_color('none')
ax.spines['left'].set_position('zero')
ax.spines['right'].set_color('none')
ax.spines['bottom'].set_position('zero')

#Plotting all line

# Define the range of y values
y = np.linspace(-1, 2, 100)

# Define the equation x = 4y - 2
x = 4 * y - 2

# Create the plot
plt.plot(x, y, label='x = 4y - 2')



#Labeling the coordinates
tri_coords = np.vstack((A,B)).T
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A(2,1)','B(-1,0.25)']
for i, txt in enumerate(vert_labels):
       plt.annotate(txt,      # this is the text
                 (tri_coords[0,i], tri_coords[1,i]), # this is the point to label
                 textcoords="offset points",   # how to position the text
                 xytext=(0,10),     # distance from text to points (x,y)
                 ha='center')     # horizontal alignment can be left, right or center


#plt.fill_between(x1,x2,O,color='green', alpha=.2)
plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
plt.grid(True) # minor
plt.axis('equal')
plt.savefig('plot')
