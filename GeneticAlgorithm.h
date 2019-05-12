#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

int GeneticAlgorithm(int P, int size, float CP, float MP, int type);
float fitnessFunc1(bool *individual, int size);
float fitnessFunc2(bool *individual, int size);
float fitnessFunc3(bool *individual, int size);

#endif