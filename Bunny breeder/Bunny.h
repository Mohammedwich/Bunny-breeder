#pragma once
#include <string>
#include <random>
#include <iostream>
#include <vector>
#include <list>


class Bunny
{
public:
	
	static int maleBunnies;
	static int femaleBunnies;
	static int rmvBunnies;
	static int adultMaleBunnies;
	static int adultFemaleBunnies;

	Bunny();
	Bunny(std::string theColor);	// constructor to create bunnies that have same color as their mom
	~Bunny();

	std::string getName();
	std::string getSex();
	std::string getColor();
	int getAge();
	bool getRmv();

	void displayInfo();
	void convert(Bunny & theBunny);
	void breed(std::list<Bunny> & theList);
	void grow();
	bool isTooOld();

private:
	std::string name;
	std::string sex;
	std::string color;
	int age;
	bool rmv;	// rmv is  radioactive_mutant_vampire_bunny

	
};

