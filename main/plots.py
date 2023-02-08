import os
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import numpy as np
import imageio as imageio
from matplotlib.ticker import (MultipleLocator)

minv = 5
binw = 0.1

if os.path.exists("output") and os.path.isdir("output"):
    sims = os.listdir("output")
    for sim in sims:
        if not os.path.isdir("output/"+sim):
            continue
        print("---- Simulation: ", sim, " ----")
        files = os.listdir("output/"+sim)
        files.sort()
        # frames for the gif
        frames = []
        PHI=[]
        timebase=[]
        xbase=[]
        ybase=[]
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
            phi_t=[]
            with open("output/"+sim+"/"+file) as f:
                # read time and number of particle types
                header = f.readline().split()
                t = float(header[0])
                n = int(header[2])
                timebase.append(t)
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
                    plt.scatter(x, y, label="q/m="+header[0],s=5)
                ############## Field ################
                header = f.readline().split()
                nx = int(header[5])
                ny = int(header[7])
                for i in range(nx):
                    line=f.readline().split()
                    phi_x=[]
                    for j in range(ny):
                        phi_y=line[j]
                        phi_x.append(float(phi_y))
                    phi_t.append(phi_x)
                PHI.append(phi_t)
                #######################################
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
            #axs[0].yaxis.set_major_locator(MultipleLocator(1))
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

        ################ FFT ##############
        print(PHI)
        for i in range(ny):
            wave=PHI[:][:][i]

            dt=timebase[1]-timebase[0]
            k_max = np.pi / dx
            omega_max = np.pi / dt

            sp = np.abs(np.fft.fft2(wave))**2
            sp = np.fft.fftshift(sp)
            plt.imshow( sp, origin = 'lower', norm=colors.LogNorm(vmin = 500.0),extent = ( -k_max, k_max, -omega_max, omega_max ),aspect = 'auto', cmap = 'gray')