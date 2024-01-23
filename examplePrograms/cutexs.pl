% first max

max(X,Y,Y) :- X =< Y.

max(X,Y,X) :- X > Y.

% version with green cut

max1(X,Y,Y) :- X =< Y,!.

max1(X,Y,X) :- X > Y.

% without 2nd body

max2(X,Y,Y) :- X =< Y,!.

max2(X,_,X).


% unification after crossing cut

max3(X,Y,Z) :- X =< Y,!,Z = Y.

max3(X,_,X).


% removing ! gives non-equivalent predicate - RED cut
% gives for example max4(3,4,3) as a solution!

max4(X,Y,Z) :- X =< Y,Z = Y.

max4(X,_,X).



