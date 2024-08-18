import numpy as np
import matplotlib.pyplot as plt

A = np.array([3, 3])
B = np.array([6, 4])
C = np.array([8, 7])
D = np.array([5, 6])

plt.figure(figsize=(8, 6))

plt.plot([A[0], B[0]], [A[1], B[1]])
plt.plot([B[0], C[0]], [B[1], C[1]])
plt.plot([C[0], D[0]], [C[1], D[1]])
plt.plot([A[0], D[0]], [A[1], D[1]])

plt.text(A[0], A[1], 'A(3, 3)')
plt.text(B[0], B[1], 'B(6,4)')
plt.text(C[0], C[1], 'C(8, 7)')
plt.text(D[0], D[1], 'D(5, 6)')

plt.grid()
plt.axis('equal')
plt.show()
