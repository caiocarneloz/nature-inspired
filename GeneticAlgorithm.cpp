#include "GeneticAlgorithm.h"
#include "utilities.h"
#include <stdio.h>
#include <math.h>

//CODIGO PARA GERAR UMA POPULACAO ALEATORIA COM P INDIVIDUOS DE TAMANHO "SIZE"
bool **randomPopulation(int P, int size)
{
    bool **pop;
    int i, j;
    
    pop = new bool*[P];
    
    for(int i = 0; i < P; i++)
        pop[i] = new bool[size];
        
    for(i = 0; i < P; i++)
        for(j = 0; j < size; j++)
            pop[i][j] = (newRandom()<=0.5?0:1);
    
    return pop;
}

//CODIGO DA ROLETA PARA ESCOLHER OS INDIVIDUOS (ROLETA SIMPLES)
bool **roulette(bool **pop, int P, int size, float (fitnessFunc)(bool *individual, int s))
{
    int i, j, k;
    float fitnessSum = 0, drawn, sum;
    float *quota = new float[P];
    bool **temp = new bool*[P];
    
    for(int i = 0; i < P; i++)
        temp[i] = new bool[size];
    
    //SOMA A APTIDÃO DE TODOS INDIVÍDUOS
    for(i = 0; i < P; i++)
        fitnessSum+=fitnessFunc(pop[i], size);
    
    //DEFINE A COTA DE CADA INDIVÍDUO NA ROLETA
    for(i = 0; i < P; i++)
        quota[i] = (fitnessFunc(pop[i], size)*360)/fitnessSum;
    
    //SORTEIA O INDIVÍDUO
    for(i = 0; i < P; i++)
    {
        //SORTEIA UM NÚMERO DE 0 A 360
        drawn = 360*newRandom();
        
        for(j = 0, sum = 0; j < P; j++)
        {
            //VAI SOMANDO PARA ACHAR QUAL FATIA FOI SORTEADA
            sum += quota[j];
            if(drawn <= sum)
                break;
        }
        
        //erro de ponto flutuante;
        if(j > P-1)
            j = P-1;
        
        //SELECIONA O INDIVÍDUO PARA A POPULAÇÃO
        for(k = 0; k < size; k++)
            temp[i][k] = pop[j][k];
    }
        
    //RETORNA A NOVA POPULAÇÃO
    return temp;
}

//CODIGO PARA FAZER O CROSSOVER BASEADO NA TAXA CP
bool **crossover(bool **pop, int P, int size, float CP)
{
    int point, i, j;
    bool temp;
    
    for(i = 0; i < P; i+=2)
        //VERIFICA SE O CASAL IRÁ CRUZAR OU NÃO
        if(newRandom() <= CP)
        {
            //SORTEIA O PONTO DE CROSSOVER
            point = (((int)newRandom()*10)%7)+3;
            
            //GERA OS FILHOS
            for(j = 0; (j+point)<size; j++)
            {
                temp = pop[i][j+point];
                
                pop[i][j+point] = pop[i+1][j+point];
                
                pop[i+1][j+point] = temp;
            }                
        }
    
    return pop;
}

//CODIGO PARA FAZER A MUTACAO DA POPULACAO BASEADA NA TAXA MP
bool **mutation(bool **pop, int P, int size, float MP)
{
    int i,j;
    
    for(i = 0; i < P; i++)
        for(j = 0; j < size; j++)
            pop[i][j] = (newRandom()<=MP?!pop[i][j]:pop[i][j]);
    
    return pop;
}


//CODIGO PARA VISUALIZAR A POPULAÇAO ATUAL
void printPopulation(bool **pop, int P, int size, float (fitnessFunc)(bool *individual, int s))
{
    int i,j, k;
    float x, y;
    
    for(int i = 0; i < P; i++)
    {
        if(i>0)
            fprintf(stdout, "\n");
        
        for(int j = 0; j < size-1; j++)
            fprintf(stdout,"%d ",pop[i][j]);
        fprintf(stdout,"%d\t",pop[i][j]);
        
        fprintf(stdout,"%.2f",fitnessFunc(pop[i], size));
        
        
        //CODIGO PARA VISUALIZAR X DO EX2 EM DECIMAL 
        x =  ((float)binToDec(pop[i], size)/100);
        fprintf(stdout," %.2f",x);
        
        
        //CODIGO PARA VISUALIZAR X E Y DO EX3 EM DECIMAL 
        x = getX(pop[i], size);
        y = getY(pop[i], size);
        fprintf(stdout,"X = %.2f, Y = %.2f", x, y);
    }
    
    fprintf(stdout, "\n");
}

