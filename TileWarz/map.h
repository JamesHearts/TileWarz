#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>
#include <sstream>
#include "tile.h"
#include "squad.h"

using namespace std;


class map
{
        tile* tileGrid[6][6];
        vector<squad*> faction1;
        vector<squad*> faction2;
        int moveCounter;
        int attackCounter;

    public:

        void createMap();
        void printMap();
        void createFaction(int player);
        void moveSquad(int player);
        void moveMenu(int x,int y);
        void startAttack(int player);
        void locateEnemy(int x,int y,int player);
        bool factionIsEmpty(int player);
        void battle(int x, int y, int player);
        int getMoveCounter();
        int setMoveCounter(int a);
        int getAttackCounter();
        int setAttackCounter(int a);
        int getInt();
        char getChar();
        int stringToNumber(string &input);


};


void map::createMap() //This function intializes the Map.
{
    /*char filename[36];

	cout << endl;
    cout << "Enter filename(.txt required): " << endl;
    cin.getline(filename, 36);*/

    ifstream file;

    file.open("Map.txt");

    if(!file.is_open())
    {
        cout << "FILE DOES NOT EXIST/FAILED TO OPEN FILE!" << endl;
        // can add error checking instead?
        exit(EXIT_FAILURE);
    }

    else
    {
        vector<char> mapData;

        char temp;

        while(!file.eof())
        {
            file.get(temp);

            if(islower(temp))
            {
                mapData.push_back(temp);
            }
        }

        /*for(int q = 0; q < mapData.size(); q++)
        {
            cout << mapData[q];
        }*/

        cout << endl;

        char read;
        int k = 0;

        //0 - plains, 1 - road, 2 - woods, 3 - city, 4 - HQ, 5 - mountain

        for(int i = 0; i < 6; i++)
        {

            for(int j = 0 ; j < 6 ; j++)
            {
                read = mapData[k];
                tileGrid[i][j] = new tile();
                switch(read)
                {
                case 'w': //woods - 2

                    tileGrid[i][j]->setTile(i,j,read);
                    //cout << "%";
                    k++;
                    break;
                case 'p': //plains - 0
                    tileGrid[i][j]->setTile(i,j,read);
                    //cout << " ";
                    k++;
                    break;
                case 'm': //mountain - 5
                    tileGrid[i][j]->setTile(i,j,read);
                    //cout << "M";
                    k++;
                    break;
                case 'c': //city - 3
                    tileGrid[i][j]->setTile(i,j,read);
                    //cout << "|";
                    k++;
                    break;
                case 'h': //HQ - 4
                    tileGrid[i][j]->setTile(i,j,read);
                    //cout << "+";
                    k++;
                    break;
                case 'r': //road - 1
                    tileGrid[i][j]->setTile(i,j,read);
                    //cout << "#";
                    k++;
                    break;

                default: //defaults to plains - 0
                    tileGrid[i][j]->setTile(i,j,read);
                    //cout << " ";
                    k++;
                    break;

                }

            }
        }

    }

}

void map::printMap()
{
    squad* temp;
    char terrain;

    cout << "     0   1   2   3   4   5" << endl;
    cout << "    ________________________" << endl;

    for(int i = 0; i < 6; i++)
    {
        cout << i << "  | ";
        for(int j = 0; j < 6; j++)
        {
            temp = tileGrid[i][j]->getOccupant();

            if(tileGrid[i][j]->getOccupant() == NULL)
            {
                terrain = tileGrid[i][j]->getTerrain();

                switch(terrain)
                {
                    case 'w': //woods - 2
                        cout << "\033[0;32mw\033[0m";
                        break;
                    case 'p': //plains - 0
                        cout << "\033[1;32mp\033[0m";
                        break;
                    case 'm': //mountain - 5
                        cout << "\033[1;31mm\033[0m";
                        break;
                    case 'c': //city - 3
                        cout << "\033[1;35mc\033[0m";
                        break;
                    case 'h': //HQ - 4
                        cout << "\033[0;33mh\033[0m";
                        break;
                    case 'r': //road - 1
                        cout << "\033[1;30mr\033[0m";
                        break;
                    default:
                        break;
                }

                cout << " | ";
            }
            else if(temp->faction == 1)
            {
                temp = tileGrid[i][j]->getOccupant();
                cout << "1" << " | ";
            }
            else if(temp->faction == 2)
            {
                temp = tileGrid[i][j]->getOccupant();
                cout << "2" << " | ";
            }

        }

        cout << endl;
        cout << endl;
    }

                        cout << "\033[0;32mw - woods(3mp)  \033[0m";
                        cout << "\033[1;32mp - plains(2mp)  \033[0m";
                        cout << "\033[1;31mm - mountain(!)  \033[0m" << endl;
                        cout << "\033[1;35mc - city(3mp)   \033[0m";
                        cout << "\033[0;33mh - hill(4mp)    \033[0m";
                        cout << "\033[1;30mr - road(1mp)  \033[0m" << endl;
                        cout << "1 - Player One   ";
                        cout << "2 - Player Two " << endl;
    cout << endl;
}

