#ifndef SPREADER_H
#define SPREADER_H

#include "spreaderRunner.h"
#include "BinaryHeap.h"

class Person2
{
public:
  int ID, peopleMet, time;
  bool visited, unvisited;
  Visitor *visitors;
  bool operator < (Person2 p) const; 
  

};

class Spreader
{
  int days, population;
  Person2* p2;
public:
  Spreader(const Person *people, int population);
  int simulate(int starterIDs[], int starterCount, int commandLineOption);

};


#endif /* SPREADER_H */

