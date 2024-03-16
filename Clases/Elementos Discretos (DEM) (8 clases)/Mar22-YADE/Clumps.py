from yade import qt

yade.qt.Renderer()
qt.View()

#Create a material
matId = O.materials.append(FrictMat(frictionAngle = 0.1, label = 'spheresMat'))

from yade import ymport
id_HouGL = O.bodies.append(ymport.gmsh(
    "hourglass.mesh",
    color=(0,0,1), scale = 1000.0))

def read_x_y_z_r_intoList(fileName, shift = Vector3.Zero, scale =1.0):
    infile = open(fileName, 'r')
    lines = infile.readlines()
    infile.close()
    cl_list = []
    for line in lines:
        data = line.split(',')
        if (data[0][0] == '#'):
            continue
        else:
            pos = Vector3(float(data[0]), float(data[1]), float(data[2]))
            cl_list.append((shift + scale*pos, scale*float(data[3])))
            
    return cl_list


from yade import pack
sp = pack.SpherePack()
file = 'Chess_Queen_100_spheres.txt'
Queen = pack.SpherePack(read_x_y_z_r_intoList(file, scale = 0.0825)) #8.5cm is the height of the queen
sp.makeClumpCloud((0,0,12),(13,13,31),[Queen], num =1 ,seed =1)
b = sp.toSimulation(material = 'spheresMat')
O.bodies.updateClumProperties(discretization=10)


#Create the engine
O.engine = [
    ForceResetter(),
    InsertionSortCollider([Bol_Sphere_Aabb(),Bol_Facet_Aabb()], label = 'collider'),  #Contact Detection 
    IntereactionLoop(
        [Ig2_Sphere_Sphere_ScGeom(), Ig2_Facet_Sphere_ScGeom()],   #Shape Interaction
        [Ip2_FrictMat_FrictMat_MindlinPhys(en = 0.1)],                    #Material Interaction
        [Law2_ScGeom_MindlinPhys_Mindlin()],                       #Force Model
    ),
    NewtonIntegrator(gravity = [0,0,-10.0], damping = 0, 
                     exactAsphericalRot = True),
    RotationEngine(
        ids = id_HouGL, 
        angularVelocity = math.pi/(O.dt*16000000),
        rotateAroundZero = True,
        rotationAxis = Vector3(0,0,1),
        zeroPoint = Vector3(0,0,0),
        dead = False,
        label = 'rotEng'),
]

O.dt = 1.5 * PWaveTimeStep()