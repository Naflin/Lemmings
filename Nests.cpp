// ******************************************************************
//
// Nests.cpp
// By: Nathan Blue
// Final Project
//  10/18/16
//  Purpose: Implementation of the Nests Class
// ******************************************************************
#include "Nests.h"
#include <iostream>
#include <cstdlib>

Nests::Nests()
{
	LemmingCluster lemmingCluster;
	nests.push_back(lemmingCluster);
	
	digging = false;
	digDays = 0;
	numNests = 1;
	sizeOfNest = 0;
}

/************************************************
*												*
*					Accessors					*
*												*
************************************************/


/************************************************
				 isDigging

data out: A boolean telling if the player
is currently digging a nest
************************************************/

bool Nests::isDigging()
{
	return digging;
}

/************************************************
				 getDigDays

data out: The number of days it takes to
dig a nest.
************************************************/

int Nests::getDigDays()
{
	return digDays;
}

/************************************************
				 getSizeOfNest 

data out: The number of nests in the game
************************************************/

int Nests::getNumNests()
{
	return nests.size();
}

/************************************************
				 getSizeOfNest 
				 
data out: The size of the nest set by
		  the nest being dug.
************************************************/

int Nests::getSizeOfNest()
{
	return sizeOfNest;
}


/************************************************
				 getTotalLemmings
				 
purpose: To get the total lemmings fromm all
of the clusters

data out: the total number of lemmings
************************************************/
int Nests::getTotalLemmings()
{
	int totalLemmings = 0;
	for(int x = 0; x < nests.size(); x++)
		totalLemmings += nests.at(x).getTotalLemmings();
	
	return totalLemmings;
}

/************************************************
				 getCluster
				 
purpose: To get a specific Lemming Cluster from
the vector array.				 
				 
data in: The index of the array.

data out: The chosen Lemming Cluster
************************************************/
LemmingCluster& Nests::getCluster(int index)
{
	return nests.at(index);
}

/************************************************
*												*
*					Modifiers					*
*												*
************************************************/

/************************************************
				 setDigDays
				 
data in: Number of days it takes to dig the nest

If the days equal 0, then the digging stops.
************************************************/

void Nests::setDigDays(int days)
{
	digDays = days;
	if(digDays == 0)
		digging = false;
}

/************************************************
				 Nest Digging Outline
				 
digDays : Generates and sets the number of days 
it takes to dig this particular nest.

digging : Sets the player to digging mode.

sizeOfNest ; Generates and sets the number
lemmings that this nest can hold
************************************************/

void Nests::digTinyNest()
{
	digDays = rand() % 3 + 2;
	digging = true;
	sizeOfNest = rand() % 4 + 2;
}

void Nests::digSmallNest()
{
	digDays = rand() % 10 + 5;
	digging = true;
	sizeOfNest = rand() % 140 + 10;
}

void Nests::digMediumNest()
{
	digDays = rand() % 20 + 15;
	digging = true;
	sizeOfNest = rand() % 500 + 100;
}

void Nests::digLargeNest()
{
	digDays = rand() % 30 + 30;
	digging = true;
	sizeOfNest = rand() % 1500 + 250;
}

void Nests::digRandomNest()
{
	digDays = rand() % 60 + 35;
	digging = true;
	sizeOfNest = rand() % 10000 + 1;
}


/************************************************
				 createNest
				 
data in: The size of the nest that is going
to be created.

Creates a nest and loads it into 
the array.
  
************************************************/

void Nests::createNest(int nestSize)
{
	LemmingCluster lemmingCluster;
	lemmingCluster.setMaxSize(nestSize);	
	nests.push_back(lemmingCluster);
	numNests++;
}


/************************************************
				 migrate
				 
data in: The current cluster with lemmings that 
want to migrate.

purpose: To free up space in other nests by
moving lemmings into a different nest with
more space available.
************************************************/
void Nests::migrate(int index)
{
	int highest = 0; //Most amount of available space
	int pos = 0; //position of the nests
	int freeSpace = 0; //Free space for extra lemmings
	
	//loop through each lemming
	for(int l = 0; l < nests.at(index).getTotalLemmings(); l++)
	{
		//loop through the nests
		for(int n = 0; n < nests.size(); n++)
		{
			//Find the nest with the most space
			freeSpace = nests.at(n).getMaxSize() - nests.at(n).getTotalLemmings();
			
			if(freeSpace > highest)
			{
				highest = freeSpace;
				pos = n;
			}
		}
		
		//If any nest was found, copy the lemming and then delete him.
		if(highest != 0)
		{
			nests.at(pos).migrateLemming(nests.at(index).getLemming(l));
			nests.at(index).deleteLemming(l, false);
		}
		
		highest = 0;//Reset for the next lemming
	}
}


