// ******************************************************************
//
// Lemming.cpp
// By: Nathan Blue
// Final Project
//  10/18/16
//  Purpose: Implementation of the Lemming Class
// ******************************************************************

#include "Lemming.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int Lemming::totalLemmings = 0;

Lemming::Lemming()
{
	int num;
    /* generate secret number between 1 and 10: */
    num = rand() % 10 + 1;
    
    if(num % 2 == 0)
		gender = true;//set to female
	else
		gender = false;//set to male
	
	has_mate = false;
	can_mate = false;
	maturity = false;
	sick = false;
	dead = false;
	pregnant = false;
	birthDay = false;
	
	ID = totalLemmings++;
	mateID = -1;
	sicknessLevel = 0;
	startBreeding = 21;//At 21 days old, lemming can start breeding.
	endBreeding = 100; //At 100 days old, lemming cannot breed.
	age = 0;
	daysPregnant = 0;
	sicknessChance = 1;
}

Lemming::Lemming(bool b)
{
	gender = b;	
	has_mate = false;
	can_mate = false;
	maturity = false;
	sick = false;
	dead = false;
	pregnant = false;
	birthDay = false;
	
	ID = totalLemmings++;
	mateID = -1;
	sicknessLevel = 0;
	startBreeding = 21;//At 21 days old, lemming can start breeding.
	endBreeding = 100; //At 70 days old, lemming cannot breed.
	age = 0;
	daysPregnant = 0;
	sicknessChance = 1;
}


/************************************************
				incrementAge
				
purpose: increments the age by 1 and then
checks to see if the lemming is old enough
to start breeding
************************************************/

void Lemming::incrementAge()
{
	age++;
	if(age == startBreeding)
		can_mate = true;
}

/************************************************
				setDead
				
purpose: sets the lemming to dead and then
subtracks from the total lemmings			
************************************************/

void Lemming::setDead()
{
	dead = true;
	totalLemmings--;
}

/************************************************
				setSick
							
purpose: sets the lemming to sick
************************************************/

void Lemming::setSick()
{
	sick = true;
}


/************************************************
				incrementSicknessLevel
				
purpose: increments the sickness level by 1				
************************************************/

void Lemming::incrementSicknessLevel()
{
	sicknessLevel++;
}

/************************************************
				setSicknessLevel
				
data in: the level of sickness to be set to the
lemming.
************************************************/

void Lemming::setSicknessLevel(int level)
{
	sicknessLevel = level;
}

/************************************************
				setSicknessChance
				
data in: the chance the lemming will get sick				
************************************************/

void Lemming::setSicknessChance(int chance)
{
	if(chance < 1)
		chance = 1;
	sicknessChance = chance;
}


/************************************************
				increaseSicknessChance
				
data in: multiplies the sickness chance by the
input amount;
************************************************/

void Lemming::increaseSicknessChance(int chance)
{
	if(chance < 1)
		chance = 1;
	sicknessChance *= chance;
}

/************************************************
				setPregnent
				
data in: a boolean that will change whether
the lemming is pregnent or not
************************************************/

void Lemming::setPregnant(bool b)
{
	if(b)
	{
		daysPregnant = 2;
		pregnant = b;
		birthDay = false;
	}
	else
	{
		daysPregnant = 0;
		pregnant = b;
		birthDay = false;
	}
}

/************************************************
				decrementDaysPregnant
				
purpose: decreases the number of days that
the lemming is pregnant.  Once the day reaches 0,
the lemming will then be set to give birth.
************************************************/

void Lemming::decrementDaysPregnant()
{
	daysPregnant--;
	if(daysPregnant == 0)
	{
		pregnant = false;
		birthDay = true;
	}
}

/************************************************
				setMateID
				
data in: the id of the lemming's mate
************************************************/

void Lemming::setMateID(int id)
{
	mateID = id;
	has_mate = true;
}

/************************************************
				setMateStutus
				
data in: sets whether the lemming has a mate
or not.
************************************************/

void Lemming::setMateStatus(bool status)
{
	has_mate = status;
}

/************************************************
				hasMate
				
data out: returns a bool of the current mate
status
************************************************/

bool Lemming::hasMate()
{
	return has_mate;
}

/************************************************
				isMature
				
data out: returns true if the lemming is mature	
and vice versa			
************************************************/

bool Lemming::isMature()
{
	if(age > startBreeding && age < endBreeding)
		return true;
	
	return false;
}

/************************************************
				isDead
				
data out: return true if the lemming has either
reached being too old, having a high sickness
level, or was already set to dead
************************************************/

bool Lemming::isDead()
{
	if(age >= 125 || sicknessLevel >= 3 || dead == true)
	{
		has_mate = false;
		can_mate = false;
		maturity = false;
		sick = false;
		pregnant = false;
		birthDay = false;
		dead = true;
		totalLemmings--;
		return true;
	}
	
	return false;
}

/************************************************
				isSick
				
data out: returns a bool of its sick status	
************************************************/

bool Lemming::isSick()
{
	return sick;
}

/************************************************
				gotSick
				
data out: will return a bool based on the chance
that it gets sick.	
************************************************/

bool Lemming::gotSick()
{
	int num = rand() * 100 + 1;
	
	if(num <= sicknessChance)
	{
		sick = true;
		return true;	
	}
	return false;
}

/************************************************
				getGender
				
data out: returns the lemmings gender
************************************************/

bool Lemming::getGender()
{
	return gender;
}

/************************************************
				isPregnant
				
data out: returns the state of pregnancy
************************************************/

bool Lemming::isPregnant()
{
	return pregnant;
}

/************************************************
				isFemale
				
data out: returns true if female and false
if male.	
************************************************/

bool Lemming::isFemale()
{
	if(gender == true)
		return true;
	return false;
}

/************************************************
				isMale
				
data out: returns true if male and false
if female.
************************************************/

bool Lemming::isMale()
{
	if(gender == false)
		return true;
	return false;
}

/************************************************
				isBirthDay
				
data out: returns true if the lemming is
going to give birth and fasle if not
************************************************/

bool Lemming::isBirthDay()
{
	return birthDay;
}

/************************************************
				getAge
				
data out: returns the age of the lemming
************************************************/

int Lemming::getAge()
{
	return age;
}

/************************************************
				getSicknessLevel
				
data out: returns the level of sickness of the
lemming
************************************************/

int Lemming::getSicknessLevel()
{
	return sicknessLevel;
}

/************************************************
				getSicknessChance
				
data out: returns the sickness chance of the
lemming
************************************************/

int Lemming::getSicknessChance()
{
	return sicknessChance;
}

/************************************************
				getMateID
				
data out: returns the ID of the lemmings mate
************************************************/

int Lemming::getMateID()
{
	return mateID;
}

/************************************************
				getID
				
data out: retunrs the lemmigns ID
************************************************/

int Lemming::getID()
{
	return ID;
}

/************************************************
				getTotalLemmings
				
data out: returns the total amount of lemmings
from all lemming classes		
************************************************/

int Lemming::getTotalLemmings()
{
	return totalLemmings;
}

/************************************************
				getDaysPregnant
				
data out: returns the days pregnant of the lemming
************************************************/

int Lemming::getDaysPregnant()
{
	return daysPregnant;
}






