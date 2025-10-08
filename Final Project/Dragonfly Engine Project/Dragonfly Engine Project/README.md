# Bingus
An ASCII murder investigation game.


How many people can you save?

## Submission Details:
**Team**: wet - Ian Perry (ihperry@wpi.edu) & Devin Mihaichuk (drmihaichuk@wpi.edu)

**Platform**: Windows

**Engine**: Ian Perry's Dragonfly

**Genre**: Deduction

**How to comile**: Open solution in Visual Studio 2022 and build project

**File directory structure**: All source and header files can be located under the Dragonfly Engine Project folder with additional
						  audio and sprite files being located under the sounds_dev and sprites_dev folders respectively.

## Game Details:
Bingus is an ASCII murder investigation game that requires the player to figure out which of the 6 people within the building is a murderer
and is tasked with executing them before they can kill the player or cause serious harm to those around them.

**Features**: below is a list of all technical features that were implemented in the game:
- Shooting at where player has cursor
- Grid of 16 unique rooms that the player can traverse between
- NPC AIs that will walk between rooms and have interactions with the murderer
- Murderer AI that will look for opportunities to murder NPCs or the player
- Swapping the sprites of NPCs to indicate if they are alive, dead, or actively trying to kill
- Multiple endings based on the results of the game
- Clue system to hint at which NPC is the murderer
- Cutscenes that play before each ending

**Controls**: the player is able to move using the WASD keys and is able to fire their gun by left clicking using their mouse
		  as a way to aim on the screen. Be aware though that as soon as a shot is fired and hits a target the game will end 
		  one way or another so be careful at who you shoot and why. Players are also now allowed to investigate clues found 
		  in the middle of the floor of certain rooms by right clicking while being next to the clue and waiting for the investigation 
		  time around the player's reticle. There are two different series of clues (that being red and blue). The first two clues of 
		  each color give the row and column of the last clue of that color (|#| indicates column and -#- indicates row given the origin 
		  is in the upper left and using 1 indexing). The last clue for the blue clues indicate whether the killer is a cool or warm color 
		  character (blue, green, cyan vs red, magenta, yellow), and the red clues indicate whether the killer is in the RGB color scheme 
		  or the CMYK color scheme (red, green, blue vs cyan, magenta, yellow). Players are also allowed to quit out at anytime using Q. 
		  A reminder of these controls is displayed at the start screen of every game if you happen to forget and both the start 
		  and end screens show how to navigate to different screens as well as start and end the game. To navigate between rooms,
		  the player can move to the doorway of a room to move to it.

**Strategy**: the murderer is built to try and hide their murders as much as possible restricting themselves only to when they are alone with 
		  only one person in a room. This allows for the player to either try and bait out the murderer (such as going into rooms alone with
		  certain characters and seeing if they kill them) or by keeping track of where characters roughly are and seeing if any character
		  that was with another ends up dead. The first is arguably riskier, but allows for less character death and often a faster and more
		  decisive game. The second strategy can also be good, but is much more dependent on luck as it can be hard for the player to track
		  those characters unless they had just seen them and could lead to the player shooting a character that is not the murderer. When
		  considering the addition of clues, the Player can also choose to look for them to lower down the possibilities of finding the killer
		  instead but this has its own tradoff of taking some time to complete allowing for the possibility of NPCs to die.

**Endings**:  Bingus sports three different endings (excluding when the player chooses to stop playing). There is the good ending where the player
          correctly identifies the murderer and shoots them resulting in the player being informed that they have won, there is the ending
		  where the player dies having been murderered, and there is the bad ending where the player incorrectly identifies the murderer and
		  shoots an innocent person instead. The Player also gets a score at the end of the good ending detailing how many NPCs they were able 
		  to save as well as how many clues they were able to find.

**Enhancements**: below is a list of improvements that we made from the Alpha into the Final:
- Created better Music to better fit the atmosphere of the game
- Created better SFX to better fit the atmosphere of the game
- Created better Sprites for characters to make it look better
- Created better Sprites for rooms so they are easy to differentiate from each other
- Added clues the player can find to reveal who the murderer is
- Added rotoscoped cutscenes that play before each ending
- Fixed some bugs that were originally in the Alpha
