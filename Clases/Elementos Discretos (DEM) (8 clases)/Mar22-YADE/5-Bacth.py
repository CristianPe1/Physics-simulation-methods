readParamsFromTable(frec=1)
from yade.params import table

import pandas as pd
data = pd.DataFrame(columns = ['t','z'])

#Create the materials
matId = O.materials.append(FrictMat())
sphere = sphere(Vector3(0,0,5),1.0,material = matId)
sphereId = O.bodies.append(sphere)

wall = wall(Vector3(0,0,0),2,sense =1,material = matId)
wallId = O.bodies.append(wall)

#Create the engine
O.engines = [
    ForceResetter(),
    InsertionSortCollider([Bo1_Sphere_Aabb(),Bo1_Wall_Aabb()], label = 'collider'),  #Contact Detection 
    InteractionLoop(
        [Ig2_Sphere_Sphere_ScGeom(), Ig2_Wall_Sphere_ScGeom()],   #Shape Interaction
        [Ip2_FrictMat_FrictMat_MindlinPhys(en = 0.1)],                    #Material Interaction
        [Law2_ScGeom_MindlinPhys_Mindlin()],                       #Force Model
    ),
    NewtonIntegrator(gravity = [0,0,-10.0], damping = 0),
    HarmonicMotionEngine(
        ids = [wallId], 
        A = Vector3(0,0,1),
        fi = Vector3(0,0,0),
        f = Vector3(0,0,table.frec),
        ),
    PyRunner(command = 'save_data()',iterPeriod = 1000)
]

#Scenein a try statement so it does not guive problems in batch or 
#clusters
if not yade.utils.runningInBatch():
    try:
        from yade import qt 
        yade.qt.Renderer()
        qt.View()
    except: pass
    
def save_data():
    global data
    if yade.utils.runningInBatch():
        #Get the z position of the sphere
        z= O.bodies[SphereId].state.pos[2]
        #Add a new row to the dataframe with the 
        # time and the z position
        data.loc[len(data)] = [O.iter*O.dt,z]
        
        
#Set the time step
O.dt = 0.1e-4
O.stopAtTime = 20000*O.dt
waitIfBatch()


if yade.utils.runningInBatch():
    data.to_csv(f'Data/frec-{table.frec}.csv', index =False)
