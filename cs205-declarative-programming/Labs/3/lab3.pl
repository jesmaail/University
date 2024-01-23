%Week 9 Task 1
add(0,X,X).
add(succ(X),Y,succ(Z)) :- add(X,Y,Z).

double(0, 0).
double(succ(X), succ(succ(Y))) :- double(X, Y).


%Exercise 3,2
directlyIn(katarina, olga).
directlyIn(olga, natasha).
directlyIn(natasha, irina).

in(X,Y) :- directlyIn(X,Y).
in(X,Y) :- directlyIn(X,Z), in(Z,Y).

%Exercise 3.3
directTrain(saarbruecken,dudweiler).
directTrain(forbach,saarbruecken).
directTrain(freyming,forbach).
directTrain(stAvold, freyming).
directTrain(fahlquemont, stAvold).
directTrain(metz, fahlquemont).
directTrain(nancy, metz).

travelFromTo(X,Y) :- directTrain(X,Y).
travelFromTo(X,Y) :- directTrain(X,Z), travelFromTo(Z,Y).

%Week 9 Task 4
child(anne,bridget).
child(bridget, caroline).
child(caroline, donna).
child(donna, emily).

descend(X,Y) :- child(X,Y).
descend(X,Y) :- descend(Z,Y), child(X,Z).