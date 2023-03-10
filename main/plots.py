import os
import matplotlib.pyplot as plt
import imageio as imageio
#from matplotlib.ticker import (MultipleLocator)
import matplotlib

matplotlib.use("Agg")

binn = 100
binr = 5

if os.path.exists("output") and os.path.isdir("output"):
    sims = os.listdir("output")
    for sim in sims[1:]:
        if not os.path.isdir("output/"+sim):
            continue
        print("---- Simulation: ", sim, " ----")
        files = os.listdir("output/"+sim)
        files.sort()
        # frames for the gif
        frames = []
        n = 0
        with open("output/"+sim+"/README.txt") as f:
            header = f.readline().split()
            Lx = float(header[1])
            Ly = float(header[3])
            dx = float(header[5])
            dy = float(header[7])
            n = int(f.readline().split()[0])
        fig, ax = plt.subplots()
        plt.xlim(0, Lx)
        plt.ylim(-10, 10)
        #ax.xaxis.set_minor_locator(MultipleLocator(dx))
        plt.xlabel("$x\;[\lambda_{De}]$")
        plt.ylabel("$v_x\;[\lambda_{De} \omega_{pe}]$")
        plt.grid(True, which='both')
        points = None
        fig2, axs2 = plt.subplots(1, 2, sharey=True, tight_layout=True, figsize=(8,4))
        hist1 = None
        hist2 = None
        axs2[0].set_xlabel("$v_x\;[\lambda_{De} \omega_{pe}]$")
        axs2[1].set_xlabel("$v_y\;[\lambda_{De} \omega_{pe}]$")
        axs2[0].set_ylabel("Count")
        axs2[1].set_ylabel("Count")
        c = matplotlib.cm.tab10
        for file in files:
            if not ".txt" in file:
                continue
            if (file == "README.txt"):
                continue
            print(file)
            with open("output/"+sim+"/"+file) as f:
                # clear the plots
                if points != None:
                    for p in points:
                        p.remove()
                points = []
                if hist1 != None:
                    for bar in hist1:
                        for b in bar:
                            b.remove()
                hist1 = []
                if hist2 != None:
                    for bar in hist2:
                        for b in bar:
                            b.remove()
                hist2 = []
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
                    plt.figure(1)
                    points.append(plt.scatter(x, vx, label="q/m="+header[0], s=2, color=c(i)))
                    plt.figure(2)
                    counts, bins, bars1 = axs2[0].hist(vx, bins = binn, range = (-binr, binr), label="q/m="+header[0], alpha=0.5, color=c(i))
                    hist1.append(bars1)
                    counts, bins, bars2 = axs2[1].hist(vy, bins = binn, range = (-binr, binr), label="q/m="+header[0], alpha=0.5, color=c(i))
                    hist2.append(bars2)
            plt.figure(1)
            plt.legend()
            plt.title(f"$t={t}"+"\;\omega_{pe}^{-1}$")
            plt.savefig("output/"+sim+"/"+file.replace("txt","png"))
            frames.append(int(file.replace(".txt","")))
            plt.figure(2)
            axs2[0].set(title=f"$v_x$ for $t={t}"+"\;\omega_{pe}^{-1}$")
            plt.legend()
            axs2[1].set(title=f"$v_y$ for $t={t}s"+"\;\omega_{pe}^{-1}$")
            plt.legend()
            plt.savefig("output/"+sim+"/"+file.replace(".txt","")+"_hist.png")
            
        frames.sort()
        with imageio.get_writer("output/"+sim+"/"+'sim.gif', mode='I', fps=10) as writer:
            for filename in frames:
                name = "output/"+sim+"/"+str(filename).zfill(4)+".png"
                print(name)
                image = imageio.imread(name)
                writer.append_data(image)
        with imageio.get_writer("output/"+sim+"/"+'sim_hist.gif', mode='I', fps=10) as writer:
            for filename in frames:
                name = "output/"+sim+"/"+str(filename).zfill(4)+"_hist.png"
                print(name)
                image = imageio.imread(name)
                writer.append_data(image)