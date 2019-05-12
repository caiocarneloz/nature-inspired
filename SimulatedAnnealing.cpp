#include "SimulatedAnnealing.h"
#include "utilities.h"
#include <math.h>

//SIMULATED ANNEALING
float SA(int T)
{
    float x, x_;
    
    x = newRandom();
    
    while(T > 1)
    {
        x_ = disturb(x);
        
        if(rate(x_) > rate(x))
            x = x_;
        else if(newRandom() < 1.0/(1 + exp((rate(x) - rate(x_))/T)))
            x = x_;
        
        T = decrease(T,0.1);
    }
    
    return x;
}