#include "Computer.cpp"
#include "BestBuy.cpp"
#include "Player.cpp"
#include "NPC.cpp"
#include "Map.cpp"

#include <iostream>
using namespace std;

void CreateHackers(Map currMap)
{
    srand(time(0));
    while(currMap.getHackerCount() < 3)
    {
        currMap.spawnHacker(rand() % 4, rand() % 8);
    }
}
void createNPCs(Map currMap)
{
    srand(time(0));
    while(currMap.getNPCCount() < 3)
    {
        currMap.spawnNPC(rand() % 4, rand() % 8);
    }
}
void createBestBuy(Map currMap)
{
    srand(time(0));
    while(!currMap.isBestBuyOnMap())
    {
        currMap.spawnHacker(rand() % 4, rand() % 8);
    }
}