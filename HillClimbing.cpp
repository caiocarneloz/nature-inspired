#include "HillClimbing.h"
#include "utilities.h"
#include <math.h>
#define T 0.001

//HILL CLIMBING ESTOCASTICO
float SHC(int max_it)
{
    float x, x_;
    int t;
    
    t = 1;
    x = newRandom();
    
    while(t < max_it)
    {
        x_ = disturb(x);
        if(newRandom() < 1.0/(1 + exp((rate(x) - rate(x_))/T)))
            x = x_;
        
        t++;
    }
    
    return x;
}

//HILL CLIMBING ITERATIVO (O NUMERO MAXIMO DE ITERACOES E IGUAL AO NUMERO DE VEZES QUE SERA EXECUTADO)
float IHC(int n_start)
{
    float best, x;
    int t, max_it = n_start;
    
    t = 1;
    best = newRandom();
    
    while(t < n_start)
    {
        x = HC(max_it);
        
        if(rate(x) > rate(best))
            best = x;
        
        t++;        
    }
    
    return best;
}

//HILL CLIMBING COMUM
float HC(int max_it)
{
    float x, x_;
    int t;
    
    
    t = 1;
    x = newRandom();
    
    while(t < max_it)
    {
        x_ = disturb(x);
        
        if(rate(x_) > rate(x))
            x = x_;
        
        t++;
    }
    
    return x;
}

