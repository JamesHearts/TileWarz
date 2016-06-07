#include "squad.h"
#include "tile.h"
#include "map.h"
#include <limits>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int player1;
int player2;
map map1;


int menu()
{
    int choice;

    cout<< "\033[1;31m ___________.__.__            __      __                      \033[0m" <<endl;
    cout<< "\033[1;31m \\__    ___/|__|  |   ____   /  \\    /  \\_____ _______  ______\033[0m" <<endl;
    cout<< "\033[1;31m   |    |   |  |  | _/ __ \\  \\   \\/\\/   /\\__  \\\\_  __ \\/  ___/\033[0m" <<endl;
    cout<< "\033[1;31m   |    |   |  |  |_\\  ___/   \\        /  / __ \\|  | \\/\\___ \\ \033[0m" <<endl;
    cout<< "\033[1;31m   |____|   |__|____/\\___  >   \\__/\\  /  (____  /__|  /____  >\033[0m" <<endl;
    cout<< "\033[1;31m                         \\/         \\/        \\/           \\/ \033[0m" <<endl;

    cout << "Welcome to the Game!" << endl;
    cout << "This is a two-player game! " << endl;
    cout << endl;
    cout << " 1: Start Game" << endl;
    cout << " 2: End Game"  << endl;
    cout << endl;
    cout << "Please enter a selection: ";




    while(!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";

    }

    cin.clear();
    cin.ignore();

    if(choice!=0)
    {

        if (choice == 1)
        {
            map1.createMap();   //Do not touch this function call!
            map1.printMap();
            cout << "Player 1, place your three units! " << endl;
            cout << "__________________________________"<< endl;
            map1.createFaction(1);
            cout << "Player 2, place your three units! " << endl;
            cout << "___________________________________"<<  endl;
            cout << endl;
            map1.createFaction(2);
            int movepoints1;
            int movepoints2;
            int attackpoints1;
            int attackpoints2;

            while(map1.factionIsEmpty(1) != true && map1.factionIsEmpty(2) != true)
            {
                map1.setMoveCounter(6);
                movepoints1 = 6;
                map1.setAttackCounter(1);
                attackpoints1 = 1;

                cout << "Player 1's turn! " << endl;
                cout << "___________________________________________"<< endl;

                while(movepoints1 != 0 && attackpoints1 != 0)
                {

                    movepoints1 = map1.getMoveCounter();

                    cout << "Player 1's choices: " << endl;
                    cout << "1: Move Squad---------Current movepoints: " << movepoints1 << endl;
                    cout << "2: Attack Squad.------Current attackpoints: " <<  attackpoints1 << endl;
                    cout << "3: Pass." << endl;

                    while(!(cin >> choice) || choice < 1 || choice > 3)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.  Try again: ";
                    }

                    switch(choice)
                    {
                    case 1:
                        movepoints1 = map1.getMoveCounter();
                        cout << endl;

                        if (movepoints1 > 0)
                        {
                            map1.moveSquad(1);
                            movepoints1 = map1.getMoveCounter();
                            map1.printMap();
                            cout << endl;
                            cout << "You have used move point(s)!"<< endl;
                            cout << "Updated movepoints: " << movepoints1 << endl;
                            cout << endl;
                        }
                        else
                            cout << "You don't have any move points, you should attack or pass! " << endl;
                        break;
                    case 2:
                        cout << endl;
                        if (attackpoints1 > 0)
                        {
                            map1.startAttack(1);
                            attackpoints1 = map1.getAttackCounter();
                            if(attackpoints1 == 0)
                            {
                                cout << "You have used your action point!" << endl;
                                movepoints1 = 0;
                                map1.printMap();
                                break;
                            }
                            else
                            {
                                break;
                            }
                        }
                        break;
                    case 3:
                        attackpoints1 = map1.getAttackCounter();
                        movepoints1 = 0;
                        break;
                    }

                }

                if(map1.factionIsEmpty(1) == true && map1.factionIsEmpty(2) == true)
                {
                    break;
                }

                map1.setMoveCounter(6);
                map1.setAttackCounter(1);
                movepoints2 = 6;
                attackpoints2 = 1;

                cout << endl;
                cout << "Player 2's turn! " << endl;
                cout << "___________________________________________"<< endl;

                while(movepoints2 != 0 && attackpoints2 != 0)
                {
                    movepoints2 = map1.getMoveCounter();
                    cout << endl;
                    cout << "Player 2's choices: " << endl;
                    cout << "1: Move Squad---------Current movepoints: " << movepoints2 << endl;
                    cout << "2: Attack Squad.------Current attackpoints: " <<  attackpoints2 << endl;
                    cout << "3: Pass. " << endl;

                    while(!(cin >> choice) || choice < 1 || choice > 3)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.  Try again: ";
                    }

                    switch(choice)
                    {
                    case 1:
                        movepoints2 = map1.getMoveCounter();
                        cout << endl;

                        if (movepoints2 > 0)
                        {
                            map1.moveSquad(2);
                            movepoints2 = map1.getMoveCounter();
                            map1.printMap();
                            cout << endl;
                            cout << "You have used move point(s)!"<< endl;
                            cout << "Updated movepoints: " << movepoints2 << endl;
                            cout << endl;
                        }
                        else
                            cout << "You don't have any move points, you should attack or pass! " << endl;
                        break;
                    case 2:
                        cout << endl;

                        if (attackpoints2 >=0)
                        {
                            map1.startAttack(2);
                            attackpoints2 = map1.getAttackCounter();
                            if(attackpoints2 == 0)
                            {
                                cout << "You have used your action point!" << endl;
                                movepoints2 = 0;
                                map1.printMap();
                                break;
                            }
                            else
                            {
                                map1.printMap();
                                break;
                            }
                        }
                        break;
                    case 3:
                        attackpoints2 = map1.getAttackCounter();
                        movepoints1 = 0;
                        break;

                    }

                }
            }

        if(map1.factionIsEmpty(1) == true)
        {
            cout << "PLAYER TWO WINS! " << endl;
        }

        if(map1.factionIsEmpty(2) == true)
        {
            cout << "PLAYER ONE WINS! " << endl;
        }

        }

        if (choice ==2)
        {
            cout << "Goodbye!" << endl;
            choice =0;
        }

    }
}

int main()
{
    srand(time(NULL));
    menu();

    return 0;
}
