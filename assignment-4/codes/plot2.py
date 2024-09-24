import sys                                  
sys.path.insert(0, '/home/matgeo/codes/CoordGeo/line')    
import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

from funcs import line_gen
import params

# Initialize lists to hold the points
A = []
B = []
C = []

with open("output2.txt", "r") as file:
    for line in file:
        # Split the line by spaces
        parts = line.strip().split()
        point_id = parts[0]  # The first part is the point identifier
        values = list(map(float, parts[1:]))  # Convert the rest to floats
        
        # Assign values to respective points
        if point_id == 'A':
            A = values
        elif point_id == 'B':
            B = values
        elif point_id == 'C':
            C = values

# Convert lists to NumPy arrays
A = np.array(A)
B = np.array(B)
C = np.array(C)

x_AB = line_gen(A,B)
x_BC = line_gen(B,C)
x_AC = line_gen(A,C)

plt.figure(figsize=(8, 6))

plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_AC[0,:],x_AC[1,:],label='$AC$')


plt.text(A[0], A[1], 'A(0.42,0.42)')
plt.text(B[0], B[1], 'B(0,0)')
plt.text(C[0], C[1], 'C(6,0)')
plt.xlabel('X-coordinate')
plt.ylabel('Y-coordinate')
plt.title('Plot of the triangle ABC such that difference between AB and AC is 5.2 cm')
plt.legend()
plt.grid(True)


plt.savefig('plot2.png')
