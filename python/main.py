import libFCpython as l
import numpy as np

i = l.interface()
i.create_simulation(50, 1, 0.1, 1, 0.05, 2, [10000,10000], [-1,-1], [[[0], [0], [0, 1, 3], [0, 1, 0]],[[0], [0], [0, 1, -3], [0, 1, 0]]], 1, [[0, 0, 0]])
#i.create_simulation(500, 1, 1, 1, 0.05, 1, [10000], [-1], [[[0], [0], [1, 1, 3, 0.33], [0, 1, 0]]], 1, [[0, 0, 0],[0,0,1./np.sqrt(5.)]])
i.run_simulation(200, 0)