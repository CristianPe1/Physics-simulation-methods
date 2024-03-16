from yade import qt

yade.qt.Renderer()
qt.View()

#Create a material

matId = O.materials.append(FrictMat())


# Parameters: 
#   center (Vector3) – center of the box
#   extents (Vector3) – half lengths of the box sides
#   orientation (Quaternion) – orientation of the box
#   wallMask (bitmask) – determines which walls will be created, in the order -x (1), +x (2), -y (4), +y (8), -z (16), +z (32). The numbers are ANDed; the default 63 means to create all walls
#   **kw – (unused keyword arguments) passed to utils.facet
# Returns:    
#   list of facets forming the box
O.bodies.append(geom.facetBox((.5, .5, .5), (.5, .5, .5), wallMask=31))



from yade import pack
sp = pack.SpherePack()
# generate randomly spheres with uniform radius distribution
# makeCloud((SpherePack)arg1[, (Vector3)minCorner=Vector3(0, 0, 0)[, (Vector3)maxCorner=Vector3(0, 0, 0)[, (float)rMean=-1[, (float)rRelFuzz=0[, (int)num=-1[, (bool)periodic=False[, (float)porosity=0.65[, (object)psdSizes=[][, (object)psdCumm=[][, (bool)distributeMass=False[, (int)seed=-1[, (Matrix3)hSize=Matrix3(0, 0, 0, 0, 0, 0, 0, 0, 0)]]]]]]]]]]]]) → int :
#   Create a random cloud of particles enclosed in a parallelepiped. The resulting packing is a gas-like state with no contacts between particles initially. Usually used as a first step before reaching a dense packing.
#
#Parameters: 
#   minCorner (Vector3) – lower corner of an axis-aligned box
#   maxCorner (Vector3) – upper corner of an axis-aligned box
#   3hSize (Matrix3) – base vectors of a generalized box (arbitrary parallelepiped, typically Cell::hSize), superseeds minCorner and maxCorner if defined. For periodic boundaries only.
#   rMean (float) – mean radius or spheres
#   rRelFuzz (float) – dispersion of radius relative to rMean
#   num (int) – number of spheres to be generated. If negative (default), generate as many as possible with stochastic sizes, ending after a fixed number of tries to place the sphere in space, else generate exactly num spheres with deterministic size distribution.
#   periodic (bool) – whether the packing to be generated should be periodic
#   porosity (float) – initial guess for the iterative generation procedure (if num>1). The algorithm will be retrying until the number of generated spheres is num. The first iteration tries with the provided porosity, but next iterations increase it if necessary (hence an initialy high porosity can speed-up the algorithm). If psdSizes is not defined, rRelFuzz (z) and num (N) are used so that the porosity given (ρ) is approximately achieved at the end of generation, rm=V(1−ρ)43π(1+z2)N−−−−−−−−√3. The default is ρ=0.5. The optimal value depends on rRelFuzz or psdSizes.
#   psdSizes – sieve sizes (particle diameters) when particle size distribution (PSD) is specified.
#   psdCumm – cummulative fractions of particle sizes given by psdSizes; must be the same length as psdSizes and should be non-decreasing.
#   distributeMass (bool) – if True, given distribution will be used to distribute sphere’s mass rather than radius of them.
#   seed – number used to initialize the random number generator.
# Returns:    
#   number of created spheres, which can be lower than num depending on the method used.
sp.makeCloud((0,0,0.5),(1,1,1.5),rMean=.05,rRelFuzz=.5,num=10 ,seed =2)
sp.toSimulation()


#Create the engine
O.engines = [
    ForceResetter(),
    InsertionSortCollider([Bo1_Sphere_Aabb(),Bo1_Facet_Aabb()], label = 'collider'),  #Contact Detection 
    InteractionLoop(
        [Ig2_Sphere_Sphere_ScGeom(), Ig2_Facet_Sphere_ScGeom()],   #Shape Interaction
        [Ip2_FrictMat_FrictMat_MindlinPhys()],                    #Material Interaction
        [Law2_ScGeom_MindlinPhys_Mindlin()],                       #Force Model
    ),
    NewtonIntegrator(gravity = [0,0,-10.0], damping = 0),
]

# Run sim here, see what happens
O.dt = .8 * PWaveTimeStep()

#Plot Energy
O.trackEnergy = True

from yade import plot

plot.plots={'i':('total','potential','kinetic')}
plot.plot()

def addData():
    plot.addData(
        i = O.iter, 
        total = O.energy.total(), 
        potential = O.energy['gravWork'], 
        kinetic = O.energy['kinetic'])

O.engines = O.engines + [PyRunner(command='addData()',iterPeriod=100)]

O.saveTmp()

    

