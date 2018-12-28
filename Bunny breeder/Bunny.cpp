#include "stdafx.h"
#include "Bunny.h"

std::vector<std::string> sexTypes{ "Male", "Female" };
std::vector<std::string> colorTypes{ "White", "Brown", "Black", "Spotted" };
std::vector<std::string> bunnyNames14{ "Thumper", "Oreo", "Bun", "Coco", "Cinnabun", "Snowball", "Daisy", "Buggs",
"Lilly", "Marshmellow", "Fluff", "Flour", "Jack", "Foofoo" };

static std::random_device namer;
std::uniform_int_distribution<int> namesDist(1, 14);	//used to pick name randomly

static std::random_device ranBunnyDev;
std::uniform_int_distribution<int> sexDist(1, 2);		//used to pick sex randomly
std::uniform_int_distribution<int> colorDist(1, 4);		//used to pick color randomly
std::uniform_int_distribution<int> rmvDist(1, 100);		// 2% chance for rmv bunny

//To get the total bunnies, add maleBunnies, femaleBunnies and rmvBunnies. Conversions increment rmv and reduce male/female
int Bunny::maleBunnies = 0;
int Bunny::femaleBunnies = 0;
int Bunny::rmvBunnies = 0;
int Bunny::adultMaleBunnies = 0;
int Bunny::adultFemaleBunnies = 0;

Bunny::Bunny()
{
	sex = sexTypes[ sexDist(ranBunnyDev) - 1 ];
	color = colorTypes[ colorDist(ranBunnyDev) - 1 ];
	age = 0;
	name = bunnyNames14[ namesDist(namer) - 1 ];

	int x = rmvDist(ranBunnyDev);
	if (x == 1 || x == 2)
	{
		rmv = true;
		name += "(rmv)";
		++rmvBunnies;
	}
	else
	{
		rmv = false;
	}

	if (sex == "Male"  && rmv == false)	//rmv bunnies don't breed so they wont count as adult bunnies
	{
		++maleBunnies;
	}
	if (sex == "Female"  && rmv == false)
	{
		++femaleBunnies;
	}

	std::cout << "A " << sex << " " << color << " bunny called " << name << " was born." << std::endl;
	if (rmv == true)
	{
		std::cout << "It is a radioactive mutant vampire bunny!" << std::endl;
	}
}

Bunny::Bunny(std::string theColor)
{
	sex = sexTypes[sexDist(ranBunnyDev) - 1];
	color = theColor;
	age = 0;
	name = bunnyNames14[namesDist(namer) - 1];

	int x = rmvDist(ranBunnyDev);
	if (x == 1 || x == 2)
	{
		rmv = true;
		name += "(rmv)";
		++rmvBunnies;
	}
	else
	{
		rmv = false;
	}

	if (sex == "Male" && rmv == false)
	{
		++maleBunnies;
	}
	if (sex == "Female" && rmv == false)
	{
		++femaleBunnies;
	}
	if (rmv == true)
	{
		++rmvBunnies;
	}

	std::cout << "A " << sex << " " << color << " bunny called " << name << " was born." << std::endl;
	if (rmv == true)
	{
		std::cout << "It is a radioactive mutant vampire bunny!" << std::endl;
	}
}

Bunny::~Bunny()
{
	//Death messages in main()

	if (sex == "Male" && rmv == false)
	{
		--maleBunnies;
		--adultMaleBunnies;
	}
	if (sex == "Female" && rmv == false)
	{
		--femaleBunnies;
		--adultFemaleBunnies;
	}
	if (rmv == true)
	{
		--rmvBunnies;
	}
}

std::string Bunny::getName()
{
	return name;
}

std::string Bunny::getSex()
{
	return sex;
}

std::string Bunny::getColor()
{
	return color;
}

int Bunny::getAge()
{
	return age;
}

bool Bunny::getRmv()
{
	return rmv;
}


void Bunny::displayInfo()
{
	std::cout << "Name: " << name << "\t\t Sex: " << sex << "\t Color: " << color << "\t Age: " << age << "\t RMV? : ";
	if (rmv)
	{
		std::cout << "Yes" << std::endl;
	}
	else
	{
		std::cout << "No" << std::endl;
	}
}

void Bunny::convert(Bunny & theBunny)
{
	theBunny.rmv = true;
	theBunny.name += "(rmv)";
	++rmvBunnies;

	if (theBunny.sex == "Male")
	{
		if (theBunny.getAge() >= 2)
		{
			--maleBunnies;
			--adultMaleBunnies;
		}
		else
		{
			--maleBunnies;
		}
	}

	if (theBunny.sex == "Female")
	{
		if (theBunny.getAge() >= 2)
		{
			--femaleBunnies;
			--adultFemaleBunnies;
		}
		else
		{
			--femaleBunnies;
		}
	}
}

void Bunny::breed(std::list<Bunny> & theList)
{
	theList.emplace_back(this->color);
}

void Bunny::grow()
{
	++this->age;

	if (this->age == 2 && this->sex == "Male")
	{
		++adultMaleBunnies;
	}
	if (this->age == 2 && this->sex == "Female")
	{
		++adultFemaleBunnies;
	}
}

bool Bunny::isTooOld()
{
	if (rmv == false)
	{
		if (age == 10)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (rmv == true)
	{
		if (age == 50)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}