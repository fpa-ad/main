import libFCpython as l

i = l.interface()
# this is an example for 2 streams of the same species
# a description of the arguments can be found in src/interface.h
i.create_simulation(50, 1, 0.1, 1, 0.05, 2, [100, 100], [-1,-1], [[[0], [0], [0, 1, 2], [0, 1, 0]], [[0], [0], [0, 1, -2], [0, 1, 0]]], 1, [[0, 0, 0]])
i.run_simulation(10, 0)
