# Project 1

## Basic Goal

### Function

1. move  
   1. up
   2. down
   3. left
   4. right
   5. no action
2. interact
   1. wall
   2. trap
   3. treasure
3. record
   1. way
   2. energy cost
4. mode
   1. real-time mode
   2. program mode

### Map

1. ASCII character
   1. wall
   2. treasure
   3. trap  
   4. player(huang)
   5. blank
2. rule  
   1. no overstep  
   2. trap punishment  
   3. final goal : get all the treasure  

### Menu

1. welcome
   1. start
   2. exit
2. menu control logic
   1. switch game level
   2. switch the mode

## Details

### Menu Content

1. menu hierarchy  
   1. main menu
   2. map selection
   3. control mode selection
2. main menu
   1. start game
   2. help
   3. exit
3. map selection
   1. several maps
   2. custom map
   3. upper menu(main menu)
4. control mode selection
   1. real-time mode
   2. programming mode

### Menu Function

   1. select menu hierarchy
   2. print menu
   3. move cursor
   4. trigger option

### Map Content

1. character definition
   1. space:ground
   2. W:wall
   3. D:trap
   4. T:treasure
   5. Y:xiaohuang
2. map interaction definition
   1. get treasure
   2. get trapped
   3. hit the wall
   4. move on ground
3. map input
   1. fixed game level
   2. custom game level

### Map Function

1. storage the map data
2. print the map data
3. custom map setting

### Player Movement

1. basic move
2. map interaction
3. rollback operation

### Player Information

1. position
2. energy cost
3. treasure acquisition number
4. trap trigger status
5. several past operation record
