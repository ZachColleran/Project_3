#include <iostream>
#include <ctime>
#include <fstream>
#include "Player.h"
using namespace std;

void Player::initializeNames()
{
    parts[0].setPartName("CPU");
    parts[1].setPartName("GPU");
    parts[2].setPartName("Power Supply Unit");
    parts[3].setPartName("Computer Case");
    parts[4].setPartName("Keyboard and Mouse");
    parts[5].setPartName("Internet Card");
    parts[6].setPartName("Internet Provider Level");
    parts[7].setPartName("VPN");
    parts[8].setPartName("USB");
    parts[9].setPartName("Extra Computer");
}

string toLower1(string word)
{
    int length = word.length();
    for(int i = 0; i < length; i++)
    {
        if(isupper(word[i]))
        {
            word[i] += 32;
        }
    }
    // cout << word << endl;
    return word;
}

int split(string str, char splitter, string arr[], int size)
{
    if(str != "") // see if there is something in the start string
    {
        int count = 0; // start number of elements in the array at 0
        int strLen = str.length(); // length of start string
        string currStr = ""; // use to find spit-up string
        for(int i = 0; i <= strLen; i++) // loop for the legnth of the start string
        {
            if(str[i] == splitter || i == strLen) // if loops reaches the split character or the end
            {
                // cout << "CurrStr: " << currStr << endl; // test
                arr[count] = currStr; // add string to the array made from the else statement
                currStr = ""; // reset string that was put into the array
                count++;
            }
            else
            {
                currStr += str[i]; // if the current character of the start string is not a split character or the end,
                                        // that will eventually be added to the array
            }
        }
        if(size >= count) // if the number of elements is less then the size of the array
        {
            return count;
        }
        else // if the number of elements is greater than the size of the array
        {
            return -1;
        }
    }
    else
    {
        return 0;
    }
}


Player::Player() // default
{
    name = "";
    coins = 200;
    frustration = 0;
    initializeNames();
    for(int i = 0; i < size; i++)
    {
        if(i == 6 || i == 7) // Vpn and Internet Provider start at 1
        {        
            parts[i].setPartQuantity(1);
        }
        else
        {
            parts[i].setPartQuantity(0);
        }
    }
}
Player::Player(string n, int c, int f, Computer arr[]) // parametrized
{
    name = n;
    coins = c;
    frustration = f;
    initializeNames();
    for(int i = 0; i < size; i++)
    {
        parts[i].setPartQuantity(arr[i].getPartQuantity());
    }
}

// setters
void Player::setName(string n)
{
    name = n;
}
void Player::setMoney(int m)
{
    coins = m;
}
void Player::setFrustration(int f)
{
    frustration = f;
}
void Player::setStartName()
{
    string n = "";
    cout << "Please enter your name: ";
    cin >> n;
    cout << "Welcome " << n << '!' << endl;
    name = n;
}

// getters
string Player::getName()
{
    return name;
}
int Player::getMoney()
{
    return coins;
}
int Player::getFrustration()
{
    return frustration;
}
string Player::getComputerPartName(int i)
{
    return parts[i].getPartName();
}
void Player::getComputerPartNames() // All names
{
    for(int i = 0; i < size; i++) // get part names from array
    {
        cout << parts[i].getPartName() << ' ';
    }
    cout << endl;
}
void Player::getComputerPartQuantities() // get part Quantities from array
{
    for(int i = 0; i < size; i++)
    {
        cout << parts[i].getPartQuantity() << ' ';
    }
    cout << endl;
}
int Player::getSize()
{
    return size;
}

