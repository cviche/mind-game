#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class Player
{
    public:
        int dollars; //This is the amount of dollars a person starts out in the game
        int points; //This is the amount of points the player receives when they win the round.
        int maxBetLimit; //This will be twenty
        int currentBetAmount; //How much the player is betting in this turn
        string playerName;
        bool inGame;
    
        Player()
        {
            this->dollars = 100;
            this->points = 0;
            this->maxBetLimit = 2;
            this->playerName = "";
        }
    
        Player(int dollars, string name)
        {
            this->dollars = dollars;
            this->points = 0;
            this->maxBetLimit = 2;
            playerName = name;
            inGame = true;
            
        }
	
	void setDollars(int dollars)
	{
		this->dollars = dollars;
	}
	
	int getDollars()
	{
		return this->dollars;
	}
	
	void setPoints(int dollars)
	{
		
	}
	
	int getPoints()
	{
		return this->points;
	}
	
	string getName()
	{
		return this->playerName;
	}
    
    private:
    
};

int checkWinnerAndUpdate(vector<Player*> players);
void properInput(vector<Player*> players, int i);
bool isGameOver(vector<Player*> players);
void printState(vector<Player*> players);

int main()
{
	string p1;
	string p2;
	string p3;
	bool gameEnd = false;
    vector<Player*> players;     
    
	cout << "Enter Player 1's Name: \n";
	cin >> p1;
    players.push_back(new Player(30, p1)); // Player 1
    std::this_thread::sleep_for (std::chrono::seconds(1));
	
	cout << "Enter Player 2's Name: \n";
	cin >> p2;
    players.push_back(new Player(30, p2)); //Player 2;
    std::this_thread::sleep_for (std::chrono::seconds(1));
	
	cout << "Enter Player 3's Name: \n";
	cin >> p3;
    players.push_back(new Player(30, p3)); //Player 3
    std::this_thread::sleep_for (std::chrono::seconds(1));

    cout << "We are now starting the game. Get ready to bet!\n";
    //std::this_thread::sleep_for (std::chrono::seconds(1));
	while(!gameEnd)
	{
        int currWinner = 0;
        for(int i = 0; i < players.size(); i++)
        {
            if(players[i]->dollars > 0)
            {
              std::this_thread::sleep_for (std::chrono::seconds(1));
              cout << players[i]->playerName +", place the amount of dollars you would like to bet this round\n";
              cin >> players[i]->currentBetAmount; 
              properInput(players, i);
              std::this_thread::sleep_for (std::chrono::seconds(1));
            }
            else
            {
                players[i]->inGame = false;
                players[i]->currentBetAmount = 0;
            }
        }    
        
        int roundWinner = checkWinnerAndUpdate(players);
        std::this_thread::sleep_for (std::chrono::seconds(1));
        cout << "The winner of this round is: " +players[roundWinner]->playerName + "\n";
        std::this_thread::sleep_for (std::chrono::seconds(1));
        
        printState(players);
        gameEnd = isGameOver(players); 
        if(gameEnd == true)
        {
            int finalWinner = 0;
            for(int i = 0; i < players.size(); i++)
            {
                players[i]->points += players[i]->dollars;
                players[i]->dollars -= players[i]->dollars;
                if(players[finalWinner]->points < players[i]->points) finalWinner = i;
            }
            cout <<"The winner of this whole game is " + players[finalWinner]->playerName + "\n";
            break;
        }
	}
}

//This function checks if the game is over
//So, if all players except one has 0 dollars, then we have a winner.
bool isGameOver(vector<Player*> players)
  {
      int noDollars = 0;
    
      for(int i = 0; i < players.size(); i++)
      {
          if(players[i]->dollars == 0) noDollars++;    
      }
        
      if(noDollars == players.size() - 1 || noDollars == players.size()) return true;
        
      return false;
}

//This prints the state of the game
void printState(vector<Player*> players)
{
    for(int i = 0; i < players.size(); i++)
      {
          cout << players[i]->playerName + " has: \n";
          cout <<"Dollars: " + to_string(players[i]->dollars) + "\n";
          cout <<"Points: " + to_string(players[i]->points) + "\n";
          cout <<"Max Bets " + to_string(players[i]->maxBetLimit) + "\n\n";
      }
}

int checkWinnerAndUpdate(vector<Player*> players)
{
   int currWinner = 0;
      while(players[currWinner]->inGame == false)
      {
         currWinner++;
      }
        
      for(int i = currWinner + 1; i < players.size(); i++)
      {
         if(players[currWinner]->currentBetAmount < players[i]->currentBetAmount)
         {
            currWinner = i;
         }                
      }
    
      for(int i = 0; i < players.size(); i++)
      {
         players[currWinner]->points += players[i]->currentBetAmount;
      }
    
   return currWinner;
}

void properInput(vector<Player*> players, int i)
{
   int below0 = players[i]->dollars - players[i]->currentBetAmount;
                
   while((players[i]->currentBetAmount > 20 || players[i]->currentBetAmount < 0) || below0 < 0)
   {
       cout << "You cannot bet more than 20 dollars or less than 0 in a bet\n";
       cout << "OR, you do not have enough to bet\n";
       cout << "OR, you don't have anymore max bets left";
       cout << "Please put a new bet: \n";
       cin >> players[i]->currentBetAmount;
       while(players[i]->currentBetAmount == 20 && players[i]->maxBetLimit == 0)
       {
           cout << "You cannot make a max bet anymore. Please choose another bet.\n";
           cin >> players[i]->currentBetAmount;
       }
      
      below0 = players[i]->dollars - players[i]->currentBetAmount;       
   }
      if(players[i]->currentBetAmount == 20 && players[i]->maxBetLimit > 0)
      {
          players[i]->maxBetLimit--;
          players[i]->dollars -= players[i]->currentBetAmount;
          cout <<"You bet 20 dollars. Careful, you only have " + to_string(players[i]->maxBetLimit) + " max bet left\n"; 
      }
      else
      {         
          players[i]->dollars -= players[i]->currentBetAmount;     
          cout <<"You bet " + to_string(players[i]->currentBetAmount) + " dollars\n";
      }      
}




