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
                    for j in range(n_particles):
                        line = f.readline().split()
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

        ################ FFT ##############
        #print(PHI)
        print(PHI[1][1][0])
        nt=len(timebase)
        for i in range(ny):
            wave=np.zeros([int(nt),nx])
            """for j in range(nt):
                waveaux=np.zeros(nx)
                for k in range(nx):
                    waveaux[k]=(PHI[j][k][i])
                wave[j,:]=waveaux[:]"""

            for j in range(nt):
                waveaux=np.zeros(nx)
                for k in range(nx):
                    waveaux[k]=(PHI[j][k][i])
                if(1):
                    wave[int(j),:]=waveaux[:]
            
            wind=np.hanning(int(nt))
            #print(wave[1,1])
            for k in range(nx):
                wave[:,k]*=wind

            print(dx)
            #wave=np.transpose(wave)
            """for k in range(1,nx-1):
                wave[:,k]=(wave[:,k+1]-wave[:,k-1])
            wave[:,0]=(wave[:,1]-wave[:,nx-1])
            wave[:,nx-1]=(wave[:,0]-wave[:,nx-2])"""

            dt=timebase[5]-timebase[4]
            k_max = np.pi / dx
            omega_max = np.pi / (dt)

            sp = np.abs(np.fft.fft2(wave))**2
            sp = np.fft.fftshift(sp)
            #print(wave[1,1])
            plt.imshow( sp, origin = 'lower', norm=colors.LogNorm(vmin=5000),extent = ( -k_max, k_max, -omega_max, omega_max ),aspect = 'auto', cmap = 'gray')

            k = np.linspace(-k_max, k_max, num = 512)
            w=np.sqrt(1)+3/2*(1**2)*(k)**2
            plt.plot( k, w, label = "Electron Plasma Wave", color = 'r',ls = '-.' )

            plt.ylim(0,10)
            plt.xlim(0,5)
            plt.xlabel("$k$ [$\omega_n/c$]")
            plt.ylabel("$\omega$ [$\omega_n$]")
            plt.title("Wave dispersion relation")

            plt.savefig("output/"+sim+"/fft_"+str(i)+".png")