// other
void Player::viewPartsInventory()
{
    cout << "INVENTORY: " << endl;
    cout << "Coins: " << coins << 'c' << endl;
    for(int i = 0; i < 6; i++)
    {
        cout << parts[i].getPartName() << ": " << parts[i].getPartQuantity() << endl;
    }
}
void Player::viewWholeInventory()
{
    cout << "INVENTORY: " << endl;
    cout << "Coins: " << coins << 'c' << endl;
    for(int i = 0; i < size; i++)
    {
        cout << parts[i].getPartName() << ": " << parts[i].getPartQuantity() << endl;
    }
    
}
void Player::updateInventoryStats(int arr[])
{
    for(int i = 0; i < size; i++)
    {
        parts[i].setPartQuantity(arr[i]);
    }
}
void Player::findInventoryStats(int arr[])
{
    for(int i = 0; i < size; i++)
    {
        arr[i] = parts[i].getPartQuantity();
    }
}
int Player::addRandomPart()
{
    srand(time(NULL));
    int loops = 0; // used to check if Player's inventory is full of parts already, in that case, give player extra vpn
    int index = (rand() % 6); // randomize the part given
    while(true) // keep looping through until part is given
    {
        if(parts[index].getPartQuantity() == 3 && loops < 6) // check to see if player has max amount of parts already for that type and if loop has already checked the type of part
        {
            index++;
        }
        else if(parts[index].getPartQuantity() < 3 && loops < 6) // add 1 to part amount if conditions are met
        {
            parts[index].setPartQuantity((parts[index].getPartQuantity() + 1));
            return index;
        }

        if(loops == 6) // if the while lopp has already looped through all the parts
        {
            parts[7].setPartQuantity(parts[7].getPartQuantity() + 1);
            return 7;
        }
        loops++;
    }
}
int Player::subtractRandomPart()
{
    srand(time(NULL));
    int loops = 0; // used to check if Player's inventory is full of parts already, in that case, give player extra vpn
    int index = (rand() % 6); // randomize the part given
    while(true) // keep looping through until part is given
    {
        if(parts[index].getPartQuantity() == 0 && loops < 6) // check to see if player has 0 parts of that type and if loop has already checked the type of part
        {
            index++;
        }
        else if(parts[index].getPartQuantity() > 0 && loops < 6) // add 1 to part amount if conditions are met
        {
            parts[index].setPartQuantity((parts[index].getPartQuantity() - 1));
            return index;
        }

        if(loops == 6) // if the while lopp has already looped through all the parts
        {
            return 7;
        }
        loops++;
    }
}
int Player::repairComputer(int m)
{
    int part, quantity;
    // menu
    for(int i = 0; i < 6; i++)
    {
        cout << i + 1 << ". " << parts[i].getPartName() << ": " << parts[i].getPartQuantity() << endl;
    }
    cout << "0. Back" << endl;
    cout << "Select a part you wish to repair with: ";
    cin >> part;
    cout << endl;
    // end menu
    if(part > 0 && part < 7)
    {
        if(parts[part - 1].getPartQuantity() > 0)
        {
            cout << "How many " << parts[part - 1].getPartName() << "(s) do you wish to use? "; 
            cin >> quantity;
            cout << endl;
            if(parts[part - 1].getPartQuantity() >= quantity)
            {
                cout << "You used " << quantity << ' ' << parts[part - 1].getPartName() << "(s) to repair your computer maintenance by " << quantity * 20 << endl;
                if((quantity * 20) + m > 100)
                {
                    cout << "Computer maintenance is 100." << endl;
                    parts[part - 1].setPartQuantity(parts[part - 1].getPartQuantity() - quantity);
                    return 100;
                }
                else
                {
                    cout << "Computer maintenance is " << m + (quantity * 20) << '.' << endl;
                    parts[part - 1].setPartQuantity(parts[part - 1].getPartQuantity() - quantity);
                    return (m + (quantity * 20));
                }
            }
            else
            {
                cout << "You do not have that many parts available." << endl;
                return m;
            }
        }
        else
        {
            cout << "No available parts." << endl;
            return m;
        }
    }
    else if(part == 0)
    {
        
    }
    else
    {
        cout << "Invalid option" << endl;
        return m;
    }
}
int Player::virus(int v)
{
    int quantity;
    cout << "You currently have " << v << " Viruses and have " << parts[8].getPartQuantity() << " USB(s)" << endl;
    cout << "How many USBs do you wish to use: ";
    cin >> quantity;
    cout << endl;
    if(quantity < 0 && quantity < parts[8].getPartQuantity())
    {
        parts[8].setPartQuantity(parts[8].getPartQuantity() - quantity);
        cout << "You used " << quantity << " USB(s). Your computer now has " << parts[8].getPartQuantity() << " Viruses." << endl; 
        return (v - quantity);
    }
    else
    {
        cout << "You do not have that many parts available." << endl;
        return v;
    }
    return v;
}
bool Player::playPuzzle(int l)
{
    ifstream finP, finS;
    string n;
    int question = 0;

    finP.open("puzzles.txt");
    while(getline(finP, n)) // find question from txt
    {
        if(question == l) // if question matches puzzle number
        {
            if(n[0] != '-')
            {
                cout << n << endl;
            }
        }
        if(n[0] == '-') // if --- line occurs increase question number by 1S
        {
            question++;
        }
    }
    int answer = 0;
    finS.open("answers.txt"); 
    while(getline(finS, n)) // find answer from txt
    {
        if(answer == l) // if answer matches puzzle number
        {
            string userAnswer;
            cout << "Answer: ";
            cin >> userAnswer;
            cout << endl;
            cout << toLower1(userAnswer) << ' ' << toLower1(n) << endl; // check input an answer
            if(toLower1(userAnswer) == toLower1(n)) // if answer matches
            {
                cout << "True" << endl;
                return true;
            }
            else // if answer is incorrect
            {
                cout << "False" << endl;
                return false;
            }
        }
        if(n[0] == '-') // if --- line occurs find next answer from txt
        {
            answer++;
        }
    }
    return false;
}
void Player::stackOverflow()
{
    int option;
    srand(time(0));
    cout << "Your frustration right now is: " << frustration << endl;
    cout << "1. Solve a puzzle" << endl;
    cout << "2. Play a game of rock-paper-scissors" << endl;
    cout << "0. Exit" << endl;
    cout << "Select an option: ";
    cin >> option;
    cout << endl;
    switch(option)
    {
        case 1:
        {
            if(playPuzzle(rand() % 4))
            {
                cout << "You are correct!" << endl;
                if(frustration - 5 > 0)
                {
                    frustration -= 5;
                    cout << "Your frustration level is now: " << frustration << endl;
                }
            }
            else
            {
                cout << "You are incorrect!" << endl;
                frustration += 5;
                cout << "Your frustration level is now: " << frustration << endl;
            }
        } break;
        case 2:
        {
            string arr[] = {"Rock", "Paper", "Scissors"};
            int choiceU, choiceC; 
            for(int i = 0; i < 3; i++)
            {
                cout << i + 1 << ' ' << arr[i] << endl;
            }
            cout << "Enter your choice: ";
            cin >> choiceU; // user choice
            cout << endl;
            choiceC = ((rand() % 3) + 1); // Computer choice
            cout << choiceU << ' ' << choiceC << endl;
            if(choiceU > 0 && choiceU < 3) // Play game if User choice is valid
            {
                if(choiceU == choiceC)
                {
                    cout << "You Tie!" << endl;
                }
                else if(choiceU == 1)
                {
                    if(choiceC == 2)
                    {
                        cout << "You Lose!" << endl;
                        frustration += 5;
                        cout << "Your frustration level is now: " << frustration << endl;
                    }
                    else if(choiceC == 3)
                    {
                        cout << "You Win!" << endl;
                        frustration -= 5;
                        cout << "Your frustration level is now: " << frustration << endl;
                    }
                }
                else if(choiceU == 2)
                {
                    if(choiceC == 1)
                    {
                        cout << "You Win!" << endl;
                        frustration -= 5;
                        cout << "Your frustration level is now: " << frustration << endl;
                    }
                    else if(choiceC == 3)
                    {
                        cout << "You Lose!" << endl;
                        frustration += 5;
                        cout << "Your frustration level is now: " << frustration << endl;
                    }
                }
                else if(choiceU == 3)
                {
                    if(choiceC == 1)
                    {
                        cout << "You Lose!" << endl;
                        frustration += 5;
                        cout << "Your frustration level is now: " << frustration << endl;
                    }
                    else if(choiceC == 2)
                    {
                        cout << "You Win!" << endl;
                        frustration -= 5;
                        cout << "Your frustration level is now: " << frustration << endl;
                    }
                }
            }

        } break;
        case 0:
        {
            cout << "You have left Stack Overflow" << endl;
        } break;
        default: cout << "Invalid input" << endl; break;
    }
}


