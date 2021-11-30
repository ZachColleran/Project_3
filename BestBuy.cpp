#include <iostream>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include "BestBuy.h"
using namespace std;

void BestBuy::initializeNames()
{
    stock[0].setPartName("CPU");
    stock[1].setPartName("GPU");
    stock[2].setPartName("Power Supply Unit");
    stock[3].setPartName("Computer Case");
    stock[4].setPartName("Keyboard and Mouse");
    stock[5].setPartName("Internet Card");
    stock[6].setPartName("Internet Provider Level");
    stock[7].setPartName("VPN");
    stock[8].setPartName("USB");
    stock[9].setPartName("Extra Computer");
}
void BestBuy::initializePrices()
{
    price[0] = 10;
    price[1] = 20;
    price[2] = 5;
    price[3] = 15;
    price[4] = 10;
    price[5] = 5;
    price[6] = 10;
    price[7] = 20;
    price[8] = 10;
    price[9] = 100;
}

BestBuy::BestBuy()
{
    initializeNames();
    initializePrices();
    for(int i = 0; i < size; i++) // set stock at random from 0-2
    {   
        // usleep(.5);
        srand(rand() % 1000);
        stock[i].setPartQuantity(rand() % 3);
    }
    floor = 1;
}
BestBuy::BestBuy(Computer arr[], int p[], int f) // set stock manually
{
    for(int i = 0; i < size; i++)
    {
        stock[i].setPartQuantity(arr[i].getPartQuantity());
    }
    for(int i = 0; i < size; i++)
    {
        price[i] = p[i];
    }
    floor = f;
}

// getters

int BestBuy::getFloor()
{
    return floor;
}

// other
void BestBuy::displayStockInfo() // cout the stock
{
    cout << "BEST BUY STOCK:" << endl;
    cout << "GPUs: " << stock[0].getPartQuantity() << "," << " CPUs: " << stock[1].getPartQuantity() << endl;
    cout << "Power Supply Unit: " << stock[2].getPartQuantity() << "," << " Computer Cases: " << stock[3].getPartQuantity() << endl;
    cout << "Internet Cards: " << stock[4].getPartQuantity() << "," << " Keyboard and Mouse: " << stock[5].getPartQuantity() << endl;
    cout << "Internet Providers: " << stock[6].getPartQuantity() << "," << " VPNs: " << stock[7].getPartQuantity() << endl;
    cout << "USBs: " << stock[8].getPartQuantity() << "," << " Extra Computers: " << stock[9].getPartQuantity() << endl;
    cout << endl;
}        
void BestBuy::startBestBuy()
{
    ifstream fin;
    string n;
    fin.open("best_buy_info.txt");
    while(getline(fin, n))
    {
        cout << n << endl;
    }
    cout << endl;
}   

int BestBuy::buyPart(int i, int coins, int arr[], int f)
{
    int quantity = 0;
    int priceIP[] = {0, 0, 10, 25, 40, 50}; // prices for internet provider
    double priceChange[] = {0, 1, 1.1, 1.2, 1.25, 1.3}; // price change per floor

    if(i == 6) // buying Internet Provider Level
    {   
        if(arr[i] < 5) // if Player is not already at max level
        {
            // menu
            for(int j = arr[i]; j < 5; j++)
            {
                cout << "Level " << (j + 1) << ": " << priceIP[j + 1] * priceChange[f] << 'c' << endl;
            }
            cout << endl;
            cout << "Your current " << stock[i].getPartName() << " is " << arr[i] << endl;
            cout << "What " << stock[i].getPartName() << " do you want to purchase? ";
            cin >> quantity;
            cout << endl;
             // end menu

            if(quantity > arr[i] && quantity < 6 && coins >= (priceIP[quantity] * priceChange[f])) // if input is valid
            {
               cout << "You have purchased " << stock[i].getPartName() << ' ' << quantity << endl;
               arr[i] = quantity;
               return (coins - (priceIP[quantity] * priceChange[f])); // return total coins after loss
            }
            else if(quantity < arr[i] || quantity > 5) // if user input is out of range
            {
                cout << "Invalid inout." << endl;
                return coins;
            }
            else
            {
                cout << "You do not have enough money to purchase item." << endl;
                return coins;
            }
        }
        else // if at max level already
        {
            cout << "You are already at max " << stock[i].getPartName() << endl;
            return coins;
        }
        
    }
    else // buying anything else
    {
        cout << "How many " << stock[i].getPartName() << "s do you want to buy? Availability: " << stock[i].getPartQuantity() << endl;
        cin >> quantity;
        if(quantity >= 0 && quantity <= stock[i].getPartQuantity())
        {
            if(coins >= (price[i] * priceChange[f] * quantity) && (arr[i] + quantity) <= 3) // check money available and if inventory is full
            {
                cout << "You bought " << quantity << ' ' << stock[i].getPartName() << "(s)." << endl;
                stock[i].setPartQuantity(stock[i].getPartQuantity() - quantity); // revove items from stock
                arr[i] += quantity; // add qauntity to arr for adding value to player inventory
                return (coins - (price[i] * quantity)); // output coins remaining
            }
            else
            {
                cout << "You do not have enough money or inventory space to purchase " << quantity << ' ' << stock[i].getPartName() << "(s)." << endl;
                return coins;
            }
        }
        else if(quantity < 0)
        {
            cout << "Invalid input. Negative value." << endl;
            return coins;
        }
        else if(quantity > stock[i].getPartQuantity())
        {
            cout << "Not enough parts in stock." << endl;
            return coins;
        }
        else
        {
            cout << "Invalid input. Other." << endl;
            return coins;
        }
    }
}

