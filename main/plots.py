import os
import matplotlib.pyplot as plt
import numpy as np
import imageio

if os.path.exists("output") and os.path.isdir("output"):
    sims = os.listdir("output")
    for sim in sims:
        if not os.path.isdir("output/"+sim):
            continue
        print("---- Simulation: ", sim, " ----")
        files = os.listdir("output/"+sim)
        # frames for the gif
        frames = []
        # read basic info
        with open("output/"+sim+"/README.txt") as f:
            header = f.readline().split()
            Lx = float(header[1])
            Ly = float(header[3])
            dx = float(header[5])
            dy = float(header[7])
        for file in files:
            if not ".txt" in file:
                continue
            if (file == "README.txt"):
                continue
            print(file)
            fig = plt.figure()
            with open("output/"+sim+"/"+file) as f:
                # read time and number of particle types
                header = f.readline().split()
                t = float(header[0])
                n = int(header[2])
                ctm = []
                # for each particle type
                for i in range(n):
                    header = f.readline().split()
                    ctm.append(float(header[0]))
                    n_particles = int(header[2])
                    x = []
                    y = []
                    vx = []
                    vy = []
                    for j in range(n_particles):
                        line = f.readline().split()
                        x.append(float(line[0]))
                        y.append(float(line[1]))
                        vx.append(float(line[2]))
                        vy.append(float(line[3]))
                    plt.scatter(x, y, label="q/m="+header[0])
            plt.xlim(0, Lx)
            plt.ylim(0, Ly)
            plt.xticks(np.arange(0, Ly+dy, dy))
            plt.yticks(np.arange(0, Ly+dy, dy))
            plt.grid(True)
            plt.title(f"t={t}s")
            plt.legend()
            name = "output/"+sim+"/"+file.replace("txt","png")
            plt.savefig(name)
            frames.append(int(file.replace(".txt","")))
            #plt.show()
            plt.close(fig)
        frames.sort()
        with imageio.get_writer("output/"+sim+"/"+'sim.gif', mode='I', fps=10) as writer:
            for filename in frames:
                name = "output/"+sim+"/"+str(filename)+".png"
                print(name)
                image = imageio.imread(name)
                writer.append_data(image)