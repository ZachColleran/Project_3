#include "functions.cpp"
#include <iostream>
using namespace std;


int main()
{
    // create first BestBuy and Player
    BestBuy BestBuy1;
    Player Player1;

    Player1.setFrustration(90);

    cout << "Welcome to Where in the Code is Carmen Sandiego!" << endl; // game starts
    Player1.setStartName();
    BestBuy1.startBestBuy(); 

    // create array and fill it with player inventory quantities
    int inventory[Player1.getSize()];
    Player1.findInventoryStats(inventory);
    int coins_left;
    // input player coin amount, return new coin amount, change player coin amount
    coins_left = (BestBuy1.buy(Player1.getMoney(), inventory));
    Player1.setMoney(coins_left);

    // Stock player inventory based on item bought
    Player1.updateInventoryStats(inventory);

    // Create Map
    Map Map1;
    Map1.spawnBestBuy(0, 0);
    Map1.spawnHacker(2,1);
    Map1.spawnNPC(1,2);

    // Create Game Stats
    int serverRoomLevel = 1;
    int computerMaintenanceLevel = 100;
    int computerDamage = 0;
    int computerViruses = 0;
    int carmensProgress = 0;
    int hackersDefeated = 0;
    int loseStatus;

    // START GAME
    bool gameStatus = true;

    do
    {
        // Ask user what they wish to do
        int option;
        cout << "1. Repair Computer" << endl;
        cout << "2. Use Antivirus Software" << endl;
        cout << "3. Travel the Server Room" << endl;
        cout << "4. Browse Stackoverflow" << endl;
        cout << "5. Game Stats" << endl;
        if(Map1.getHackerCount() < 3) // give option to player if at least 1 hacker has been defeated
        {
            cout << "6. Move to next server room" << endl;
        }
        cout << "0. Quit Game" << endl;
        cout << "Select Option: ";
        cin >> option;
        cout << endl;

        switch(option)
        {
            case 1: // Repair Computer
            {
                if(computerMaintenanceLevel < 100)
                {
                    computerMaintenanceLevel = Player1.repairComputer(computerMaintenanceLevel);
                }
                else
                {
                    cout << "Computer Maintenance Level is alread 100." << endl;
                }
                cout << endl;
            } break;
            case 2: // Virus
            {
                if(computerViruses > 0)
                {
                    Player1.virus(computerViruses);
                }
                else 
                {
                    cout << "There are no Viruses on your computer." << endl;
                }
                cout << endl;
            } break;
            case 3: // Move Player
            {
                // Create moveset and display Map
                char move;
                // display map
                Map1.displayMap();

                // display available moves
                cout << "Avaliable moves:" << endl;
                Map1.displayMoves();

                // ask user to make a move
                cout << "Input a move: ";
                cin >> move;

                // move player position on map
                Map1.executeMove(move);

                if (Map1.isBestBuyLocation()) // if player lands on a BestBuy
                {
                    cout << "You're outside a Best Buy!" << endl;
                    string option;
                    cout << "Would you like to enter? y/n: ";
                    cin >> option;
                    cout << endl;
                    if(toLower(option) == "y")
                    {
                        // create array and fill it with player inventory quantities
                        int inventory[Player1.getSize()];
                        Player1.findInventoryStats(inventory);
                        int coins_left;
                        // input player coin amount, return new coin amount, change player coin amount
                        coins_left = (BestBuy1.buy(Player1.getMoney(), inventory));
                        Player1.setMoney(coins_left);

                        // Stock player inventory based on item bought
                        Player1.updateInventoryStats(inventory);
                    }
                }
                else if (Map1.isHackerLocation()) // if player lands on a Hacker
                {
                    cout << "You've encountered a Hacker!" << endl;
                    if(Player1.battle(serverRoomLevel, Map1.getHackerCount())) // Player Wins
                    {
                        cout << "You won 50 coins!" << endl;
                        Player1.setMoney(Player1.getMoney() + 50);
                        // Map1.removeHacker(Map1.getPlayerRowPosition(), Map1.getPlayerColPosition()); // remove hacker
                    }
                    else // Player loses
                    {

                        int index = Player1.subtractRandomPart();
                        cout << "You lost a " << Player1.getComputerPartName(index) << endl;
                    }
                }
                else if (Map1.isNPCLocation())  // if player lands on a NCP
                {
                    int result;
                    cout << "You've encountered an NPC!" << endl;
                    NPC NPC1 = NPC();
                    result = NPC1.startNPC();
                    if(result == 0)
                    {
                        int index = Player1.subtractRandomPart();
                        if(index != 7)
                        {
                            cout << "You lost a " << Player1.getComputerPartName(index) << endl;
                        }
                        else
                        {
                            cout << "You have nothing to lose." << endl;
                        }
                    }
                    else if(result == 1)
                    {
                        int index;
                        index = Player1.addRandomPart();
                        cout << "You won a " << Player1.getComputerPartName(index) << endl;
                    }
                    else if(result == 2)
                    {
                        srand(time(NULL));
                        cout << "Test your luck!" << endl;
                        int chance = (rand() % 3); 
                        if(chance == 0)
                        {
                            int index = Player1.subtractRandomPart();
                            if(index != 7)
                            {
                                cout << "You lost a " << Player1.getComputerPartName(index) << endl;
                            }
                            else
                            {
                                cout << "You have nothing to lose." << endl;
                            }
                        }
                        else if(chance == 1)
                        {
                            int index = Player1.addRandomPart();
                            cout << "You won a " << Player1.getComputerPartName(index) << endl;
                        }
                        else if(chance == 2)
                        {
                            cout << "Seems like nothing happened" << endl;
                        }
                    }
                }

                // Misfortunes
                srand(time(NULL));
                int chance = (rand() % 10);
                if(chance >= 0 && chance <= 2) // Misfortune occurs
                {
                    if(chance == 0) // lose pc part
                    {
                        int index = Player1.subtractRandomPart();
                        if(index != 7)
                        {
                            cout << "OH NO! You lost a " << Player1.getComputerPartName(index) << endl;
                        }
                        else
                        {
                            cout << "You have nothing to lose." << endl;
                        }
                    }
                    else if(chance == 1) // computer damaged
                    {
                        computerMaintenanceLevel -= 10;
                        cout << "OH NO! Your computer was damaged!" << endl;
                    }
                    else if(chance == 2) // increased frustration
                    {
                        cout << "OH NO! Why won't my code work! Your frustration has increased." << endl;
                        Player1.setFrustration(Player1.getFrustration() + 10);
                    }
                }
                cout << endl;

            } break;
            case 4: 
            {
                Player1.stackOverflow();
                cout << endl;
            } break;
            case 5:
            {

            } break;
            case 6:
            {
                if(Map1.getHackerCount() == 3)
                {
                    cout << "Invalid option." << endl;
                }
                else // continue to next server room 
                {

                }
            } break;
            case 0:
            {
                cout << "You quit the game!" << endl;
                gameStatus = false;
            } break;
            default:
            {
                cout << "Invalid input." << endl;
            } break;
        }


        // Check Game Conditions

        if(Player1.getFrustration() == 100)
        {
            gameStatus = false;
            cout << "Your frustration got too high and you quit the game!" << endl;
        }
        else if(carmensProgress == 100)
        {
            gameStatus = false;
            cout << "Carmen has succeeded at hacking the mainframe!" << endl;
        }
        else if(computerMaintenanceLevel == 0)
        {
            gameStatus = false;
            cout << "Computer Maintenance Level has reached 100!" << endl;
        }

        // End Game Conditions


    }while(gameStatus == true);

    cout << "GAME OVER!" << endl;
}