import sys                                          # for path to external scripts
sys.path.insert(0, '/home/pushkar/matgeo/codes/CoordGeo')        # path to my scripts
import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# local imports
from line.funcs import *
from triangle.funcs import *
# Read data from file
c_values = [0.48, 0.6, 1.21]
A_x_values = []
A_y_values = []

with open('results.txt', 'r') as file:
    for line in file:
        c, A_x, A_y, _ = map(float, line.strip().split(','))
        A_x_values.append(A_x)
        A_y_values.append(A_y)

# Create plots for each c value

# Create and save three separate plots
for i, c in enumerate(c_values):
    plt.figure(figsize=(5, 5))
    
    # Coordinates of point A
    A_x = A_x_values[i]
    A_y = A_y_values[i]
    
    A= np.array([A_x, A_y])
    C= np.array([6, 0])
    B = np.array([0, 0])
    # Plot points A, B, and C
    x_AB = line_gen(A,B)
    x_BC = line_gen(B,C)
    x_AC = line_gen(A,C)
    
    plt.plot(x_AB[0, :], x_AB[1, :], label='$AB$')
    plt.plot(x_BC[0, :], x_BC[1, :], label='$BC$')
    plt.plot(x_AC[0, :], x_AC[1, :], label='$CA$')
    plt.text(A_x, A_y, f'A({A_x:.2f}, {A_y:.2f})', fontsize=10, ha='right')
    plt.text(B[0], B[1], 'B(0,0)')
    plt.text(C[0], C[1], 'C(6,0)')
    plt.title(f'Plot for c = {c}')
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.legend()
    plt.grid()
    plt.savefig(f'Plot_for_c_{c:.2f}.png')
    plt.close()  # Close the figure to avoid display
