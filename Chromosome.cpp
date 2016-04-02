#include "Chromosome.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

Chromosome::Chromosome(double a, double b, double c, double d, bool e) 
{
	ymin = a;
	ymax = b;
	tmin = c;
	tmax = d;
	buy = e;
	score = 0;
}

Chromosome::Chromosome()
{
	ymin = 0;
	ymax = 0;
	tmin = 0;
	tmax = 0;
	buy = 0;
	score = 0;
}

void Chromosome::print()
{
	cout << ymin << "  " << ymax << "  " << tmin << "  " << tmax << "  " << buy << "  " << score << "\n";
}

void Chromosome::mutate()
{
	srand(time(NULL));
	int x = rand() % 5;
	default_random_engine generator;
	normal_distribution<double> distribution(0.0, 1.15);//normal distribution with mean 0 and SD 1.15
	
	if (x == 0)
	{
		do {
			ymin = distribution(generator);
		} while (ymin > ymax);
		
	}
	if (x == 1)
	{
		do {
			ymax = distribution(generator);
		} while (ymin > ymax);

	}
	if (x == 2)
	{
		do {
			tmin = distribution(generator);
		} while (tmin > tmax);

	}
	if (x == 3)
	{
		do {
			tmax = distribution(generator);
		} while (tmin > tmax);

	}
	if (x == 4)
	{
		if (buy)
			buy = false;
		else
			buy = true;
	}
		


}