import libFCpython as l

i = l.interface()
i.create_simulation(1.0, 1.0, 0.1, 0.1, 0.01, 1, [10], [1], [[0], [0], [0, 0], [0, 0]], 1, [[1, 0, 0]])
i.run_simulation(1, 0.5)