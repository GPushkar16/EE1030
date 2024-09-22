import sys                                  
sys.path.insert(0, '/home/matgeo/codes/CoordGeo/line')    
import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

from funcs import line_gen
import params

A = np.array(([1.21, 1.21]))
B = np.array(([0, 0]))
C = np.array(([6, 0]))

x_AB = line_gen(A,B)
x_BC = line_gen(B,C)
x_AC = line_gen(A,C)

plt.figure(figsize=(8, 6))

plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_AC[0,:],x_AC[1,:],label='$AC$')


plt.text(A[0], A[1], 'A(1.21,1.21)')
plt.text(B[0], B[1], 'B(0,0)')
plt.text(C[0], C[1], 'C(6,0)')
plt.xlabel('X-coordinate')
plt.ylabel('Y-coordinate')
plt.title('Plot of the triangle ABC such that difference of length between AB and AC is 4cm')
plt.legend()
plt.grid(True)


plt.savefig('plot3.png')
