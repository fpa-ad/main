import libFCpython as l

i = l.interface()
#i.create_simulation(50, 1, 0.1, 1, 0.05, 2, [10000,10000], [1,-1], [[[0], [0], [0, 0.4, 2], [0, 0.4, 0]],[[0], [0], [0, 0.4, -2], [0, 0.4, 0]]], 1, [[0, 0, 0]])
i.create_simulation(50, 1, 0.1, 1, 0.05, 1, [10000], [-1], [[[0], [0], [0, 1, 0], [0, 1, 0]]], 2, [[0, 0, 0],[0,0,1./5.]])
i.run_simulation(200, 0)