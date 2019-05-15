# nature-inspired
Basic nature-inspired algorithms developed to a master's class lesson

## Fitness Functions
Fitness functions used in the genetic algorithm are defined in **GeneticAlgorithm.cpp**. However the functions used in Hill Climbing and Simmulated Annealing are defined in **utilities.cpp**, as "rate". Two of them are math functions to be minimized or maximized. The last one is a Hamming Distance to calculate the difference between pixels of a image.

## Hill Climbing
The Hill Climbing algorithms just get as param the number of iterations.
There are three different implementations for this algorithm, as below:
- Hill Climbing
- Iterative Hill Climbing
- Stochastic Hill Climbing
Which can be used by typing:
```
HC(max_it)
IHC(max_it)
SHC(max_it)
```

## Simmulated Annealing
