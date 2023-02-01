As it stands, parece estar tudo funcional: com um campo externo positivo, os eletrões vão embora para a esquerda e os positrões para a direita.
Looks good, output looks good.
"make clean" agora limpa a pasta output também.
Meti no gitignore para ele não commitar mais o conteúdo do bin, sounds like a recipe for disaster.
Por vezes é necessário apagar a lib para ele a refazer devidamente. Isto é chato. "make lib -B" força, mas é chato.

1. Situação nos campos:

double Field::get_X(double x, double y){
    /*int auxX = (int)(x/hx);
    int auxY = (int)(y/hy);
    return Fx[auxX][auxY]+ext_x;*/
    return ext_x;
}

double Field::get_Y(double x, double y){
    /*int auxX = (int)(x/hx);
    int auxY = (int)(y/hy);
    return Fy[auxX][auxY]+ext_y;*/
    return ext_y;
}

O código comentado causa Segmentation Violation. Não logo, mas à segunda iteração.

2. O campo magnético ainda não está nas contas para avançar posições e velocidades

3. Funções de distribuição (estão completamente em falta, está tudo a zeros e com nullptrs)