int map::getMoveCounter()
{
    return moveCounter;
}

int map::setMoveCounter(int a)
{
    moveCounter = a;
}

int map::getAttackCounter()
{
    return attackCounter;
}

int map::setAttackCounter(int a)
{
    attackCounter = a;
}

void printDice(int a)
{

    switch(a)
    {
    case 1:
        cout << "\033[1;31m ----- \033[0m" << endl;
        cout << "\033[1;31m|     |\033[0m" << endl;
        cout << "\033[1;31m|\033[0m" << "  O  " << "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m|     |\033[0m" << endl;
        cout << "\033[1;31m ----- \033[0m" << endl;
        break;
    case 2:
        cout << "\033[1;31m ----- \033[0m" << endl;
        cout << "\033[1;31m|\033[0m"  <<  "   O " << "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m|     |\033[0m" << endl;
        cout << "\033[1;31m|\033[0m" << " O   " <<   "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m ----- \033[0m" << endl;
        break;
    case 3:
        cout << "\033[1;31m ----- \033[0m" << endl;
        cout << "\033[1;31m|\033[0m"  <<  "   O " << "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m|\033[0m" << "  O  " <<   "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m|\033[0m" << " O   " <<   "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m ----- \033[0m" << endl;
        break;
    case 4:
        cout << "\033[1;31m ----- \033[0m" << endl;
        cout << "\033[1;31m|\033[0m"  <<  " O O " << "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m|     |\033[0m" << endl;
        cout << "\033[1;31m|\033[0m" << " O O " <<   "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m ----- \033[0m" << endl;
        break;
    case 5:
        cout << "\033[1;31m ----- \033[0m" << endl;
        cout << "\033[1;31m|\033[0m"  <<  " O O " << "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m|\033[0m" << "  O  " <<   "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m|\033[0m" << " O O " <<   "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m ----- \033[0m" << endl;
        break;
    case 6:
        cout << "\033[1;31m ----- \033[0m" << endl;
        cout << "\033[1;31m|\033[0m"  <<  " O O " << "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m|\033[0m" << " O O " <<   "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m|\033[0m" << " O O " <<   "\033[1;31m|\033[0m" << endl;
        cout << "\033[1;31m ----- \033[0m" << endl;
        break;
    default:
        break;


    }
}


int rollDice(int player)
{
    int roll;

    for (int i = 0; i < 2; i++)
    {

        for (int j = 0; j <6; j++)
        {
          //cout << rand()% 6+1 << endl;
          roll = rand()%6+1;
          return roll;
        }
    }

}


void map::createFaction(int player)
{
    int sizefaction1 = faction1.size();
    int sizefaction2 = faction2.size();

    int x;
    int y;
    int type;

    int count = 0;

    do
    {


        sizefaction1 = faction1.size();
        sizefaction2 = faction2.size();

        if(sizefaction1 == 3 && player == 1)
            {
                break;
            }
        if(sizefaction2 == 3 && player == 2)
            {
                break;
            }

        cout << "Choose a location to place squad: " << endl;

        while((cout << "X: ") && (!(cin >> x) || x<0 || x>5))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: " << endl;
		}

		cout << endl;

        while((cout << "Y: ") && (!(cin >> y) || y<0 || y>5))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: " << endl;
		}

        cout << endl;

        cout<< endl;


        tile* temp;
        temp = tileGrid[x][y];

        squad* tempSquad = new squad(x,y,type,player);


        if(temp->getOccupant() == NULL && temp->getTerrain() != 'm' && player == 1)  //Checks to see if the squad you want to move exists!
        {
                cout << "Squad successfully placed! " << endl;
                cout << endl;
                temp->setOccupant(tempSquad);
                faction1.push_back(tempSquad);
                this->printMap();
                count++;

        }
        else if(temp->getOccupant() == NULL && temp->getTerrain() != 'm' && player == 2)
        {
                cout << "Squad successsfully placed! " << endl;
                cout << endl;
                temp->setOccupant(tempSquad);
                faction2.push_back(tempSquad);
                this->printMap();
                count++;
        }
        else
        {
            cout << "There is an obstruction there! " << endl;
            createFaction(player);
        }
    }
    while(count < 3);


}



