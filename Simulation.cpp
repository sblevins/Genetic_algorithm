#include "Simulation.h"
#include <random>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

int compare(const void * a, const void * b)
{
	return (int)((*(Chromosome*)a - *(Chromosome*)b));
}

void Simulation::generatePopulation()
{
	default_random_engine generator;
	normal_distribution<double> distribution(0.0, 1.15);//normal distribution with mean 0 and SD 1.15
	for (int i = 0; i < populationSize; i++)
	{
		Chromosome child;
		child.ymin = distribution(generator);
		do {
			child.ymax = distribution(generator);
		} while (child.ymax < child.ymin);//re roll if max is lower than min
		child.tmin = distribution(generator);
		do {
			child.tmax = distribution(generator);
		} while (child.tmax < child.tmin);//re roll

		//assigning 0 or 1 to buy
		double iforgothowtodorandomlol;
		do {
			iforgothowtodorandomlol = distribution(generator);
		}while (iforgothowtodorandomlol == 0);
		if (iforgothowtodorandomlol > 0)
			child.buy = true;
		else
			child.buy = false;
		Population.push_back(child);
	}

}

void Simulation::setFitness()
{
	for (int i = 0; i < populationSize; i++)
	{
		Population[i].score = 0;
		bool foundmatch = false;//record if the chromosomes find at least 1 match
		for (unsigned int x = 0; x < change1.size(); x++)
		{
			if (Population[i].ymin < change1[x] &&//price ranges match and we are BUYing
				Population[i].ymax > change1[x] &&
				Population[i].tmin < change2[x] &&
				Population[i].tmax > change2[x] &&
				Population[i].buy == true)
			{
				foundmatch = true;
				Population[i].score += pchange[x];
			}
			else if (Population[i].ymin < change1[x] &&//price ranges match and we are SHORTing
				Population[i].ymax > change1[x] &&
				Population[i].tmin < change2[x] &&
				Population[i].tmax > change2[x] &&
				Population[i].buy == true)
			{
				foundmatch = true;
				Population[i].score -= pchange[x];
			}
			
		}
		if (!foundmatch)//set fitness score to -5000 if no matches are found
			Population[i].score = -5000;
	}
}

Chromosome Simulation::getChromosome(int x)
{
	return Population[x];
}

void Simulation::eliteCull(int n)
{
	setFitness();
	fittest.clear();
	sort();
	for (int i = 0; i < n; i++)
	{
		fittest.push_back(Population[populationSize - n + i]);
	}
}

void Simulation::sort()
{

	bool swap = true;
	while (swap)
	{
		swap = false;
		for (int i = 0; i < Population.size()-1; i++)
		{
			if (Population[i].score > Population[i + 1].score)
			{
				Chromosome temp = Population[i];
				Population[i] = Population[i + 1];
				Population[i + 1] = temp;
				swap = true;
			}
		}
	}
}

void Simulation::read(string x)
{
	
	ifstream file;
	file.open(x);
	if (!file.is_open()) {
		cout << "File could not be read";
		system("pause");
		exit(1);
	}
	else
	{
		double num = 0.0;

		// Parse file into three different vectors
		while (!file.eof())
		{
			file >> num;
			change1.push_back(num);
			file >> num;
			change2.push_back(num);
			file >> num;
			pchange.push_back(num);
		}
	}

	//Testing to see if it parsed correctly
	/*for (int i = 0; i < pchange.size(); i++)
		cout << pchange[i] << endl;
	*/
}

void Simulation::uniformCross(int m)
{
	srand(time(NULL));
	vector<Chromosome> descendants;
	for (int i = 0; i < populationSize - fittest.size(); i++)
	{
		Chromosome A = fittest[rand() % fittest.size()];
		Chromosome B = fittest[rand() % fittest.size()];
		Chromosome child;
		if (rand() % 2 == 0)
			child.tmin = A.tmin;
		else
			child.tmin = B.tmin;


		if (rand() % 2 == 0)
			child.tmax = A.tmax;
		else
			child.tmax = B.tmax;


		if (rand() % 2 == 0)
			child.ymin = A.ymin;
		else
			child.ymin = B.ymin;


		if (rand() % 2 == 0)
			child.ymax = A.ymax;
		else
			child.ymax = B.ymax;


		if (rand() % 2 == 0)
			child.buy = A.buy;
		else
			child.buy = B.buy;

		descendants.push_back(child);

	}
	for (int i = 0; i < descendants.size(); i++)
	{
		int r = rand() % 100;
		if (r <= m)//2%chance of mutation
			descendants[i].mutate();
		Population[i] = descendants[i];
	}
	for (int i = descendants.size(); i < Population.size(); i++)
	{
		Population[i] = fittest[i - descendants.size()];
	}
	setFitness();
}

void Simulation::kCross(int m)
{
	srand(time(NULL));
	vector<Chromosome> descendants;
	for (int i = 0; i < populationSize - fittest.size(); i++)
	{
		Chromosome A = fittest[rand() % fittest.size()];
		Chromosome B = fittest[rand() % fittest.size()];
		Chromosome child;
		child.ymin = A.ymin;
		child.ymax = A.ymax;
		child.tmin = B.tmin;
		child.tmax = B.tmax;
		child.buy = B.buy;
		descendants.push_back(child);
	}
	for (int i = 0; i < descendants.size(); i++)
	{
		int r = rand() % 100;
		if (r <= m)
			descendants[i].mutate();
		Population[i] = descendants[i];
	}
	for (int i = descendants.size(); i < Population.size(); i++)
	{
		Population[i] = fittest[i-descendants.size()];
	}
	setFitness();
}

void Simulation::tournament(int x)
{
	
	fittest.clear();
	srand(time(NULL));
	int rand1;
	int rand2;
	for (int i = 0; i < x; i++)
	{
		rand1 = rand() % populationSize;
		do
		{
			rand2 = rand() % populationSize;
		} while (rand1 == rand2);

		if (Population[rand1].score > Population[rand2].score)
		{
			fittest.push_back(Population[rand1]);
			
		}
		else
		{
			
			fittest.push_back(Population[rand2]);
		}
		
	}
}