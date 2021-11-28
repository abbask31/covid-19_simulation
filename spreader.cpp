#include <iostream>  // for debugging
#include <cstring>
#include "BinaryHeap.h"
#include "spreader.h"
using namespace std;


Spreader::Spreader(const Person *people, int population) : population(population), p2(new Person2[population]) 
{
  // Students write this. 
  // Note that people will be deleted before simulate() is called.
  
  for (int i = 0; i < population; i++){

    memcpy(&p2[i],&people[i],sizeof(people[i]));
    p2[i].time = 100000;
    p2[i].visited = false;
    p2[i].unvisited = false;
    p2[i].visitors = new Visitor[p2[i].peopleMet];
    for (int j = 0; j < p2[i].peopleMet; j++)
      memcpy(&p2[i].visitors[j],&people[i].visitors[j],sizeof(people[i].visitors[j]));

  }
} // Spreader()

bool Person2::operator<(Person2 p)const{
  return (time < p.time);
}


// garbge clean up // 

Spreader::Spreader(const Person *people, int population) : population(population), p2(new Person2[population])
{
  // Students write this. 

  for (int i = 0; i < population; i++){
    memcpy(&p2[i],&people[i],sizeof(people[i]));
    p2[i].time = 100000;
    p2[i].visited = false;
    p2[i].unvisited = false;
    p2[i].visitors = new Visitor[p2[i].peopleMet];
    for (int j = 0; j < p2[i].peopleMet; j++)
        memcpy(&p2[i].visitors[j],&people[i].visitors[j],sizeof(people[i].visitors[j]));
  }

} // Spreader()
int Spreader::simulate(int starterIDs[], int starterCount, int commandLineOption)
{
  // commandLineOption may be used to signal the program to do whatever the students
  // want, or nothing at all.
  BinaryHeap<Person2> heap(population / 4); // empty less heap at one time
  Person2 person;
  Visitor v;
  days = 0;
  
  
  for (int i = 0; i < starterCount; i++){
    p2[starterIDs[i]].time = 0;
    heap.insert(p2[starterIDs[i]]);
  }
  
  for (;heap.isEmpty() == false;){
    heap.deleteMin(person); // always delete lowest false value in heap //

    for (int i = 0; i < person.peopleMet; i++){
      v = person.visitors[i];

      if (p2[v.ID].visited == false){
           int tmpDays = (person.time + v.period) - (person.time % v.period);
        for(;tmpDays - person.time < INCUBATION_TIME;) // another period added since it was less than 3 days
          tmpDays += v.period;

        if(tmpDays < p2[v.ID].time) {
          p2[v.ID].time = tmpDays;
          if(tmpDays > days)
            days = tmpDays;
          }
        if(p2[v.ID].unvisited == false) {
          heap.insert(p2[v.ID]);
          p2[v.ID].unvisited = true;
        }
      }
    }
    
    person.visited = true;
  }
  // Students write this.  Returns days until of last person catches the virus
  return days; // to avoid warnings for now.
}

