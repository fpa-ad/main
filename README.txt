As it stands, parece estar tudo funcional: com um campo externo positivo, os eletrões vão embora para a esquerda e os positrões para a direita.
Looks good, output looks good.
"make clean" agora limpa a pasta output também.
Meti no gitignore para ele não commitar mais o conteúdo do bin, sounds like a recipe for disaster.
Por vezes é necessário apagar a lib para ele a refazer devidamente. Isto é chato. "make lib -B" força, mas é chato.

Já dá para ver coisas!!!
Se executares o test.exe, ele deve criar uma pasta output com uma pasta lá dentro correspondente a essa simulação.
É mega básica, tem só 10 eletrões e 10 positrões, velocidades iniciais nulas e posições randoms.
Anywho, de seguida corres o plots.py, ele faz a sua magia et voila: surge uma cambada de imagens, correspondentes às snapshots e um gif!
Já meti os limites a serem Lx e Ly, a grelha que aparece deve ser a mesma grelha que nós usamos internamente, ele lê do README da simulação.

Havendo mais do que uma simulação no output, ele vai processá-las todas pasta a pasta, portanto tem cuidado



2. O campo magnético ainda não está nas contas para avançar posições e velocidades

3. Funções de distribuição (estão completamente em falta, está tudo a zeros e com nullptrs)
