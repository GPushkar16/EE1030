import ctypes
import matplotlib.pyplot as plt

# Load the shared library
# On Linux or macOS
lib = ctypes.CDLL('./libsection.so')

# On Windows
# lib = ctypes.CDLL('section.dll')

# Define the argument and return types of the function
lib.section_formula.argtypes = [
    ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double,
    ctypes.c_double, ctypes.c_double, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)
]
lib.section_formula.restype = None

# Create variables to store the result
px = ctypes.c_double()
py = ctypes.c_double()

# Coordinates of endpoints and ratio
x1, y1 = 3.0, 3.0
x2, y2 = 8.0, 7.0
x3, y3 = 6.0, 4.0
x4, y4 = 5.0, 6.0
m, n = 1.0, 1.0

# Call the function
lib.section_formula(x1, y1, x2, y2, m, n, ctypes.byref(px), ctypes.byref(py))

# Resultant point
px_value = px.value
py_value = py.value

# Print the result
print(f'The coordinates of the point dividing the line segment in the ratio {m}:{n} are ({px_value}, {py_value})')

# Plotting
plt.figure(figsize=(8, 6))

# Plot the endpoints
plt.plot([x1, x2], [y1, y2], 'ro-', linestyle='--')
plt.plot([x1, x4], [y1, y4])
plt.plot([x3, x2], [y3, y2])
plt.plot([x3, x1], [y3, y1])
plt.plot([x4, x2], [y4, y2])
plt.plot([x3, x4], [y3, y4], 'ro-', linestyle='--')
# Plot the resultant point
plt.plot(px_value, py_value, 'bo', label='Mid Point(O)')

# Annotate the points
plt.text(x1, y1, ' A(3,3)', fontsize=12, verticalalignment='bottom', horizontalalignment='right')
plt.text(x2, y2, ' C(8,7)', fontsize=12, verticalalignment='bottom', horizontalalignment='left')
plt.text(x3, y3, ' B(6,4)', fontsize=12, verticalalignment='bottom', horizontalalignment='right')
plt.text(x4, y4, ' D(5,6)', fontsize=12, verticalalignment='bottom', horizontalalignment='right')
plt.text(px_value, py_value, ' O(5.5,5)', fontsize=12, verticalalignment='bottom', horizontalalignment='left')

# Set labels and title
plt.xlabel('X-coordinate')
plt.ylabel('Y-coordinate')
plt.title('Plot of Line Segment and Dividing Point')
plt.legend()
plt.grid(True)

# Show the plot
plt.savefig('parallelogram.png')

