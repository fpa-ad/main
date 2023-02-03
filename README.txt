Alterações:
//typedef double (*funcdouble)(double); // type for conciseness
typedef std::function<double(double)> funcdouble;
-> acho que não tem impacto e assim posso usar lambdas para definir as distribuições no problem

Já dá para correr a simulação a partir do Python!
-> make test 

Furthermore, estou confused com a situação da temperatura e da maxwelliana. Só sabemos q/m e seria necessário m, how?
Meti uma maxwelliana que não depende realmente da temperatura só para testar.
As of now, só implementei mesmo a uniforme para as posições e a pseudo-fake-maxwelliana para as velocidades, o resto will follow.

----

To do list:

1. As partículas ainda não avançam em y
2. Fazer o cálculo da densidade sem ele morrer
3. Simular a equação de Poisson para o campo elétrico
4. O campo magnético ainda não está nas contas para avançar posições e velocidades
5. Corrigir a pseudo-maxwelliana e implementar o resto
6. A lib continua a não compilar devidamente por vezes... Só fazendo rm lib/*
7. A Ana continua a usar mallocs e news sem qualquer shred of self-respect (deve rever a situação no interface.C asap)
8. Será necessária a massa para além do ctm?

J A N E L A S:
- Para cada tipo de partícula:
    Distribuições nas posições:
    - random
    - step (sobe) -> controlar posição de subida
    - plateau (sobe e desce) -> controlar ambas as posições

    Distribuições nas velocidades:
    - maxwellian -> controlar temperatura e v_0
    - bump-on-tail -> controlar separação e um dos coefs