int BestBuy::buy(int coins, int arr[], int f)
{
    int optionStart;
    double priceChange[] = {0, 1, 1.1, 1.2, 1.25, 1.3}; // price change per floor
    do {

        cout << endl;
        cout << "You have " << coins << " coins available." << endl;
        cout << "1. Computer Parts" << endl;
        cout << "2. Antivirus Software" << endl;
        cout << "3. Virtual Private Network" << endl;
        cout << "4. Internet Provider" << endl;
        cout << "0. Exit" << endl;
        cout << "Select category to buy from: ";
        cin >> optionStart;
        cout << endl;

        switch(optionStart)
        {
            case 1: 
            {
                int option1;
                int quantity = 0;


                // output 'Menu'
                cout << "You have " << coins << " coins available." << endl;
                cout << "NAME(AVAILABLITY): PRICE" << endl;
                for(int i = 0; i < 6; i++)
                {
                    cout << (i + 1) << ". " << stock[i].getPartName() << '(' << stock[i].getPartQuantity() << "): " << price[i] * priceChange[f] << 'c' << endl;
                }
                cout << "10. " << stock[9].getPartName() << '(' << stock[9].getPartQuantity() << "): " << price[9] * priceChange[f] << 'c' << endl;
                cout << "0. Back" << endl;

                // user input
                cout << "Select an item to buy: ";
                cin >> option1;
                cout << endl;

                // buy parts
                switch(option1)
                {
                    case 1: coins = buyPart(0, coins, arr, f); break;
                    case 2: coins = buyPart(1, coins, arr, f); break;
                    case 3: coins = buyPart(2, coins, arr, f); break;
                    case 4: coins = buyPart(3, coins, arr, f); break;
                    case 5: coins = buyPart(4, coins, arr, f); break;
                    case 6: coins = buyPart(5, coins, arr, f); break;
                    case 10: coins = buyPart(9, coins, arr, f); break;
                    case 0: break;

                    default: cout << "Invalid option. Try again." << endl;
                }
            } break;
            case 2:
            {
                int option2;
                // output 'Menu'
                cout << "You have " << coins << " coins available." << endl;
                cout << "1. Purchase USB(" << stock[8].getPartQuantity() << "): " << price[8] << 'c' << endl;
                cout << "0. Back" << endl;
                cout << "Select an option: ";
                cin >> option2;
                
                // buy part
                switch(option2)
                {
                    case 1: coins = buyPart(8, coins, arr, f); break;
                    case 0: break;
                    default: cout << "Invalid input." << endl; break;
                } 
                
            } break;
            case 3: 
            {
                int option3;

                // output 'Menu'
                cout << "You have " << coins << " coins available." << endl;
                cout << "1. Purchase VPN(" << stock[7].getPartQuantity() << "): " << price[7] << 'c' << endl;
                cout << "0. Back" << endl;
                cout << "Select an option: ";
                cin >> option3;

                // buy part
                switch(option3)
                {
                    case 1: coins = buyPart(7, coins, arr, f); break;
                    case 0: break;
                    default: cout << "Invalid input." << endl; break;
                }

            } break;
            case 4: 
            {
                int option4;

                // output 'Menu'
                cout << "You have " << coins << " coins available." << endl;
                cout << "1. Purchase Internet Provider Level" << endl;
                cout << "0. Back" << endl;
                cout << "Select an option: ";
                cin >> option4;
                cout << endl;

                switch(option4)
                {
                    case 1: coins = buyPart(6, coins, arr, f); break;
                    case 0: break;
                    default: cout << "Invalid input." << endl; break;
                }

            } break;
            case 0: break;

            default: cout << "Invalid input. Try again." << endl; break;
        }
        
    } while(optionStart != 0);

    return coins;
}


