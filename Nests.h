// ******************************************************************
//
// Nests.h
// By: Nathan Blue
// Final Project
//  10/18/16
// Purpose: Interface for the Nests Class
// ******************************************************************
#ifndef NESTS_H_
#define NESTS_H_
#include <vector>
#include "LemmingCluster.h"
using namespace std;

class Nests
{
	private:		
		bool digging;
		int digDays;
		int numNests;
		int sizeOfNest;
		
		vector<LemmingCluster> nests;
	public:
		Nests();
		
		bool isDigging();
		int getDigDays();
		int getNumNests();
		int getSizeOfNest();
		int getTotalLemmings();
		
		void createNest(int);
		void setDigDays(int);
		void digTinyNest();
		void digSmallNest();
		void digMediumNest();
		void digLargeNest();
		void digRandomNest();
		
		LemmingCluster& getCluster(int);
		void migrate(int);
				
};

#endif