//CRITERIOS DE PARADA DE CADA EXERCICIO
bool stoppingCriteria1(bool **pop, int P, int size)
{
    int i;
    float fit;
    float sum = 0;
    float s = 13;
    
    for(i = 0; i<P;i++)
    {
        fit = fitnessFunc1(pop[i], size);
        if(fit < s)
            s = fit;
        
        sum += fit;
    }
    
    //fprintf(stdout, "%.2f\t%.2f\n",sum/P,s);
    
    for(i = 0; i<P;i++)
        if(fitnessFunc1(pop[i], size) == 12)
            return false;
    
    return true;
}

bool stoppingCriteria2(bool **pop, int P, int size)
{
    int i;
    float fit;
    float sum = 0;
    float s = 13;
    
    for(i = 0; i<P;i++)
    {
        fit = fitnessFunc2(pop[i], size);
        if(fit < s)
            s = fit;
        
        sum += fit;
    }
    
    //fprintf(stdout, "%.2f\t %.2f\n",sum/P,s);
    
    
    for(i = 0; i<P;i++)
        if(fitnessFunc2(pop[i], size) == 1)
            return false;
    
    
    return true;
}

bool stoppingCriteria3(bool **pop, int P, int size)
{
    int i;
    float sum = 0;
    float s = 0;
    float fit;
    
    
    for(i = 0; i<P;i++)
    {
        fit = fitnessFunc3(pop[i], size);
        if(fit > s)
            s = fit;
        
        sum += fit;
    }
    
    //fprintf(stdout, "%.2f\t%.2f\n",sum/P,s);
    
    for(i = 0; i<P;i++)
        if(fitnessFunc3(pop[i], size) == 0)
            return false;
    
    return true;
}

//ITERAÇAO DO ALGORITMO GENETICO, FUNCOES DE PARADA E APTIDAO MUDAM DE ACORDO COMO O "TYPE"
int GeneticAlgorithm(int P, int size, float CP, float MP, int type)
{
    bool **pop;
    int gen = 0;
    bool (*crit)(bool**,int,int);
    float (*func)(bool*,int);
    
    switch(type)
    {
        case 1:
            crit = &stoppingCriteria1;
            func = &fitnessFunc1;
            break;
        case 2:
            crit = &stoppingCriteria2;
            func = &fitnessFunc2;
            break;
        case 3:
            crit = &stoppingCriteria3;
            func = &fitnessFunc3;
            break;
    }
    
    //MANOBRA PARA DEIXAR A POPULAÇAO EM NUMERO PAR E FACILITAR AS OPERACOES
    if(P%2==1)
        P++;
    
    pop = randomPopulation(P, size);
    
    do
    { 
        gen++;
        pop = roulette(pop, P, size, func);
        pop = crossover(pop, P, size, CP);
        pop = mutation(pop, P, size, MP);
        //fprintf(stdout, "%d\t",gen);
    }
    while(crit(pop, P, size));
    
    //printPopulation(pop, P, size, func);
    
    return gen;
}

//FUNÇOES DE APTIDAO DE CADA EXERCICIO
float fitnessFunc1(bool *individual, int size)
{
    int i;
    float fit = 0;
    bool number[] = {1,1,1,1,0,1,1,0,1,1,1,1};
    
    for(int i = 0; i < size; i++)
        if(individual[i] == number[i])
            fit++;
    
    return fit;
}

float fitnessFunc2(bool *individual, int size)
{
    int i;
    float x=0;
    
    x =  ((float)binToDec(individual, size)/100);
    
    if(x>1)
        x = 1;
    
    return pow(2,(-2*pow((x-0.1)/0.9,2)))*pow(sin(5*M_PI*x),6);
}

float fitnessFunc3(bool *individual, int size)
{
    int i;
    float x, y;

    x = getX(individual, size);
    y = getY(individual, size);    
    
    return pow(1 - x, 2) + 100*pow((y-pow(x,2)),2);
}