O plots.py agora também produz histogramas das velocidades (should be nifty).
Para facilitar a leitura é simpático pré-definir logo os limites e largura de bin (está no início do ficheiro)
Alterar para simulações diferentes

Também já corrigi a grelha para hopefully não ficarem 1000 números sobrepostos mas aparecer a grelha na mesma.

-----------------------------------------------------------
To do list:
	Código C++ Simulação:
		1. Interpolação-Density for particles on edge of grid
	Interface python:
		6. A lib continua a não compilar devidamente por vezes... Só fazendo rm lib/*
    Data analysis:
        7. Make a study of what units we're using, adjust length scales, particle densities and number of particles in each superparticle
        8. Do Fourier transform and find the langmuir dispersion relation
---------------------------------------------------------

pngcrush -ow -rem allb -reduce file.png
