TileWarz is a C++ text based game.
---------------------------------------------------------------------------------------------------------

The game is a mixed between checkers and battleship. Battles are decided through the roll of dice. The game is almost 99% playable. There is one bug that I have to fix and will fix when I get around to it. If you find it and fix it first then let me know!

As the game starts player one gets to place their pieces on the board. Then player two gets to place their piece on the board. When it is a players turn the player gets to choose where they want to move a piece and how many spaces they would like to move. The player is given a number of movement tokens, everytime the player moves their piece the total number of tokens is deduced. The number of tokens that is deduced is dependent on the terrain of the board.

The board is made up of defined cells. Each cell contains a terrain property. The type of terrain dictates how many tokens is required to move there and if a piece can actually be moved there in the first place. 

When two pieces of the opposite team meet they can choose to "encounter". When this happens the player will roll a dice in order to win cell. If the cell is won the attacking piece moves to the cell and the defending piece is removed from the board.

The game ends when all the pieces of any team are removed from the board. 

