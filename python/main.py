import libFCpython as l

i = l.interface()
i.create_simulation(10, 1, 0.1, 1, 0.01, 2, [10000,10000], [1,-1], [[[0], [0], [0, 0.02], [0, 0.02]],[[0], [0], [1, 0.02, 0.05, 0.33], [0, 0.02]]], 1, [[0, 0, 0]])
i.run_simulation(30, 1)