void map::moveMenu(int x, int y) //This function finds the possible movement choices and lets you choose which one is best.
{
    tile* temp = tileGrid[x][y]; //Points temp to the tile at x,y.
    tile* up;
    tile* down;
    tile* left;
    tile* right;
    squad* tempSquad;
    int moveCount = getMoveCounter();
    bool breakthis = false;

    //Now we start to check for edge cases.

    if(x == 0 && y == 0)
    {
        cout << "You entered: " << x << ", " << y << endl;

        right = tileGrid[x][y+1];
        down = tileGrid[x+1][y];



        if(right->getTerrain() != 'm' && right->getOccupant() == NULL)
        {
            cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
        }

        if(down->getTerrain() != 'm' && down->getOccupant() == NULL)
        {
            cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
        }

        char option;

        cout << "Choose an option (Enter a character): " << endl;

        breakthis = false;
		while(!breakthis){
			option = getChar();
			switch (option){
				case 'R':
				case 'r':
				case 'D':
				case 'd':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}

		cout << option << endl;
        cout << endl;

        if(option == 'R' || option == 'r')
        {
            if((moveCount - right->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                right->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (right->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'D' || option == 'd')
        {
            if((moveCount - down->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                down->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (down->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

    }

    else if(x == 5 && y == 0)
    {
        up = tileGrid[x-1][y];
        right = tileGrid[x][y+1];

        if(up->getTerrain() != 'm' && up->getOccupant() == NULL)
        {
            cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
        }

        if(right->getTerrain() != 'm' && right->getOccupant() == NULL)
        {
            cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
        }

        char option;

        breakthis= false;
       while(!breakthis){
			option = getChar();
			switch (option){
				case 'U':
				case 'u':
				case 'R':
				case 'r':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}


        cout << endl;

        if(option == 'U' || option == 'u')
        {
            if((moveCount - up->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                up->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (up->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;

        }

        else if(option == 'R' || option == 'r')
        {
            if((moveCount - right->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                right->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (right->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }


    }

   else if(x == 0 && y == 5)
    {
        left = tileGrid[x][y-1];
        down = tileGrid[x+1][y];

        if(left->getTerrain() != 'm' && left->getOccupant() == NULL)
        {
            cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
        }

        if(down->getTerrain() != 'm' && down->getOccupant() == NULL)
        {
           cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
        }

        char option;

        cout << "Choose an option (Enter a character): " << endl;

        breakthis = false;
        while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'D':
				case 'd':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
        cout << endl;

        if(option == 'L' || option == 'l')
        {
            if((moveCount - left->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                left->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (left->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'D' || option == 'd')
        {
            if((moveCount - down->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                down->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (down->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;

        }

    }

    else if(x == 5 && y == 5)
    {
        left = tileGrid[x][y-1];
        up = tileGrid[x-1][y];

        if(left->getTerrain() != 'm' && left->getOccupant() == NULL)
        {
            cout << "L - Option(right: " << left->getX() << ", " << left->getY() << ")" << endl;
        }

        if(up->getTerrain() != 'm' && up->getOccupant() == NULL)
        {
            cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
        }

        char option;

        cout << "Choose an option (Enter a character): " << endl;


        breakthis =false;
        while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
        cout << endl;

        if(option == 'L' || option == 'l')
        {
            if((moveCount - left->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                left->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (left->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'U' || option == 'u')
        {
            if((moveCount - up->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                up->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (up->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }
    }

    else if((x != 0 && x != 5) && y == 0)
    {
        right = tileGrid[x][y+1];
        down = tileGrid[x+1][y];
        up = tileGrid[x-1][y];

        if(right->getTerrain() != 'm' && right->getOccupant() == NULL)
        {
            cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
        }

        if(down->getTerrain() != 'm' && down->getOccupant() == NULL)
        {
            cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
        }

        if(up->getTerrain() != 'm' && up->getOccupant() == NULL)
        {
            cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
        }

        char option;

        cout << "Choose an option (Enter a character): " << endl;

        breakthis = false;
        while(!breakthis){
			option = getChar();
			switch (option){
				case 'R':
				case 'r':
				case 'D':
				case 'd':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}

        cout << endl;

        if(option == 'R' || option == 'r')
        {
            if((moveCount - right->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                right->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (right->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'D' || option == 'd')
        {
            if((moveCount - down->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                down->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (down->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;

        }

        else if(option == 'U' || option == 'u')
        {
            if((moveCount - up->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                up->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (up->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }
    }

    else if(x == 0 && (y != 0 && y != 5))
    {
        left = tileGrid[x][y-1];
        right = tileGrid[x][y+1];
        down = tileGrid[x+1][y];

        if(left->getTerrain() != 'm' && left->getOccupant() == NULL)
        {
            cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
        }

        if(right->getTerrain() != 'm' && right->getOccupant() == NULL)
        {
            cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
        }

        if(down->getTerrain() != 'm' && down->getOccupant() == NULL)
        {
            cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
        }

        char option;

        cout << "Choose an option (Enter a character): " << endl;


        breakthis = false;
        while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'R':
				case 'r':
				case 'D':
				case 'd':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}

        cout << endl;

        if(option == 'L' || option == 'l')
        {
            if((moveCount - left->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                left->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (left->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'R' || option == 'r')
        {
            if((moveCount - right->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                right->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (right->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'D' || option == 'd')
        {
            if((moveCount - down->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                down->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (down->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;

        }
    }

    else if(x == 5 && (y != 0 && y != 5))
    {
        left = tileGrid[x][y-1];
        right = tileGrid[x][y+1];
        up = tileGrid[x-1][y];

        if(left->getTerrain() != 'm' && left->getOccupant() == NULL)
        {
            cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
        }

        if(right->getTerrain() != 'm' && right->getOccupant() == NULL)
        {
            cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
        }

        if(up->getTerrain() != 'm' && up->getOccupant() == NULL)
        {
            cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
        }

        char option;

        cout << "Choose an option (Enter a character): " << endl;

         breakthis = false;
       while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'R':
				case 'r':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}


        cout << endl;

        if(option == 'L' || option == 'l')
        {
            if((moveCount - left->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                left->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (left->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'R' || option == 'r')
        {
            if((moveCount - right->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                right->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (right->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'U' || option == 'u')
        {
            if((moveCount - up->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                up->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (up->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

    }

    else if((x != 0 && x != 5) && y == 5)
    {
        left = tileGrid[x][y-1];
        down = tileGrid[x+1][y];
        up = tileGrid[x-1][y];

        if(left->getTerrain() != 'm' && left->getOccupant() == NULL)
        {
            cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
        }

        if(down->getTerrain() != 'm' && down->getOccupant() == NULL)
        {
            cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
        }

        if(up->getTerrain() != 'm' && up->getOccupant() == NULL)
        {
            cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
        }

        char option;

        cout << "Choose an option (Enter a character): " << endl;

        breakthis = false;
       while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'D':
				case 'd':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
        cout << endl;

        if(option == 'L' || option == 'l')
        {
            if((moveCount - left->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                left->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (left->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'D' || option == 'd')
        {
            if((moveCount - down->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                down->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (down->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;

        }

        else if(option == 'U' || option == 'u')
        {
            if((moveCount - up->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                up->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (up->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }


    }
    else
    {
         left = tileGrid[x][y-1];
         right = tileGrid[x][y+1];
         down = tileGrid[x+1][y];
         up = tileGrid[x-1][y];

        if(up->getTerrain() != 'm' && up->getOccupant() == NULL)
        {
            cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
        }

        if(down->getTerrain() != 'm' && down->getOccupant() == NULL)
        {
            cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
        }

        if(right->getTerrain() != 'm' && right->getOccupant() == NULL)
        {
            cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
        }

        if(left->getTerrain() != 'm' && left->getOccupant() == NULL)
        {
            cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
        }

        char option;

        cout << "Choose an option (Enter a character): " << endl;

        breakthis = false;
       while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'R':
				case 'r':
				case 'D':
				case 'd':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
        cout << endl;

        cout << endl;

        if(option == 'L' || option == 'l')
        {
            if((moveCount - left->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                left->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (left->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'D' || option == 'd')
        {
            if((moveCount - down->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                down->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (down->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;

        }

        else if(option == 'U' || option == 'u')
        {
            if((moveCount - up->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                up->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (up->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

        else if(option == 'R' || option == 'r')
        {
            if((moveCount - right->getMoveModifier()) >= 0)
            {
                tempSquad = temp->getOccupant();
                right->setOccupant(tempSquad);
                temp->setOccupant(NULL);
                moveCount = moveCount - (right->getMoveModifier());
                setMoveCounter(moveCount);
            }
            else
                cout << "Not enough move points! " << endl;
        }

    }

}






void map::moveSquad(int player) //This function facilitates squad movement.
{
    int x;
    int y;
    cout << "Which squad would you like to move?" << endl;


        while((cout << "X: ") && (!(cin >> x) || x<0 || x>5))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: " << endl;
		}

        cout << endl;
        while((cout << "Y: ") && (!(cin >> y) || y<0 || y>5))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: " << endl;
		}




    cout << endl;

    tile* temp = tileGrid[x][y];
    squad* tempSquad = temp->getOccupant();

    if(temp->getOccupant() == NULL)  //Checks to see if the squad you want to move exists!
    {
        cout << "Squad does not exist! " << endl;
        moveSquad(player);
    }
    else if(tempSquad->faction != player)
    {
        cout <<"This is not your squad! " << endl;
        moveSquad(player);
    }
    else
        moveMenu(x,y);
}


void map::locateEnemy(int x, int y, int player)
{

    tile* temp = tileGrid[x][y];
    tile* up;
    tile* down;
    tile* left;
    tile* right;
    squad* tempSquad;
    int enemies = 0;
    bool breakthis = false;

    if(x==0 && y==0)
    {
        down = tileGrid[x+1][y];
        right = tileGrid[x][y+1];

        if (right->getOccupant() !=NULL)
        {
            squad* tempSquad = right->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
                enemies++;
            }
        }

        else if (down->getOccupant()!= NULL)
        {
            squad* tempSquad = down->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
                enemies++;
            }
        }

        if(enemies == 0)
        {
            cout << "No enemies located! " << endl;
            startAttack(player);
            return;
        }

        char option;

        cout << "Who would you like to attack? " << endl;
        cout << "Choose an option (Enter a character): " << endl;

       while(!breakthis){
			option = getChar();
			switch (option){
				case 'R':
				case 'r':
				case 'D':
				case 'd':

					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
        cout << endl;

        if(option == 'D' || option == 'd')
        {
            battle(down->getX(), down->getY(), player);
        }

        else if(option == 'R' || option == 'r')
        {
            battle(right->getX(), right->getY(), player);
        }
    }

    else if (x==0 && y==5)
    {
        down = tileGrid[x+1][y];
        left = tileGrid [x][y-1];

        if (left->getOccupant()!= NULL)
        {
            squad* tempSquad = left->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
                enemies++;
            }

        }

        if (down->getOccupant()!= NULL)
        {
            squad* tempSquad = down->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
                enemies++;
            }
        }

        if(enemies == 0)
        {
            cout << "No enemies located! " << endl;
            startAttack(player);
            return;
        }

        char option;

        cout << "Who would you like to attack? " << endl;
        cout << "Choose an option (Enter a character): " << endl;

        breakthis = false;
       while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'D':
				case 'd':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
        cout << endl;

        if(option == 'L' || option == 'l')
        {
            battle(left->getX(), left->getY(), player);
        }

        else if(option == 'D' || option == 'd')
        {
            battle(down->getX(), down->getY(), player);
        }

    }

    else if (x==5 && y==0)
    {
        up = tileGrid[x-1][y];
        right = tileGrid[x][y+1];

        if (up->getOccupant()!= NULL)
        {
            squad* tempSquad = up->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
                enemies++;
            }
        }

        if (right->getOccupant()!= NULL)
        {
            squad* tempSquad = right->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
                enemies++;
            }
        }

        if(enemies == 0)
        {
            cout << "No enemies located! " << endl;
            startAttack(player);
            return;
        }


        char option;

        cout << "Who would you like to attack? " << endl;
        cout << "Choose an option (Enter a character): " << endl;

         breakthis = false;
       while(!breakthis){
			option = getChar();
			switch (option){
				case 'R':
				case 'r':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}

        cout << endl;

        if(option == 'U' || option == 'u')
        {
            battle(up->getX(), up->getY(), player);
        }

        else if(option == 'R' || option == 'r')
        {
            battle(right->getX(), right->getY(), player);
        }

    }

    else if (x == 5 && y ==5)
    {
        up = tileGrid[x-1][y];
        left = tileGrid[x][y-1];

        if (up->getOccupant()!= NULL)
        {
            squad* tempSquad = up->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
                enemies++;
            }
        }

        if (left->getOccupant()!= NULL )
        {
            squad* tempSquad = left->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
                enemies++;
            }
        }

        if(enemies == 0)
        {
            cout << "No enemies located! " << endl;
            startAttack(player);
            return;
        }


        char option;

        cout << "Who would you like to attack? " << endl;
        cout << "Choose an option (Enter a character): " << endl;

         breakthis = false;
       while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
        cout << endl;

        if(option == 'L' || option == 'l')
        {
            battle(left->getX(), left->getY(), player);
        }

        else if(option == 'U' || option == 'u')
        {
            battle(up->getX(), up->getY(), player);
        }

    }

    else if((x != 0 && x != 5) && y == 0)
    {
        right = tileGrid[x][y+1];
        down = tileGrid[x+1][y];
        up = tileGrid[x-1][y];

        if(right->getOccupant() != NULL)
        {
            squad* tempSquad = right->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
                enemies++;
            }
        }

        if(down->getOccupant() != NULL)
        {
            squad* tempSquad = down->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
                enemies++;
            }
        }

        if(up->getOccupant() != NULL)
        {
            squad* tempSquad = up->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
                enemies++;
            }
        }

        if(enemies == 0)
        {
            cout << "No enemies located! " << endl;
            startAttack(player);
            return;
        }


        char option;

        cout << "Who would you like to attack? " << endl;
        cout << "Choose an option (Enter a character): " << endl;

        breakthis = false;
       while(!breakthis){
			option = getChar();
			switch (option){
				case 'R':
				case 'r':
				case 'D':
				case 'd':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}


        cout << endl;

        if(option == 'D' || option == 'd')
        {
            battle(down->getX(), down->getY(), player);
        }

        else if(option == 'U' || option == 'u')
        {
            battle(up->getX(), up->getY(), player);
        }

        else if(option == 'R' || option == 'r')
        {
            battle(right->getX(), right->getY(), player);
        }

    }


    else if(x == 0 && (y != 0 && y != 5))
    {

        left = tileGrid[x][y-1];
        right = tileGrid[x][y+1];
        down = tileGrid[x+1][y];

        if(left->getOccupant() != NULL)
        {
            squad* tempSquad = left->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
                enemies++;
            }
        }

        if(right->getOccupant() != NULL)
        {
            squad* tempSquad = right->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
                enemies++;
            }
        }

        else if(down->getOccupant() != NULL)
        {
            squad* tempSquad = down->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
                enemies++;
            }
        }

        if(enemies == 0)
        {
            cout << "No enemies located! " << endl;
            startAttack(player);
            return;
        }


        char option;

        cout << "Who would you like to attack? " << endl;
        cout << "Choose an option (Enter a character): " << endl;

         breakthis = false;
       while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'R':
				case 'r':
				case 'D':
				case 'd':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
        cout << endl;

        if(option == 'L' || option == 'l')
        {
            battle(left->getX(), left->getY(), player);
        }

        else if(option == 'D' || option == 'd')
        {
            battle(down->getX(), down->getY(), player);
        }

        else if(option == 'R' || option == 'r')
        {
            battle(right->getX(), right->getY(), player);
        }

    }


    else if(x == 5 && (y != 0 && y != 5))
    {

        left = tileGrid[x][y-1];
        right = tileGrid[x][y+1];
        up = tileGrid[x-1][y];

        if(left->getOccupant() != NULL)
        {
            squad* tempSquad = left->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
                enemies++;
            }
        }

        if(right->getOccupant() != NULL)
        {
            squad* tempSquad = right->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
                enemies++;
            }
        }

        if(up->getOccupant() != NULL)
        {
            squad* tempSquad = up->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
                enemies++;
            }
        }

        if(enemies == 0)
        {
            cout << "No enemies located! " << endl;
            startAttack(player);
            return;
        }


        char option;

        cout << "Who would you like to attack? " << endl;
        cout << "Choose an option (Enter a character): " << endl;

         while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'R':
				case 'r':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
        cout << endl;

        if(option == 'L' || option == 'l')
        {
            battle(left->getX(), left->getY(), player);
        }

        else if(option == 'U' || option == 'u')
        {
            battle(up->getX(), up->getY(), player);
        }

        else if(option == 'R' || option == 'r')
        {
            battle(right->getX(), right->getY(), player);
        }

    }


    else if((x != 0 && x != 5) && y == 5)
    {

        left = tileGrid[x][y-1];
        down = tileGrid[x+1][y];
        up = tileGrid[x-1][y];

        if(left->getOccupant() != NULL)
        {
            squad* tempSquad = left->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
                enemies++;
            }
        }

        if(down->getOccupant() != NULL)
        {
            squad* tempSquad = down->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
                enemies++;
            }
        }

        if(up->getOccupant() != NULL)
        {
            squad* tempSquad = up->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
                enemies++;
            }
        }

        if(enemies == 0)
        {
            cout << "No enemies located! " << endl;
            startAttack(player);
            return;
        }


        char option;

        cout << "Who would you like to attack? " << endl;
        cout << "Choose an option (Enter a character): " << endl;

       breakthis = false;
      while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'D':
				case 'd':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
        cout << endl;

        if(option == 'L' || option == 'l')
        {
            battle(left->getX(), left->getY(), player);
        }

        else if(option == 'D' || option == 'd')
        {
            battle(down->getX(), down->getY(), player);
        }

        else if(option == 'U' || option == 'u')
        {
            battle(up->getX(), up->getY(), player);
        }

    }

    else
    {

        right = tileGrid[x][y+1];
        left = tileGrid[x][y-1];
        down = tileGrid[x+1][y];
        up = tileGrid[x-1][y];

        if(right->getOccupant() != NULL)
        {
            squad* tempSquad = right->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "R - Option(right: " << right->getX() << ", " << right->getY() << ")" << endl;
                enemies++;
            }
        }

        if(left->getOccupant() != NULL)
        {
            squad* tempSquad = left->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "L - Option(left: " << left->getX() << ", " << left->getY() << ")" << endl;
                enemies++;
            }
        }

        if(down->getOccupant() != NULL)
        {
            squad* tempSquad = down->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "D - Option(down: " << down->getX() << ", " << down->getY() << ")" << endl;
                enemies++;
            }
        }

        if(up->getOccupant() != NULL)
        {
            squad* tempSquad = up->getOccupant();

            if(tempSquad->faction != player)
            {
                cout << "An enemy has been located! " << endl;
                cout << "U - Option(up: " << up->getX() << ", " << up->getY() << ")" << endl;
                enemies++;
            }
        }

        if(enemies == 0)
        {
            cout << "No enemies located! " << endl;
            startAttack(player);
            return;
        }


        char option;

        cout << "Who would you like to attack? " << endl;
        cout << "Choose an option (Enter a character): " << endl;

       breakthis = false;
       while(!breakthis){
			option = getChar();
			switch (option){
				case 'L':
				case 'l':
				case 'R':
				case 'r':
				case 'D':
				case 'd':
				case 'U':
				case 'u':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}

        cout << endl;

        if(option == 'R' || option == 'r')
        {
            battle(right->getX(), right->getY(), player);
        }

        else if(option == 'L' || option == 'l')
        {
            battle(left->getX(), left->getY(), player);
        }

        else if(option == 'D' || option == 'd')
        {
            battle(down->getX(), down->getY(), player);
        }

        else if(option == 'U' || option == 'u')
        {
            battle(up->getX(), up->getY(), player);
        }

    }



}


void map::startAttack(int player) //This function facilitates squad movement.
{
    setAttackCounter(1);

    int x;
    int y;
    char option;
    bool breakthis = false;

    cout << "Would you like to keep attacking?(Y/N) " << endl;
    breakthis = false;
		while(!breakthis){
			option = getChar();
			switch (option){
				case 'Y':
				case 'y':
				case 'N':
				case 'n':
					breakthis = true ;
					break;
				default:
					cout << "Invalid input. Please try again: " << endl;
					break;
			}
		}
    cout << endl;

    if(option == 'N' || option == 'n')
    {
        return;
    }

    cout << "Which squad would you like to attack with? " << endl;



        while((cout << "X: ") && (!(cin >> x) || x<0 || x>5))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: " << endl;
		}


        cout << endl;
        while((cout << "Y: ") && (!(cin >> y) || y<0 || y>5))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: " << endl;
		}

    tile* temp = tileGrid[x][y];
    squad* tempSquad = temp->getOccupant();

    if(temp->getOccupant() == NULL)  //Checks to see if the squad you want to move exists!
    {
        cout << "Squad does not exist! " << endl;
        startAttack(player);
    }
    else if(tempSquad->faction != player)
    {
        cout <<"This is not your squad! " << endl;
        startAttack(player);
    }
    else
        locateEnemy(x,y,player);

    setAttackCounter(0);
}


bool map::factionIsEmpty(int player)
{
    if(player == 1)
    {
        if(faction1.size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(player == 2)
    {
        if(faction2.size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


}


void map::battle(int x, int y, int player)
{
    cout << "Player " << player << " attacks!" << endl;
    int dice1a;
    int dice1b;
    int dice2a;
    int dice2b;
    int total1;
    int total2;
    tile* temp = tileGrid[x][y];
    squad* tempSquad = temp->getOccupant();
    int pos;

    if(player == 1)
    {

        for(int i = 0; i < faction2.size(); i++)
        {
            if(faction2[i] == tempSquad)
            {
                pos = i;
            }
        }

        cout << "You get two dice rolls! The player with the highest total roll wins tile! " << endl;
        dice1a = rollDice(player);
        printDice(dice1a);
        dice1b = rollDice(player);
        printDice(dice1b);

        total1 = (dice1a + dice1b);
        cout << "You rolled a combination of: " << total1 << endl;

        cout << "Player 2's turn to roll! " << endl;

        dice2a = rollDice(player);
        printDice(dice2a);
        dice2b = rollDice(player);
        printDice(dice2b);
        cout << endl;

        total2 = (dice2a + dice2b);
        cout << "Player 2 rolled a combination of: " << total2 << endl;

        if(total1 > total2)
        {
            cout << "Player 1 wins the dice roll! " << endl;
            temp->setOccupant(NULL);
            faction2.erase(faction2.begin() +pos);
            cout << endl;
        }
        else if(total2 > total1)
        {
            cout << "Player 2 wins the dice roll! " << endl;
            cout << "Player 2 lives to tell the tale! " << endl;
            cout << endl;
        }
        else
        {
            cout << "Draw! No tiles were exchanged today! " << endl;
            cout << endl;
        }

    }

    if(player == 2)
    {
        for(int i = 0; i < faction1.size(); i++)
        {
            if(faction1[i] == tempSquad)
            {
                pos = i;
            }
        }

        cout << "You get two dice rolls! The player with the highest total roll wins tile! " << endl;
        dice1a = rollDice(player);
        printDice(dice1a);
        dice1b = rollDice(player);
        printDice(dice1b);

        total1 = (dice1a + dice1b);
        cout << "You rolled a combination of: " << total1 << endl;

        cout << "Player 1's turn to roll! " << endl;

        dice2a = rollDice(player);
        printDice(dice2a);
        dice2b = rollDice(player);
        printDice(dice2b);
        cout << endl;

        total2 = (dice2a + dice2b);
        cout << "Player 1 rolled a combination of: " << total2 << endl;

        if(total1 > total2)
        {
            cout << "Player 2 wins the dice roll! " << endl;
            temp->setOccupant(NULL);
            faction1.erase(faction1.begin() +pos);
            cout << endl;
        }
        else if(total2 > total1)
        {
            cout << "Player 1 wins the dice roll! " << endl;
            cout << "Player 1 lives to tell the tale! " << endl;
            cout << endl;
        }
        else
        {
            cout << "Draw! No tiles were exchanged today! " << endl;
            cout << endl;
        }

    }


}

char map :: getChar(){ // this example will accept chars programmed in the switch
    string input = "" ;
    char limit;
    char pass ;

    while(true){
        cin >> input ;
        limit = cin.peek() ;

        if(limit == '\n' && input.length() == 1){ // input is a good input
            pass = input[0] ;
            return pass;

        }
        else{
            cout << "Invalid Selection, please try again: " ;
        }

        cin.clear();
        cin.ignore(65534, '\n');
    }
}



int map :: getInt(){
    string input = "" ;
    char limit;

    char c;
    int letter;
    bool numgood = true;

    while(true){

        cin >> input ;
        limit = cin.peek() ;
        numgood = true ;


        if(limit == '\n'){ // input is a good input
            for(unsigned int i = 0 ; i < input.length() ; i++){
                c = input[i];
                letter = static_cast<int>(c) ;

                if(letter < 48 || letter > 57)
                    numgood = false ;
            } // checks if input is a number

            if(numgood){
				letter = stringToNumber(input) ;
                return letter;
			}
            else
                cout << "Invalid Selection, please try again: " ;

        }
        else{
            cout << "Invalid Selection, please try again: " ;
        }

        cin.clear();
        cin.ignore(65534, '\n');
    }
}



int map:: stringToNumber(string &input){
    stringstream ss(input);
    int letter ;
    return ss >> letter ? letter : 0 ;
}









#endif // MAP_H
