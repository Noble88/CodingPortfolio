Name: Henry Burton
Student number: 2418581
class section: 04

Sources
Note: (I Know) means I already know how what is listed and I'd be wasting my time other wise
-GPT: general compiler errors
-GPT: To get the code to read lines 4 to 8 (I Know)
-GPT: Write code for random num genorator from 1-100
-GPT: Made the code to add the Generated level to the WorldLayout 3D array
-GPT: Made printing the array (I Know)
-GPT: code to get the distination when moving a direction (I Know)
-GPT: Making the line of code that makes the main method wait 1 second
-GPT: writing array to text file (I Know)





    Other Misc Planning

//Outline

World
- Stores Level Object 
- Method: wrapping vertically & horizontally
- Method: Switching levels
- Method: Display current level
- Method Generate Level

Mario
- Collisions -> Coins, Warp Pipe, Enemies, Boss
- Random Movement
- Power level Management
- 


//Insteructions
World 
- L = is final level (which will be provided at runtime.)

Level
- Represented by: NxN grid (think 2D array) & N (provided at runtime)
- Mario nav via left right up down
- grid wraps horizontally and vertically (a torus)
-- Mario is in the rightmost column and moves right, he will wrap to the same row in the leftmost column.
--- SO WHOLE SCREEN CHANGES WHEN HIT RIGHT SIDE 
- Can have Coin, mushroom, Goomba or a Koopa Troopa, The boss of the level (there must be exactly 1 per level), or nothing




Mario
- V = Lives (which will be provided at runtime)
- can ability to collect coins (He starts with 0 coins)
-- every 20 coins collected = 1 up (coins resets to 0))
- 3 Power level (PL0, PL1, PL2) (PL0 = weakest)
-- Mushroom = ++ power level
-- If hurt -- power level


Mario Interaction with the Environment
- begin at a random location in the first level (w/ PL0)
-- starts interacting with the environment immediately. 
-Once he has interacted with the current location -> moves on to the next location by moving up, down, left, or right. The direction is chosen randomly with uniform probability
-Conditions
--moves to position has nothing, Mario moves on.
--if pos is coin -> adds coin, delete coin, Mario moves on
--if pos is mushroom -> increase power level
--if enemy -> do regular enemy collision
--if boss -> do boss collision interaction
--if warp pipe -> jump to randdom posiition in next level (no need to beat boss)

Mario’s Interaction with a Regular Enemy
- IF DEATH -> --life and resume from same location if have enough life -> if no game over
when hit enemy mario does code and moves on 
- if goomba -> 80 precent kill enemy, empty if killed and 20 precent lose power level
- if Koopa -> 65 precent kill, empty pos, 
- if KILLS 7 enemies (on same life) -> life++

Mario’s Interaction with Boss
- 50 precent kill boss, empty pos, next level, 
-- if last level game win
- If mario hit -> lose 2 power level, attempts interaction again

Level Characters 
● x - nothing
● m - a mushroom
● c - a coin
● g - a Goomba
● k - a Koopa Troopa
● b - the level boss
● w - a warp pipe
● H - stands for hero. Mario’s current position.