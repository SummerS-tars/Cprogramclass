# renew

## Menu

1. struct renew  
link between different rank  
2. fresh operation renew  
clear the screen -> cursor operation clear and reprint  
3. little changes
   1. help document specify
      1. stored in txt file  
      2. different game modes have their own help file  
4. new things  
   1. last play information  
   start new game or continue  
   2. save status change(menu itself)  

## Game

1. struct renew  
   1. player operation record -> linked list  
   2. some functions should renew  
   3. try to use `enum`  
2. existing bug fix
   1. redo operation will not be covered by common operation after rollback  
3. new functions
   1. save game progress  
   2. load game progress( or not )  
4. extra function attempt  
   1. ranking list  
   2. multilayer map  

## Realization

1. menu struct renew  
   1. menu status fresh  
   2. menu print fresh
