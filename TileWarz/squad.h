#ifndef SQUAD_H
#define SQUAD_H
#include <vector>


// from looking at the description, this class should be treated as a public entity or node with publicly accessible
// variables.

class squad{
	public:
		int posX;			// X-position on the map
		int posY;			// Y-position on the map
		int faction ;		// 0 - neutral, 1-Player 1, 2 - Player 2 etc...
		int actionPoints ;	// how many actions can be used by the unit
		int unitsInSquad ;	// number of units in each squad unit (default 5)
		bool moveThruMtn ;	// whether or not the unit can pass thru mountainous terrain
		char unitType ;		// add in unit types later, for now just representing type of unit with numbers 0, 1 and 2
                            // t-light tank, a-artillery, l-laser cannon, d-deez nut
		char firePattern ;	// firing style of unit, as follows:
							// d - default, targets 1 tile per unit and deals damage to targets in the tile
							// a - aoe shelling, targets 2x2 areas per unit and deals damage to all targets in each area
							// l - linear piercing, targets line of tiles extending from front of each unit and damages
							// 	   all units in the line
							// b - Bust nuts on all dem hoes with damage to entire map


		squad();
		squad(int x, int y, char unitType, int player);
		~squad();


};

squad::squad(int x, int y, char unitType, int player)
{
    //then assigns unit type
    this->posX = x;
    this->posY = y;
    this->unitType = unitType;
    this->faction = player;
    this->actionPoints = 6;
}



#endif // UNIT_H
