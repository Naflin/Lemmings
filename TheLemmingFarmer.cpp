// ******************************************************************
//
// TheLemmingFarmer.cpp
// By: Nathan Blue
// Final Project
//  10/18/16
// Purpose: The lemming Farmer Game.
//  	    Collect as many lemmings as you can
//			before they all die
// ******************************************************************

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LemmingGame.h"
using namespace std;

//Prototypes
void chooseNest(LemmingGame &);
void chooseInfo(LemmingGame &);
void chooseHelp(LemmingGame &);

int main()
{
	srand(time(0));
	LemmingGame game;
	int sicknessL1 = 0;
	int sicknessL2 = 0;
	int sicknessL3 = 0;
	int died = 0;
	int migrations = 0;
	int choice = 0;
	int matesFound = 0;
	int mostLemmings = 0;
	
	
	cout << "=============== Welcome to the Lemming Farmer! =====================\n"
		 << "You are in charge of a lemming farm.\n"
		 << "Your goal is to keep alive as many lemmings as you can.\n"
		 << "If your lemmings have mates, they will produce offspring every 7 days.\n"
		 << "If the nests get too crowded the lemmings will migrate to other nests.\n"
		 << "However, if they can't migrate, they will start to get sick and die.\n"
		 << "\n\n";
		 
	cout << "All you can do is dig nests.\nThere are several different size nests.\n"
		 << "Pick your nests wisely and keep the lemmings alive.\nIf you have any"
		 << "questions, choose the help option."
		 << "\n\n";
		 
	cout << "Press enter to begin...\n\n\n\n\n";
	
	cin.get();
	
	while(game.nests.getTotalLemmings() != 0)
	{		
		cout << "\n==-==-==-==-==-==-==-== Lemming Farmer ==-==-==-==-==-==-==-==\n";
		cout << "Days: " << game.days.getDays() << endl;
		cout << "Total Lemmings: " << game.nests.getTotalLemmings() << endl;
		cout << "Total Nests: " << game.nests.getNumNests() << endl;
		cout << "Dig Days Left: " << game.nests.getDigDays() << endl;
		cout << "==============================================================\n\n";
		
		while(choice != 1)
		{	
			cout << "\nMenu (Enter a number): \n"
				 << ((game.nests.isDigging()) ? 
				 ("1. Continue digging\n") : ("1. Dig a nest\n"))
				 << "2. Info for nests and lemmings\n"
				 << "3. Help\n"
				 << "choice: ";
			cin >> choice;
			cout << "\n\n";
			
			
			switch(choice)
			{
				case 1 : 
				{
					if(!game.nests.isDigging())
						chooseNest(game);
					cout << endl;
					break;
				}
				case 2 : chooseInfo(game);
						 cout << endl;
						 break;
				case 3 : chooseHelp(game);
						 cout << endl;
						 break;
				default: cout << endl;
						 break;
			}
		}
		
		//End day calculations and events
		
		if(game.nests.isDigging())
		{
			game.nests.setDigDays(game.nests.getDigDays() - 1);
			
			//Creates a nest based on the size of the nest dug
			if(game.nests.getDigDays() == 0)
				game.nests.createNest(game.nests.getSizeOfNest());
		}
		
		//All the checks for each lemming in each cluster
		for(int x = 0; x < game.nests.getNumNests(); x++)
		{				 
			for(int y = 0; y < game.nests.getCluster(x).getTotalLemmings(); y++)
			{
				//Each lemming becomes 1 day older
				game.nests.getCluster(x).getLemming(y).incrementAge();
				
				//All mature female lemmings who have mates can now create offspring 
				if(game.nests.getCluster(x).getLemming(y).isMature() && 
					game.nests.getCluster(x).getLemming(y).hasMate() &&
					game.nests.getCluster(x).getLemming(y).isFemale() &&
					!game.nests.getCluster(x).getLemming(y).isPregnant())
				{
					game.nests.getCluster(x).getLemming(y).setPregnant(true);
				}
				
				//If a lemming is pregnant, then decrease the days that she is pregnant
				if(game.nests.getCluster(x).getLemming(y).isPregnant())
				{
					game.nests.getCluster(x).getLemming(y).decrementDaysPregnant();
				}
				
				//If a lemming gave birth, create 1 lemmings;
				if(game.nests.getCluster(x).getLemming(y).isBirthDay())
				{
					game.nests.getCluster(x).createLemming(1);
					
					//if the lemming doesn't have a partner, 
					//then prevent it from getting pregnant
					if(game.nests.getCluster(x).getLemming(y).getDaysPregnant() == 0 &&
						!game.nests.getCluster(x).getLemming(y).hasMate())
					{
						game.nests.getCluster(x).getLemming(y).setPregnant(false);
					}
				}
				
				//If the nest is crowded, then the chances 
				//of the lemming getting sick increases
				if(game.nests.getCluster(x).isCrowded() ||
					game.nests.getCluster(x).isPosionous())
				{
					game.nests.getCluster(x).getLemming(y).increaseSicknessChance(3);
				}
					
				//If the number of sick lemmings in a cluster
				//is greater than 40%, then get more lemmings sick
				if((static_cast<double>(game.nests.getCluster(x).getNumSick()) / 
					game.nests.getCluster(x).getTotalLemmings()) > 0.4)
				{
					game.nests.getCluster(x).getLemming(y).increaseSicknessChance(2);
				}	
				
				
				if(game.nests.getCluster(x).getLemming(y).gotSick())
				{
					game.nests.getCluster(x).getLemming(y).incrementSicknessLevel();
					switch(game.nests.getCluster(x).getLemming(y).getSicknessLevel())
					{
						case 1 : sicknessL1++;
							     break;
						case 2 : sicknessL2++;
								 break;
						case 3 : sicknessL3++;
								 break;
						default : cout << "[WARNING] Lemming: " 
							     << game.nests.getCluster(x).getLemming(y).getID()
							     << " has reached an INSANE level of sickness.\n";
							     break;
					}
				}
				
				//If lemming dies, remove it from the vector array
				if(game.nests.getCluster(x).getLemming(y).isDead())
				{
					game.nests.getCluster(x).deleteLemming(y, true);
					died++;
				}
			}
			
			matesFound += game.nests.getCluster(x).findMates();
			
			//If the total amount of lemmings is greator than 
			//the available space, then move some of the
			//lemmings to other nests
			if(game.nests.getCluster(x).getTotalLemmings() >= 
				game.nests.getCluster(x).getMaxSize())
			{
				game.nests.migrate(x);
				migrations++;
			}
		}
		
		if(mostLemmings < game.nests.getTotalLemmings())
			mostLemmings = game.nests.getTotalLemmings();
		
		cout << "\n========== Lemming News =============\n"
			 << "Lemmings that just died: " << died << endl
			 << "Lemmings that just reached sickness level 1: " << sicknessL1 << endl
			 << "Lemmings that just reached sickness level 2: " << sicknessL2 << endl
			 << "Lemmings that just reached sickness level 3: " << sicknessL3 << endl
			 << "The number of migrations: " << migrations << endl
			 << "Number of mates that have been found: " << matesFound << endl << endl;
		
		if(died > 500)
			cout << "[DEATH] DIG NESTS FASTER!!! WHAT ARE YOU DOING!?!\n";
		else if(died > 100)
			cout << "[DANGER] We're losing lots of lemmings. Dig!'\n";
		else if(died > 20)
			cout << "[Warning] Things are looking to good. Keep digging!\n";
		else if(died > 0)
			cout << "[Update] Lemmings are starting to die.  Just keep digging.\n";
		else
			cout << "[Update] The Lemmings seem to be fine.\n";
		
		died = 0;
		sicknessL1 = 0;
		sicknessL2 = 0;
		sicknessL3 = 0;
		migrations = 0;
		matesFound = 0;
		
		cout << endl << endl;
		game.days.incrementDay();
		choice = -1;//Set to -1 so that the user can pick a new action next loop
	}
	
	cout << "Congratulations! You made it " << game.days.getDays()
		 << " days before losing all "
		 << mostLemmings << " of your lemmings!\n Better luck next time.\n\n";
		 
	cout << "Press enter to continue...\n";
	cin.get();
	cin.get();
	
	
	return 0;
}

