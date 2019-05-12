#ifndef UTILITIES_H
#define UTILITIES_H

void initialize();
float newRandom();
float rate(float x);
float disturb(float x);
float decrease(float T, float b);
int binToDec(bool *binary, int size);
float getX(bool *individual, int size);
float getY(bool *individual, int size);

#endif

