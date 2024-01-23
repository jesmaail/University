
%Exercise 4.3
second([_|T], Y) :- member(T, Y).
member([H|_], Y) :- H=:=Y.	

%alt([_,X|_], X).

%Exercise 4.6
twice([], []).
twice([X|Y], [X, X | Z]) :- twice(Y,Z).

%Exercise 5.3
addOne([], []).
addOne([X|Y], [Z|W]) :-	is(Z, +(X,1)),
						addOne(Y,W).

%Exercise 6.1
doubled(List) :-	split(List,X,Y),
					equal(X,Y).

equal([],[]).
equal([X|Y], [X|Z]) :- equal(Y,Z).

pre(P,L) :- append(P,_,L).
suf(S,L) :- append(_,S,L).

split([],[],[]).
split(L, P, S) :-	pre(P,L),
					suf(S,L),
					length(L, LLength),
					length(P, PLength),
					length(S, SLength),
					PLength is SLength,
					LLength is PLength + SLength.

%append(x,x,List)