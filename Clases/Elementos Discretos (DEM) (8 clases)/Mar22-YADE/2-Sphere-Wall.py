from yade import qt

yade.qt.Renderer()
qt.View()

#Create a material
matId = O.materials.append(FrictMat())


#Create a sphere
# yade.utils.sphere(center, radius, dynamic=None, fixed=False, wire=False, color=None, highlight=False, material=-1, mask=1)[source]
# Create sphere with given parameters; mass and inertia computed automatically.
#
# Last assigned material is used by default (material = -1), and utils.defaultMaterial() will be used if no material is defined at all.
#
# Parameters: 
#   center (Vector3) – center
#   radius (float) – radius
#   dynamic (float) – deprecated, see “fixed”
#   fixed (float) – generate the body with all DOFs blocked?
#   material –
#   specify Body.material; different types are accepted:
#   int: O.materials[material] will be used; as a special case, if material==-1 and there is no shared materials defined, utils.defaultMaterial() will be assigned to O.materials[0]
#   string: label of an existing material that will be used
#   Material instance: this instance will be used
#   callable: will be called without arguments; returned Material value will be used (Material factory object, if you like)
#   mask (int) – Body.mask for the body
#   wire – display as wire sphere?
#   highlight – highlight this body in the viewer?
#   Vector3-or-None – body’s color, as normalized RGB; random color will be assigned if None.
# Returns:    
#   A Body instance with desired characteristics.
sphere = yade.utils.sphere(Vector3(0,0,5), 1.0, material = matId)
O.bodies.append(sphere)

# Create the flor
# yade.utils.wall(position, axis, sense=0, color=None, material=-1, mask=1)
#   Return ready-made wall body.
#
# Parameters: 
#   position (float-or-Vector3) – center of the wall. If float, it is the position along given axis, the other 2 components being zero
#   axis (∈{0,1,2}) – orientation of the wall normal (0,1,2) for x,y,z (sc. planes yz, xz, xy)
#   sense (∈{-1,0,1}) – sense in which to interact (0: both, -1: negative, +1: positive; see Wall)
wall = yade.utils.wall(Vector3(0,0,0), 2, sense=1, material = matId)
O.bodies.append(wall)




#Create the engine
O.engines = [
    ForceResetter(),
    InsertionSortCollider([Bo1_Sphere_Aabb(), Bo1_Wall_Aabb()]), # Contact Detection
    InteractionLoop(
            [Ig2_Sphere_Sphere_ScGeom(), Ig2_Wall_Sphere_ScGeom()],            # Shape Interactions 
            [Ip2_FrictMat_FrictMat_MindlinPhys()],                             # Material Interactions and physics
            [Law2_ScGeom_MindlinPhys_Mindlin()],                               # Force Model
    ),
    NewtonIntegrator(damping=0, gravity=[0,0,-10.0]),
]

O.dt = 0.1e-4

#ScGeom Geometrical contact detection 3D