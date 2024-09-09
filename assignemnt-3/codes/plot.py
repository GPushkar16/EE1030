import numpy as np
import matplotlib.pyplot as plt

A = np.array(([4 , 4]))
B = np.array(([1, 0]))
C = np.array(([4, -4]))

plt.figure(figsize=(8, 6))

plt.plot([A[0], B[0]], [A[1], B[1]])
plt.plot([B[0],C[0]], [B[1], C[1]])


plt.text(A[0], A[1], 'A(4,4)')
plt.text(B[0], B[1], 'B(1,0)')
plt.text(C[0], C[1], 'C(4,-4)')
plt.xlabel('X-coordinate')
plt.ylabel('Y-coordinate')
plt.title('Plot of the two possible points A and C which are 5 units away from B')
plt.legend()
plt.grid(True)


plt.savefig('plot.png')


