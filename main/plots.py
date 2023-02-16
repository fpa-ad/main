import os
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import numpy as np
import imageio as imageio
from matplotlib.ticker import (MultipleLocator)

minv = 5
binw = 0.05

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
                    #print(x)
                    #print(y)
                    plt.scatter(x, vx, label="q/m="+header[0],s=1)
            plt.xlim(0, Lx)
            plt.ylim(-10, 10)
            ax.xaxis.set_minor_locator(MultipleLocator(dx*10))
            ax.yaxis.set_minor_locator(MultipleLocator(dy*10))
            plt.grid(True, which='both')
            pe='pe'
            plt.title(f"$t={t}\omega_{{pe}}^{{-1}}$")
            plt.legend(loc='upper right')
            plt.xlabel("$x$ [$\lambda_{De}$]")
            plt.ylabel("$v_x$ [$\lambda_{De}\omega_{pe}$]")
            plt.savefig("output/"+sim+"/"+file.replace("txt","png"))
            #frames.append(int(file.replace(".txt","")))
            #plt.show()
            plt.close(fig)
            fig, axs = plt.subplots(1, 2, sharey=True, tight_layout=True, figsize=(8,4))
            axs[0].hist(vx, bins=np.arange(-minv, minv, binw))
            axs[0].set(title=f"$v_x$ for $t={t}\omega_{{pe}}^{{-1}}$")
            #axs[0].yaxis.set_major_locator(MultipleLocator(1))
            axs[1].hist(vy, bins=np.arange(-minv, minv, binw))
            axs[1].set(title=f"$v_y$ for $t={t}\omega_{{pe}}^{{-1}}$")
            plt.savefig("output/"+sim+"/"+file.replace(".txt","")+"_hist.png")
            #plt.show()
            plt.close(fig)

        for file in files:
            if not ".txt" in file:
                continue
            if (file == "README.txt"):
                continue
            frames.append(int(file.replace(".txt","")))

            

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

        """################ FFT ##############
        #print(PHI)
        print(PHI[1][1][0])
        nt=frames[-1]
        for i in range(ny):
            wave=np.zeros([nt,nx])
            for j in range(nt):
                waveaux=np.zeros(nx)
                for k in range(nx):
                    waveaux[k]=(PHI[j][k][i])
                wave[j,:]=waveaux[:]
            
            wind=np.hanning(nt)
            print(wave[1,1])
            for k in range(nx):
                wave[:,k]*=wind

            dt=timebase[1]-timebase[0]
            k_max = np.pi / dx
            omega_max = np.pi / dt

            sp = np.abs(np.fft.fft2(wave))**2
            sp = np.fft.fftshift(sp)
            print(wave[1,1])
            plt.imshow( sp, origin = 'lower', norm=colors.LogNorm(),extent = ( -k_max, k_max, -omega_max, omega_max ),aspect = 'auto', cmap = 'gray')

            plt.ylim(0,omega_max)
            plt.xlim(0,k_max)
            plt.xlabel("$k$ [$\omega_n/c$]")
            plt.ylabel("$\omega$ [$\omega_n$]")
            plt.title("Wave dispersion relation")

            plt.savefig("output/"+sim+"/fft_"+str(i)+".png")"""