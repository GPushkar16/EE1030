import sys                                  
sys.path.insert(0, '/home/matgeo/codes/CoordGeo/line')    
import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

from funcs import line_gen
import params

A = np.array(([4 , 4]))
B = np.array(([1, 0]))
C = np.array(([4, -4]))

x_AB = line_gen(A,B)
x_BC = line_gen(B,C)

plt.figure(figsize=(8, 6))

plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')


plt.text(A[0], A[1], 'A(4,4)')
plt.text(B[0], B[1], 'B(1,0)')
plt.text(C[0], C[1], 'C(4,-4)')
plt.xlabel('X-coordinate')
plt.ylabel('Y-coordinate')
plt.title('Plot of the two possible points A and C which are 5 units away from B')
plt.legend()
plt.grid(True)


plt.savefig('plot.png')


