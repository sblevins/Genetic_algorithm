#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <string>
#include <vector>
#include "Chromosome.h"

using namespace std;

class Simulation
{
private:
	int length = 0;//the length of the text files read in
	vector<Chromosome> Population;//all of the chromosomes in the population
	vector<Chromosome> fittest;//individuals  selected to reproduce
	vector<double> change1;//the previous days price change
	vector<double> change2;//todays price change
	vector<double> pchange;//tomorrows price change
	
public:
	int populationSize = 100;//the number of chromosomes
	void eliteCull(int x);//elitist selection
	void tournament(int x);//tournament selection
	void setFitness();//fitness test
	void generatePopulation();//generates the initial population
	Chromosome getChromosome(int);//returns a chromosome in the population array by number
	void sort();//super amazing sorting algorithm
	void read(string);//file read in
	void uniformCross(int m);//uniform crossover
	void kCross(int m);//kpoint crossover
};
 





#endif
