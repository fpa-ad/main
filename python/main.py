import libFCpython as l

i = l.interface()
i.create_simulation(10, 10, 0.2, 0.2, 0.001, 2, [1000,1000], [-1,1], [[[0], [0], [1, 15, 36, 0.33], [0, 15]],[[0], [0], [0, 15], [0, 15]]], 1, [[0, 0, 0]])
i.run_simulation(10, 0.03)