from yade import qt

yade.qt.Renderer()
qt.View()

#Create a material

matId = O.materials.append(FrictMat())


#Create a sphere
O.bodies(utils.sphere(center=(0,0,5),radius=1,material=matId))


#Create a wall
wall = utils.wall((0,0,0),2,material=matId)
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
    NewtonIntegrator(damping=0, gravity=[0,0,-10.0], damping = 0),
]

O.dt = 0.1e-6

#ScGeom Geometrical contact detection 3D