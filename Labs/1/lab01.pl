%Lab01 1.4
man(vincent).
man(jules).
woman(mia).


person(X) :- man(X); woman(X).
loves(X,Y) :- father(X,Y).
father(Y,Z) :- man(Y), son(Z,Y).
father(Y,Z) :- man(Y), daughter(Z,Y).

son(jules, vincent).
daughter(mia, vincent).