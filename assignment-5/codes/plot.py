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
def affine_transform(P,c,x):
    return P@x + c

I =  np.eye(2)
e1 =  I[:,0]
#Input parameters



#circle parameters
V = np.array(([1,0],[0,0]))
u = np.array(([0,-2]))
f = 0

#for parabola
lamda,P = LA.eigh(V)
if(lamda[1] == 0):  # If eigen value negative, present at start of lamda
    lamda = np.flip(lamda) # e value
    P = np.flip(P,axis=1)   #e vectors in col

#
eta = u@P[:,0]
a = np.vstack((u.T + eta*P[:,0].T, V))
b = np.hstack((-f, eta*P[:,0]-u))
center = LA.lstsq(a,b,rcond=None)[0]
O = np.array([0,0])
n = np.sqrt(lamda[1])*P[:,0]
c = 0.5*(LA.norm(u)**2 - lamda[1]*f)/(u.T@n)
F = np.array(([0,0.7]))
fl = LA.norm(F)

#pmeters to generate parabola
num_points = 1700
delta = 20*np.abs(fl)/10
p_y = np.linspace(-2*np.abs(fl)-delta,2*np.abs(fl)+delta,num_points)
a = -2*eta/lamda[1]   # y^2 = ax => y'Dy = (-2eta)e1'y


##Generating all shapes
p_x = parab_gen(p_y,a)
p_std = np.vstack((p_x,p_y)).T


##Affine transformation
p = np.array([affine_transform(P,center,p_std[i,:]) for i in range(0,num_points)]).T
plt.plot(p[0,:], p[1,:])



#Generating  line
x_R1 = line_gen(A,B);


# use set_position
ax = plt.gca()
ax.spines['top'].set_color('none')
ax.spines['left'].set_position('zero')
ax.spines['right'].set_color('none')
ax.spines['bottom'].set_position('zero')

#Plotting all line
plt.plot(x_R1[0,:],x_R1[1,:],label='$line$')

#Labeling the coordinates
tri_coords = np.vstack((A,B,O)).T
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A(2,1)','B(-1,0.25)','O']
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
