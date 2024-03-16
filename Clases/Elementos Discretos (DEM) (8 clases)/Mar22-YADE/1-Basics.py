# Create a Body
b = Body()
b.dict()

# Create a shape
s = Sphere()
s.dict()
s.radius = 1 

b.shape = s
b.dict()

# Create a Material
m = FrictMat()
m.dict()

# See the state
b.state.dict()
b.state.mass = 1
b.state.inertia = Vector3(1,1,1)

# Scene
from yade import qt
rndr = yade.qt.Renderer()
v=qt.View()

# Add the new body to the simulation
bodyId = O.bodies.append(b)
matId = O.materials.append(m)