// Bunny breeder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bunny.h"
#include <random>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <thread>         // To use std::this_thread::sleep_for
#include <chrono>         // To use std::chrono::seconds  as parameter for  std::this_thread::sleep_for
 


using std::cin;
using std::cout;
using std::endl;

static std::random_device bunnySelector;	//Used to pick random bunny from list to get infected or get culled

int main()
{
	int turnNumber = 1;

	std::list<Bunny> bunnyList;

	cout << "Starter bunnies: " << endl;
	for (int i = 0; i < 5; i++)	//Making 5 random bunnies to start with
	{
		bunnyList.emplace_back();
	}
	
	
	while (Bunny::maleBunnies >= 1 || Bunny::femaleBunnies >= 1)	// Stuff that happen each turn as long as there is one bunny alive.
	{
		char input;
		cout << endl << "Enter 'y' to start the next turn or something else to stop breeding: ";
		cin >> input;
		if (input != 'y' && input != 'Y')
		{
			cin.clear();
			cin.ignore();
			break;
		}
		else
		{
			//Avoid the cin buffer becoming messed up or getting a double input
			cin.clear();
			cin.ignore();
		}
		

		cout << endl << "********************************  Turn " << turnNumber << "  *******************************" << endl;

		//ages all bunnies in the list by 1 year per turn and displays name and age
		for (Bunny & theBunny : bunnyList)	
		{
			theBunny.grow();
			cout << theBunny.getName() << " is now " << theBunny.getAge() << " years old." << endl;
		} 
		cout << endl;


		//Checks if any bunny is too old and kills them off
		for (auto iter = bunnyList.begin(); iter != bunnyList.end(); )		//incrementing happens in the body based on conditions
		{																	
			if (iter->isTooOld() )
			{
				auto tempIter = iter;		//increment iter before erasing element so as not to disrupt going through the list
				++iter;

				cout << tempIter->getName() << " died of old age." << endl;
				bunnyList.erase(tempIter);
			}
			else
			{
				++iter;	
			}
		}	
		cout << endl;


		// each rmv converts one regular bunny if available
		if (Bunny::rmvBunnies > 0)
		{
			int infected = 0;
			int numberToInfect = Bunny::rmvBunnies;

			for (auto iter = bunnyList.begin(); (infected < numberToInfect) && (iter != bunnyList.end()); ++iter)
			{
				if ( (iter->getRmv()) == true && (Bunny::rmvBunnies < (Bunny::maleBunnies + Bunny::femaleBunnies + Bunny::rmvBunnies)) )	// second condition to avoid infinite while loop when we have nothing left to infect
				{
					auto victim = iter;
					while ((victim->getRmv() == true) && victim != bunnyList.end())	// loop till we get a non-rmv bunny to infect
					{
						++victim;
					}

					iter->convert(*victim);
					cout << iter->getName() << " turned " << victim->getName() << " into a radioactive mutant vampire." << endl;

					++infected;
				}
			}

		}
		cout << endl;


		// Birth a new bunny for every female in the list
		if (Bunny::adultFemaleBunnies >= 1 && Bunny::adultMaleBunnies >= 1)		
		{
			for (auto theBunny = bunnyList.begin(), end = bunnyList.end(); theBunny != end; ++theBunny)
			{
				if ( theBunny->getSex() == "Female" && theBunny->getAge() >= 2 && theBunny->getRmv() == false && Bunny::adultMaleBunnies >= 1)
				{
					cout << theBunny->getName() << " gave birth to a bunny." << endl;
					theBunny->breed(bunnyList);
				}
			}
		}
		cout << endl;


		// Food shortage kills half the bunnies when they reach a population over 100
		if ((Bunny::maleBunnies + Bunny::femaleBunnies + Bunny::rmvBunnies) > 100)	
		{
			cout << "There are too many bunnies so half the bunnies will die of starvation: " << endl;

			int numberToCull = ( bunnyList.size() / 2 );

			for (int culled = 0; culled < numberToCull; ++culled)
			{
				std::uniform_int_distribution<int> bunnyCullDist(0, bunnyList.size()-1 );
				int listSpot = bunnyCullDist(bunnySelector);
				auto chosenBunny = next(bunnyList.begin(), listSpot);
				cout << chosenBunny->getName() << " has died of starvation." << endl;
				bunnyList.erase(chosenBunny);
			}

		}
		cout << endl;


		// while loop should fail and end once all bunnies are mutants
		if (Bunny::rmvBunnies == bunnyList.size())
		{
			cout << "All the bunnies are mutants now..." << endl;
		}

		++turnNumber;

		// The following line is for pausing each turn for 3 seconds if manual turn progression is commented out
		/*
		std::this_thread::sleep_for(std::chrono::seconds(3));	// Makes the current thread wait for 3 seconds before starting the next operation(next loop)
		*/

	}
	
	
	//Code for testing and debugging purposes
	/*
	for (Bunny & i : bunnyList)
	{
		i.displayInfo();
	}
	*/

	//cin.ignore();
	char pause;
	cout << endl << "Enter anything to exit" << endl;
	cin >> pause;

    return 0;
}

