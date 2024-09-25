import sys
sys.path.insert(0, '/home/matgeo/codes/CoordGeo/line')
import numpy as np
import matplotlib.pyplot as plt
from funcs import line_gen

# Initialize lists to hold the points for each output file
points = {'A': [], 'B': [], 'C': []}
files = ['output1.txt', 'output2.txt', 'output3.txt']

# Function to read points from a file
def read_points_from_file(filename):
    local_points = {'A': [], 'B': [], 'C': []}
    try:
        with open(filename, "r") as file:
            for line in file:
                parts = line.strip().split()
                point_id = parts[0]  # The first part is the point identifier
                values = list(map(float, parts[1:]))  # Convert the rest to floats
                if point_id in local_points:
                    local_points[point_id] = values
    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.")
        sys.exit(1)
    except ValueError:
        print(f"Error: Could not convert data to float in '{filename}'. Please check the file format.")
        sys.exit(1)
    
    return local_points

# Read points from each file and store in the points dictionary
for filename in files:
    file_points = read_points_from_file(filename)
    points['A'].append(file_points['A'])
    points['B'].append(file_points['B'])
    points['C'].append(file_points['C'])

# Convert lists to NumPy arrays
points_A = [np.array(p) for p in points['A']]
points_B = [np.array(p) for p in points['B']]
points_C = [np.array(p) for p in points['C']]

# Create the plot
plt.figure(figsize=(10, 8))

# Colors for different files
colors = ['blue', 'green', 'red']
labels = ['Output 1', 'Output 2', 'Output 3']

for i in range(len(points_A)):
    x_AB = line_gen(points_A[i], points_B[i])
    x_BC = line_gen(points_B[i], points_C[i])
    x_AC = line_gen(points_A[i], points_C[i])

    plt.plot(x_AB[0, :], x_AB[1, :], label=f'AB ({labels[i]})', color=colors[i])
    plt.plot(x_BC[0, :], x_BC[1, :], label=f'BC ({labels[i]})', color=colors[i], linestyle='--')
    plt.plot(x_AC[0, :], x_AC[1, :], label=f'AC ({labels[i]})', color=colors[i], linestyle=':')

    # Label points with their coordinates
    plt.text(points_A[i][0], points_A[i][1], f'A({points_A[i][0]:.2f},{points_A[i][1]:.2f})', fontsize=10, ha='right')
    plt.text(points_B[i][0], points_B[i][1], f'B({points_B[i][0]:.2f},{points_B[i][1]:.2f})', fontsize=10, ha='right')
    plt.text(points_C[i][0], points_C[i][1], f'C({points_C[i][0]:.2f},{points_C[i][1]:.2f})', fontsize=10, ha='right')

# Set plot labels and title
plt.xlabel('X-coordinate')
plt.ylabel('Y-coordinate')
plt.title('Plot of Triangles ABC from Multiple values pf AB-AC')
plt.legend()
plt.grid(True)

# Save the plot
plt.savefig('plot_triangles.png')
plt.show()  # Show the plot in addition to saving it

