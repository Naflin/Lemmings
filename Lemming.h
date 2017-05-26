// ******************************************************************
//
// Lemming.h
// By: Nathan Blue
// Final Project
//  10/18/16
// Purpose: Interface for the Lemming Class
// ******************************************************************
#ifndef LEMMING_H_
#define LEMMING_H_

class Lemming
{
	private:
		static int totalLemmings;
		
		bool has_mate;
		bool can_mate;
		bool gender;  //true = female, false = male
		bool maturity;
		bool sick;
		bool dead;
		bool pregnant;
		bool birthDay;
		
		int ID;
		int mateID;
		int sicknessLevel;
		int startBreeding;
		int endBreeding;
		int age;
		int daysPregnant;
		int sicknessChance;
	public:
		Lemming();
		Lemming(bool);
		
		void incrementAge();		
		void setDead();
		void setSick();
		void setSicknessLevel(int);
		void setSicknessChance(int);
		void increaseSicknessChance(int);
		void incrementSicknessLevel();
		void setPregnant(bool);
		void decrementDaysPregnant();
		void setMateID(int);
		void setMateStatus(bool);
		
		bool hasMate();
		bool isMature();
		bool isDead();
		bool isSick();
		bool gotSick();
		bool getGender();
		bool isPregnant();
		bool isFemale();
		bool isMale();
		bool isBirthDay();
		
		
		int getAge();
		int getSicknessLevel();
		int getSicknessChance();
		int getMateID();
		int getID();
		int getTotalLemmings();
		int getDaysPregnant();
};

#endif