void chooseNest(LemmingGame& game)
{
	int choice;
	
	while(choice < 1 || choice > 5)
	{
		cout << "Choose what size nest to dig (Enter a number):\n";
		cout << "#. Nest size (Dig time | Capacity)\n";
		cout << "==========================================================\n";
		cout << "1. Tiny nest (1-3 days | 2-6 lemmings)\n";
		cout << "2. Small nest (4-14 days | 10-150 lemmings)\n";
		cout << "3. Medium nest (14-34 days | 100-600 lemmings)\n";
		cout << "4. Big nest (29-59 days | 250-1750 lemmings)\n";
		cout << "5. Random (34-94 days | 1 - 10000 lemmings)\n";
		cin >> choice;
		
		switch(choice)
		{
			case 1 : game.nests.digTinyNest();
					 break;
			case 2 : game.nests.digSmallNest();
					 break;
			case 3 : game.nests.digMediumNest();
					 break;
			case 4 : game.nests.digLargeNest();
					 break;
			case 5 : game.nests.digRandomNest();
					 break;
			default: cout << "Please choose a number between 1 and 4\n";
		}
	}
}

void chooseInfo(LemmingGame& game)
{
	int choice;
	cout << "========= This is info! Cool! ============\n";
	cout << "1. Show lemming cluster info" << endl;
	cout << "2. Show lemming info" << endl;
	cout << "Choice: ";
	cin >> choice;
	cout << "\n\n";
	
	switch(choice)
	{
		case 1 : {			
			cout << "\n========== Lemming Clusters ===========\n";
			
			for(int x = 0; x < game.nests.getNumNests(); x++)
			{
				cout << "Cluster ID: " 
					 << game.nests.getCluster(x).getClusterID()
					 << ", Number of Lemmings: " 
					 << game.nests.getCluster(x).getTotalLemmings()
					 << ", Max number of lemmings: " 
					 << game.nests.getCluster(x).getMaxSize() << endl;
			}
			break;
		}
		case 2 : {
			
			do{
				cout << "Which cluster would you like to analyze? Choose between 1 and " 
				 << game.nests.getNumNests() << ": ";
				cin >> choice;
				choice -= 1;
			} while(choice < 0 || choice > (game.nests.getNumNests() - 1) );
			
			cout << "\n\n";
			
			for(int y = 0; y < game.nests.getCluster(choice).getTotalLemmings(); y++)
			{
				cout << " LemmingID: "
					 << game.nests.getCluster(choice).getLemming(y).getID()
					 << "\tMate ID: " 
					 << game.nests.getCluster(choice).getLemming(y).getMateID()
				 	 << "\tAge: " 
					 << game.nests.getCluster(choice).getLemming(y).getAge()
				 	 << "\tGender: " 
					 << ((game.nests.getCluster(choice).getLemming(y).getGender()) ?
					    ("Female") : ("Male"))
					 << "\tAlive: "
					 << ((game.nests.getCluster(choice).getLemming(y).isDead()) ? 
					    ("No") : ("Yes")) << endl
					 << " Sickness Level: " 
					 << game.nests.getCluster(choice).getLemming(y).getSicknessLevel()
					 << "\tSicknass chance: "
					 <<  game.nests.getCluster(choice).getLemming(y).getSicknessChance()
					 << "\tDays pregnant: " 
					 << game.nests.getCluster(choice).getLemming(y).getDaysPregnant() 
					 << "\n==================================="
					 << "===========================================\n";
			}
			
			break;
		}
	}
	
}

void chooseHelp(LemmingGame& game)
{
	cout << "=========== Help ============\n";
	cout << "At the menu, choosing 1 will allow you to dig more nests\n"
		 << "for your lemmings.  After they are dug, the lemmings\n"
		 << "will later migrate over to them. \n";
		 
	cout << "When you choose 1 to dig, you get to choose from 5\n"
		 << "different types of nests. Each type of nest has a\n"
		 << "capacity range and takes several days to dig.\n"
		 << "This can be seen on the menu.\n\n";
		 
	cout << "Choosing 2 will bring you to the submenu that allows\n"
		 << "you to view the data about the nests and lemmings.\n"
		 << "You should frequently use this feature to keep\n"
		 << "up with your lemmings.";
}










