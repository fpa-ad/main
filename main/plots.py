import os
import matplotlib.pyplot as plt
import numpy as np
import imageio as imageio
from matplotlib.ticker import (MultipleLocator, AutoMinorLocator)

minv = 60
binw = 1

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
            fig, ax = plt.subplots()
            with open("output/"+sim+"/"+file) as f:
                # read time and number of particle types
                header = f.readline().split()
                t = float(header[0])
                n = int(header[2])
                ctm = []
                # for each particle type
                for i in range(1):
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
                    plt.scatter(x, y, label="q/m="+header[0],s=5)
            plt.xlim(0, Lx)
            plt.ylim(0, Ly)
            ax.xaxis.set_minor_locator(MultipleLocator(dx))
            ax.yaxis.set_minor_locator(MultipleLocator(dy))
            plt.grid(True, which='both')
            plt.title(f"t={t}s")
            plt.legend()
            plt.savefig("output/"+sim+"/"+file.replace("txt","png"))
            frames.append(int(file.replace(".txt","")))
            #plt.show()
            plt.close(fig)
            fig, axs = plt.subplots(1, 2, sharey=True, tight_layout=True, figsize=(8,4))
            axs[0].hist(vx, bins=np.arange(-minv, minv, binw))
            axs[0].set(title=f"$v_x$ for t={t}s")
            axs[0].yaxis.set_major_locator(MultipleLocator(1))
            axs[1].hist(vy, bins=np.arange(-minv, minv, binw))
            axs[1].set(title=f"$v_y$ for t={t}s")
            plt.savefig("output/"+sim+"/"+file.replace(".txt","")+"_hist.png")
            #plt.show()
            plt.close(fig)
        frames.sort()
        with imageio.get_writer("output/"+sim+"/"+'sim.gif', mode='I', fps=10) as writer:
            for filename in frames:
                name = "output/"+sim+"/"+str(filename)+".png"
                print(name)
                image = imageio.imread(name)
                writer.append_data(image)
        with imageio.get_writer("output/"+sim+"/"+'sim_hist.gif', mode='I', fps=10) as writer:
            for filename in frames:
                name = "output/"+sim+"/"+str(filename)+"_hist.png"
                print(name)
                image = imageio.imread(name)
                writer.append_data(image)