from yade import qt

yade.qt.Renderer()
qt.View()

#Create a material

matId = O.materials.append(FrictMat())


#Create a box
O.bodies.append(geom.facetBox((0.5,0.5,0.5),(.5,.5,.5),material=matId,wallMask=31))


from yade import pack
sp = pack.SpherePack()
sp.makeCloud((0,0,0.5),(1,1,1.5),rMean=.05,rRelFuzz=.5,num=10 ,seed =2)
sp.toSimulation()


#Create the engine
O.engine = [
    ForceResetter(),
    InsertionSortCollider([Bol_Sphere_Aabb(),Bol_Facet_Aabb()], label = 'collider'),  #Contact Detection 
    IntereactionLoop(
        [Ig2_Sphere_Sphere_ScGeom(), Ig2_Facet_Sphere_ScGeom()],   #Shape Interaction
        [Ip2_FrictMat_FrictMat_MindlinPhys()],                    #Material Interaction
        [Law2_ScGeom_MindlinPhys_Mindlin()],                       #Force Model
    ),
    NewtonIntegrator(gravity = [0,0,-10.0], damping = 0),
]

O.dt = 0.8 * PWaveTimeStep()

#Plot Energy
O.trackEnergy = True

from yade import plot

plot.plots={'i':('total','potential','kinetic')}
plot.plot()

def addData():
    plot.addData( i=O.iter, 
                total=O.energy.total(),
                potential=O.energy.potential(), 
                kinetic=O.energy.kinetic()
                )

O.engines = O.engines + [PyRunner(command='addData()',iterPeriod=100)]

O.saveTmp()

    

