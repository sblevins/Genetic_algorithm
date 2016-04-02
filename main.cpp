using namespace std;
#include <iostream>
#include <time.h>
#include "Simulation.h"



int main()
{
	
	Simulation sim;
	string file = "test.txt";
	int generations=20;
	double percentage=20;
	char crossover='k';
	char selection='t';
	int mutation1=10;
	int mutation2=1;
	cout << "~~~~~~~~~Genetic Algorithm~~~~~~~~~~\n";
	cout << "Input a file name: ";
	cin >> file;
	cout << "Input number of chromosomes: ";
	cin >> sim.populationSize;
	cout << "Input the number of generations: ";
	cin >> generations;
	cout << "Input 'e' for elitist selection or 't' for tournament selection: ";
	cin >> selection;
	cout << "Input the percentage of each preceding generation formed using selection (int): ";
	cin >> percentage;
	cout << "Input 'u' for uniform crossover or 'k' for kpoint crossover: ";
	cin >> crossover;
	cout << "Input the initial mutation rate: ";
	cin >> mutation1;
	cout << "Input the rate of change in mutation: ";
	cin >> mutation2;
	int numfit = (int)((double)sim.populationSize*percentage*.01);
	if (numfit % 2 == 1)
		numfit--;
	numfit = sim.populationSize - numfit;
	sim.read(file);
	sim.generatePopulation();//create the initial population
	sim.setFitness();//set the fitness of the original population

	cout << "computing...";
	//loop through generations
	for (int i = 0; i < generations; i++)
	{
		int mutation = mutation1 + (mutation2*i);
		if (selection == 'e')
			sim.eliteCull(numfit);
		else if (selection == 't')
		{
			sim.tournament(numfit);
		}
			

		if (crossover == 'u')
			sim.uniformCross(mutation);
		else if (crossover == 'k')
		{
			sim.kCross(mutation);
		}
	}
	sim.sort();
	system("cls");
		for (int i = 0; i < sim.populationSize; i++)
		{
			sim.getChromosome(i).print();
		} 
		system("pause");
}
