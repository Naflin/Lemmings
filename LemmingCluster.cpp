// ******************************************************************
//
// LemmingCluster.cpp
// By: Nathan Blue
// Final Project
//  10/18/16
// Purpose: Implementation of the LemmingCluster Class
// ******************************************************************
#include "LemmingCluster.h"
#include <iostream>
using namespace std;

int LemmingCluster::numOfClusters = 1;

LemmingCluster::LemmingCluster()
{
	//If this is the first cluster of lemmings
	//Then create the first pair of lemmings to start off the game
	if(numOfClusters == 1)
	{
		Lemming lemming1(true);//Create female lemming
		lemmingCluster.push_back(lemming1);
		females++;
		
		Lemming lemming2(false);//Create male lemming
		lemmingCluster.push_back(lemming2);
		males++;
	}
	
	clusterID = numOfClusters++;
	alive = 0;
	dead = 0;
	sick = 0;
	males = 0;
	females = 0;
	maxSize = 10;
	poisonous = false;
	
}

/************************************************
				getClusterID

data out: get the ID of the cluster
************************************************/

int LemmingCluster::getClusterID()
{
	return clusterID;
}

/************************************************
				getTotalLemmings

data out: get the total lemmings in the cluster
************************************************/

int LemmingCluster::getTotalLemmings()
{
	return lemmingCluster.size();
}

/************************************************
				getNumAlive

data out: the number of alive lemmings in the cluster
************************************************/

int LemmingCluster::getNumAlive()
{
	return alive;
}

/************************************************
				getNumDead

data out: the number of dead lemmigns in the cluster
************************************************/

int LemmingCluster::getNumDead()
{
	return dead;
}

/************************************************
				getNumSick

data out: the number of sick lemmings in the cluster
************************************************/

int LemmingCluster::getNumSick()
{
	sick -= sick / 3;//Even though some lemmings have died, the effects of the sickness linger
	for(int x = 0; x < lemmingCluster.size(); x++)
		if(lemmingCluster.at(x).isSick())
			sick++;
	return sick;
}

/************************************************
				getNumMales

data out: the number of male lemmigns in the cluster
************************************************/

int LemmingCluster::getNumMales()
{
	return males;
}

/************************************************
				getNumFemales

data out: the number of females lemmigns in the cluster
************************************************/

int LemmingCluster::getNumFemales()
{
	return females;
}

/************************************************
				getMaxSize

data out: the maximum number of lemmings
the cluster can hold before the lemmings
get sick.
************************************************/

int LemmingCluster::getMaxSize()
{
	return maxSize;
}

/************************************************
				findMates

data out: the number of mates found

fpos = first position
spos = second position

Start at the beggining of the array and check 
if the first lemming has a match already.
If it does, move on to the next lemming.
Once you find a lemming that does not have a match, 
check the following lemmings to see if they have a match.  
If the second positioned lemming does not have a
match, then match them up and start the loop over 
to make sure they all have matches.

************************************************/


int LemmingCluster::findMates()
{
	bool gender;//temporary gender checker
	int temp = 0;
	int matesFound = 0;
	
	//first lemming
	for(int fpos = 0; fpos < lemmingCluster.size(); fpos++)
	{
		gender = lemmingCluster.at(fpos).getGender();
		
		//If the first lemming can mate, then find another lemming that can
		if(!lemmingCluster.at(fpos).hasMate() && 
			lemmingCluster.at(fpos).isMature())
		{
			for(int spos = fpos + 1; spos < lemmingCluster.size(); spos++)
			{
				if(!lemmingCluster.at(spos).hasMate() && 
					lemmingCluster.at(spos).getGender() != gender && 
					lemmingCluster.at(spos).isMature())
				{
					temp = lemmingCluster.at(spos).getID();
					lemmingCluster.at(fpos).setMateID(temp);
					lemmingCluster.at(fpos).setMateStatus(true);
					
					temp = lemmingCluster.at(fpos).getID();
					lemmingCluster.at(spos).setMateID(temp);
					lemmingCluster.at(spos).setMateStatus(true);
					
					matesFound++;
				}
			}
		}
	}
	
	return matesFound;
}

/************************************************
				isCrowded

data out: A bool based on whether the number
of lemmings is greater than the space available
************************************************/

bool LemmingCluster::isCrowded()
{
	if(lemmingCluster.size() > maxSize)
		return true;
	return false;
}

/************************************************
				isPoisonous

data out: A boolean based on whether the amount
of lemmings that died in this cluster is
greator than half the maximum space available
************************************************/

bool LemmingCluster::isPosionous()
{
	if((maxSize / 2) <= dead)
		return true;
	return false;
}

/************************************************
				getLemming

data in: the index of the lemming in the cluster

data out: the lemming from the specific index
in the cluster
************************************************/

Lemming& LemmingCluster::getLemming(int index)
{
	return lemmingCluster.at(index);
}

/************************************************
				getLemmingByID

data in: the id of a specific lemming

data out: the lemming with that id
************************************************/

Lemming& LemmingCluster::getLemmingByID(int id)
{
	for(int x = 0; x < lemmingCluster.size(); x++)
	{
		if(lemmingCluster.at(x).getID() == id)
			return lemmingCluster.at(x);
	}
}

/************************************************
				setMaxSize

data in: the maximum size of the cluster
************************************************/

void LemmingCluster::setMaxSize(int n)
{
	maxSize = n;
}


/************************************************
				createLemming

data in: the number of lemmings to be created
************************************************/

void LemmingCluster::createLemming(int num)
{
	for(int x = 0; x < num; x++)
	{
		Lemming lem;
		lemmingCluster.push_back(lem);
		if(lem.getGender())
			females++;
		else
			males++;
	}
}

/************************************************
				migrateLemming

data in: accept a lemming at place it in the
array of this cluster

************************************************/

void LemmingCluster::migrateLemming(Lemming lem)
{
	lem.setMateID(-1);
	lem.setMateStatus(false);
	lemmingCluster.push_back(lem);
}

/************************************************
				deleteLemming

data in 1: the index of the specific lemming that
should be deleted

data in 2; set to false if you don't want to 
add this lemming to the death count. set to true 
if you do.

************************************************/

void LemmingCluster::deleteLemming(int index, bool deadLemming = false)
{
	int id = lemmingCluster.at(index).getMateID();
	
	for(int x = 0; x < lemmingCluster.size(); x++)
	{
		if(lemmingCluster.at(x).getID() == id)
		{
			lemmingCluster.at(x).setMateID(-1);
			lemmingCluster.at(x).setMateStatus(false);
		}
			
	}
	
	if(deadLemming)
		dead++;
	
	lemmingCluster.erase(lemmingCluster.begin() + index);
														  
}







