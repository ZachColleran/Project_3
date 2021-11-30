#include <iostream>
#include <fstream>
#include <ctime>
#include "NPC.h"
using namespace std;

string toLower(string word)
{
    for(int i = 0; i < word.length(); i++)
    {
        if(isupper(word[i]))
        {
            word[i] += 32;
        }
    }
    // cout << word << endl;
    return word;
}


// constructor
NPC::NPC() // default
{
    srand(time(NULL));
    friendliness = (rand() % 3);
    puzzle = (rand() % 4);
}
NPC::NPC(int f, int p) // parametrized
{
    friendliness = f;
    puzzle = p;
}

// setters
void NPC::setFriendliness(int f)
{
    friendliness = f;
}
void NPC::setPuzzle(int p)
{
    puzzle = p;
}

// getters
int NPC::getFriendliness()
{
    return friendliness;
}
int NPC::getPuzzle()
{
    return puzzle;
}

// other
void NPC::puzzleGame() // have three different games at random* Not implimented yet
{
    if(puzzle == 0) 
    {
        cout << "Puzzle 1" << endl;
    }
    else if(puzzle == 1)
    {
        cout << "Puzzle 2" << endl;
    }
    else if(puzzle == 2)
    {
        cout << "Puzzle 3" << endl;
    }
}
void NPC::friendlinessGame() // at random (not implimented) decided friendliness of NPC
{
    if(friendliness == 0)
    {
        cout << "Neutral NPC!" << endl;
    }
    else if(friendliness == 1)
    {
        cout << "Friendly NPC!" << endl;
    }
    else if(friendliness == 2)
    {
        cout << "Unfriendly NPC!" << endl;
    }
}
bool NPC::playPuzzle(int l)
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
            // cout << toLower(userAnswer) << ' ' << toLower(n) << endl; // check input an answer
            if(toLower(userAnswer) == toLower(n)) // if answer matches
            {
                return true;
            }
            else // if answer is incorrect
            {
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

int NPC::startNPC()
{
    int option = 1;
    int valid = 1;
        cout << "1. Solve puzzle" << endl;
        cout << "2. Try to leave safely" << endl;
        cout << "Select an option: ";
        cin >> option;
        cout << endl;

        switch(option)
        {
            case 1:
            {
                if(playPuzzle(puzzle)) // if puzzle is done correctly
                {
                    cout << "You are Correct!" << endl;
                    return 1;
                }
                else // if puzzle is done incorrectly
                {
                    cout << "You are Incorrect!" << endl;
                    return 0;
                }

            } break;
            case 2:
            {
                return 2;

            } break;
            default: cout << "Invalid option. Try again." << endl; return 3; break;
        }
}