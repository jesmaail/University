wizard(ron).
wizard(X) :- hasBroom(X), hasWand(X).
hasWand(harry).
quidditchPlayer(harry).
hasBroom(X) :- quidditchPlayer(X).