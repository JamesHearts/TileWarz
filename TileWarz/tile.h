#ifndef TILE_H
#define TILE_H
#include <cstdlib>
#include <iostream>
#include <squad.h>

using namespace std;

class tile{
	int x; 		// tile's x coordinate.
	int y; 		// tile's y coordinate.
	char terrain;	// tile's type, as follows:
					// p - plains, r - road, w - woods, c - city, H - HQ, m - mountain

	int defenseModifier;
	int moveModifier;
	bool obstruction;
	squad* occupant;

	public:
		tile() ;
		~tile() ;
		void setTile(int x, int y, char type);

		void changeTerrain(char type);
		void boostDefense(int boost);
		bool getObstruction();
		char getTerrain();
		void setOccupant(squad *x); //sets the occupant at the tile
        squad* getOccupant(); //gets the occupant at the tile
        int getX();
        int getY();
        int getMoveModifier();

};

tile::tile()
{			// by default with no parameters make plains
	terrain = 'p' ;
	defenseModifier = 1 ;
	moveModifier = 1 ;
	obstruction = false ;
	occupant = NULL;
}

tile::~tile()
{
}

void tile::setTile(int x, int y, char type)
{
	this->x = x ;
	this->y = y ;
	terrain = type ;

	switch(type)
	{	// switches are your friends, use them more.
		case 'p':
			defenseModifier = 1 ;
			moveModifier = 2 ;
			obstruction = false ;
			break;

		case 'r':	// these seem useless according to stats and actually hurt you
			defenseModifier = 0 ;
			moveModifier = 1 ;
			obstruction = false ;
			break;

		case 'w':
			defenseModifier = 2 ;
			moveModifier = 3 ;
			obstruction = true ;
			break;

		case 'c':
			defenseModifier = 3 ;
			moveModifier = 3 ;
			obstruction = true ;
			break;

		case 'h':
			defenseModifier = 4 ;
			moveModifier = 4 ;
			obstruction = true ;
			break;

		case 'm':
			defenseModifier = 4 ;
			moveModifier = 6 ;
			obstruction = false ;
			break;

		default:
			terrain = 'p' ;
			defenseModifier = 1 ;
			moveModifier = 2 ;
			obstruction = false ;
		break;
	}
}

void tile::changeTerrain(char type)
{
    terrain = type;
}

void tile::boostDefense(int boost)
{
	defenseModifier += boost ;
}

void tile::setOccupant(squad *x) //this function sets the occupant of the tile.
{
    this->occupant = x;
}

squad* tile::getOccupant()
{
    return this->occupant;
}

char tile::getTerrain()
{
    return terrain;
}

int tile::getX()
{
    return x;
}

int tile::getY()
{
    return y;
}

int tile::getMoveModifier()
{
    return moveModifier;
}

#endif // TILE_H