bool Player::battle(int f, int b)
{
    ifstream fin;
    string n, arr[2];
    string Hackers[20]; // store hacker names
    int i = 0; // iterator
    fin.open("hackers.txt");
    while(getline(fin, n)) // put hackers into an array
    {
        split(n, ',', arr, 2);
        Hackers[i] = arr[0];
        i++;
    }

    int option;
    do
    {
        cout << "1. Fight Hacker" << endl;
        cout << "2. Forfeit" << endl;
        cout << "Select an option: ";
        cin >> option;
        cout << endl;

        switch(option)
        {
            case 1: // Fight Hacker
            {
                srand(time(NULL)); 
                double result = (((rand() % 6) + 1) * parts[6].getPartQuantity()) - (((rand()/13 % 6) * f) * (double(1) / double(parts[7].getPartQuantity()))); // battle equation
                cout << "Result of the battle: " << result << endl;
                if(result > 0)
                {
                    cout << "You have defeated " << Hackers[((f - 1) * 4) + (3 - b)] << endl; // floor Level * 4 + Hackers already faced
                    return true;
                }
                else
                {
                    cout << "You lost to " << Hackers[(f * 4) + (3 - b)] << endl;
                    return false;
                }
                
            }
            case 2: // Forfeit
            {
                cout << "You ran away but not without consequences!" << endl;
                return false;
            }
            default:
            {
                cout << "Invalid option." << endl;
            }
        }


    } while (option == 1 || option == 2);

    return false;
}
