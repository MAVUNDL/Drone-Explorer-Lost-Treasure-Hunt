# C-Game

This is a  simulator game that will teach the treasure hunters how to search for the map pieces
using the  drone technology.
You pilot a drone that flies over the Utopian forest in the game. The drone has a specific charge.
The drone can recharge at charging towers that stick out over the forest canopy. Hidden in the
trees are the map pieces. The drone can scan a specific area and uncover any features hidden
underneath the trees. The drone can collect the map piece when a map piece is found. The
game ends when the drone has found all the map pieces or the drone's battery runs out and
crashes into the trees.

***Initializing the game***

The size of the environment, the chance of charging towers getting destroyed and the
number of map pieces are given as command-line arguments.
• The world is filled in the following order. Entities cannot occupy the same position in
the world, except where stated otherwise:
◦ Every square in the world contains trees.
◦ Each row in the world area has one charging tower located in a random column.
Charging towers overwrite any trees in that location.
◦ The command line-defined map pieces are scattered randomly throughout the
world area. Map pieces are initially hidden and do not appear. Map pieces cannot
be placed on top of each other or on charging towers, but can be hidden below a
tree..
◦ The drone starts in a random row in any one of the last two columns of the area
(The right-hand side of the area).
◦ The drone flies over the trees and can occupy the same location as any other
feature in the world.
◦ The drone starts with a battery charge level of 10 units.

***Movement***
The player may move in any direction, including any diagonal direction.
• The player may not move outside the game area.
• The player may move over any square in the world area.
• The player may choose to initiate a scan. Scanning and area reveal the features hidden
under the trees. These features may be empty or contain a previously hidden map
piece. Scanning an area is similar to removing the trees from the scanning range.
• Moving the drone over to a charging station recharges the drone.
• Moving the drone over a map piece does not automatically collect the map piece.
Instead, the player must specifically choose to collect a map piece.
• Doing activities with the drone uses up the battery charge. The following describes the
battery charge used for the various activities:
◦ Moving: 1 Unit
◦ Scanning: 3 Units
◦ Collecting a map piece: 2 Units

***Updating***
There is a command line-defined percentage chance that each individual charging
tower may be destroyed by the indigenous people living in the jungle.

***End game***
The game succeeds when the player successfully collects all the map pieces
• The game fails when the drone runs out of battery charge.

