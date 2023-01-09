# Shogi in C



110503520 通訊二 葉易展

This is assighment 2



## Compile & Run



### #Compile



```javascript
>cd johnchi
>make
gcc -c src/johnchi.c -o build/johnchi.o
gcc -c src/timer.c -o build/timer.o
gcc src/main.c build/johnchi.o build/timer.o -lev -o bin/johnchi
```

### #Run
>make run
#### ->How to play
(1)    Input the coordinate of your chess.
(2)    Input the coordinate you want to go.
(3)    Turn to the other player 
* Input '0' to return to previus step
* Input 's' to save the process

### #Review
>make review

(review the game have been saved)
#### ->How to play
* Input 'f' to go to next step
* Input 'b' to return to previus step
* Input 'e' to exit review
