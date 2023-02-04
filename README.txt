-----------------------------------------------------------
To do list:
	Código C++ Simulação:
		1. As partículas ainda não avançam em y
		3. Simular a equação de Poisson para o campo elétrico
		4. O campo magnético ainda não está nas contas para avançar posições e velocidades
	Interface python:
		5. Corrigir a pseudo-maxwelliana e implementar o resto
		6. A lib continua a não compilar devidamente por vezes... Só fazendo rm lib/*

---------------------------------------------------------

J A N E L A S:
- Para cada tipo de partícula:
    Distribuições nas posições:
    - random
    - step (sobe) -> controlar posição de subida
    - plateau (sobe e desce) -> controlar ambas as posições

    Distribuições nas velocidades:
    - maxwellian -> controlar temperatura e v_0
    - bump-on-tail -> controlar separação e um dos coefs
