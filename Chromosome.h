#ifndef CHROMOSOME_H
#define CHROMOSOME_H

class Chromosome
{
public:
	Chromosome();
	Chromosome(double, double, double, double, bool);
	double ymin;//minimum change for yesterday
	double tmin;//minimum change today
	double ymax;//maximum change yesterday
	double tmax;//maximum change today
	bool buy;//1 = buy/0 = short
	double score;//the chromosomes fittness score
	void print();//prints chromosome info to screen
	void mutate();//mutates the chromosome
	double operator - (Chromosome b)
	{
		return score - b.score;
	}

};




#endif