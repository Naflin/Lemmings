// ******************************************************************
//
// LemmingCluster.h
// By: Nathan Blue
// Final Project
//  10/18/16
// Purpose: Interface for the LemmingCluster Class
// ******************************************************************
#ifndef LEMMING_CLUSTER_H_
#define LEMMING_CLUSTER_H_
#include <vector>
#include "Lemming.h"
using namespace std;

class LemmingCluster
{
	private:
		static int numOfClusters;
		int clusterID;
		int alive; 
		int dead; 
		int sick; 
		int males;
		int females;
		int maxSize;
		bool poisonous;
		
		vector<Lemming> lemmingCluster;
	public:
		LemmingCluster();
		
		int getClusterID();
		int getTotalLemmings();
		int getNumAlive();
		int getNumDead();
		int getNumSick();
		int getNumMales();
		int getNumFemales();
		int getMaxSize();
		int findMates();
		
		bool isCrowded();
		bool isPosionous();
		
		Lemming& getLemming(int);
		Lemming& getLemmingByID(int);
		void setMaxSize(int);
		
		void createLemming(int);
		void migrateLemming(Lemming);
		void deleteLemming(int, bool);
		
};

#endif
