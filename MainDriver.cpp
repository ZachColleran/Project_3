#include <iostream>
#include "Player.h"
#include "BestBuy.h"
#include "NPC.h"

using namespace std;


int main()
{   
    // test Computer
    Computer Computer1 = Computer();
    cout << "Part Name: " << Computer1.getPartName() << endl;
    cout << "Quantity: " << Computer1.getPartQuantity() << endl;
    Computer Computer2 = Computer("Power Supply Unit", 1);
    cout << "Part Name: " << Computer2.getPartName() << endl;
    cout << "Quantity: " << Computer2.getPartQuantity() << endl;

    

    // test Player
    Player Player1 = Player();
    cout << "Name: " << Player1.getName() << endl;
    cout << "Money: " << Player1.getMoney() << endl;
    cout << "Frustration: " << Player1.getFrustration() << endl;
    // test Computer array
    Player1.getComputerPartNames();
    Player1.getComputerPartQuantities();
    

    // test NPC
    NPC NPC1 = NPC(), NPC2 = NPC(1, 1);

    NPC1.friendlinessGame();
    NPC1.puzzleGame();
    NPC2.friendlinessGame();
    NPC2.puzzleGame();

    // test Best Buy Stock

    BestBuy BestBuy1 = BestBuy();
    BestBuy BestBuy2 = BestBuy();
    cout << "Discount: " << BestBuy1.getDiscount() << endl;
    BestBuy1.displayStockInfo();

}