#include "utilities.h"
#include <iostream>
#include <random>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
//CODIGO PARA INICIALIZAR A GERACAO DE NUMEROS RANDOMICOS
void initialize()
{
    srand(time(NULL));
}

//CODIGO PARA GERAR UM ALEATORIO ENTRE 0 E 1
float newRandom()
{
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

//FUNCAO DE AVALIACAO
float rate(float x)
{
    return pow(2,(-2*pow((x-0.1)/0.9,2)))*pow(sin(5*M_PI*x),6);
}

//CODIGO PARA APLICAR UM DISTURBIO EM X USANDO A DISTRIBUIÇAO NORMAL
float disturb(float x)
{
    float x_;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0,0.1);
    x_ = x+distribution(generator);
    return x_<0?0:x_>1?1:x_;
}

//CODIGO PARA DECREMENTAR A TEMPERATURA BASEADO EM B
float decrease(float T, float b)
{
    T = T*b;
}

//CODIGO PARA PEGAR A PARTE DO INDIVIDUO PERTENCENTE AO X E CONVERTER PARA DECIMAL (EX 3)
float getX(bool *individual, int size)
{
    float x;
    int i;
    int sizeTemp = size/2-1;
    bool *temp = new bool[sizeTemp];
    
    for(i = 0; i < sizeTemp; i++)
        temp[i] = individual[i+1];
    x =  ((float)binToDec(temp, sizeTemp)/100);
    
    if(x>5 && individual[0] == 1)
        x = -5;
    else if(x>5)
        x = 5;
    
    return x;
}

//CODIGO PARA PEGAR A PARTE DO INDIVIDUO PERTENCENTE AO Y E CONVERTER PARA DECIMAL (EX 3)
float getY(bool *individual, int size)
{
    float y;
    int i;
    int sizeTemp = size/2-1;
    bool *temp = new bool[sizeTemp];
    
    for(i = 0; i < sizeTemp; i++)
        temp[i] = individual[(i+size/2)+1];
    y = ((float)binToDec(temp, sizeTemp)/100);
    
    
    if(y>5 && individual[10] == 1)
        y = -5;
    else if(y>5)
        y = 5;
    
    return y;
}

//CODIGO PARA CONVERTER BINARIO PARA DECIMAL
int binToDec(bool *binary, int size)
{
    int x = 0, i;
    
    for(i = 0; i < size-1; i++)
        x+=binary[i]*pow(2, (size-i)-1);
    
    if(binary[i] == 1)
        x++;
    
    return x;
}