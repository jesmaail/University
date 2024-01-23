% some list examples

% member with remove
% takes an element from a list and also returns what's left

member_rem(X,[X|Xs],Xs). % take the first element

member_rem(Y,[X|Xs],[X|R]) :- member_rem(Y,Xs,R).

% could also be defined using append

member_rem2(X,L,R) :- append(L1,[X|L2],L),
                      append(L1,L2,R).


% a2b example - a2b(A,B) true if A is list of a's and B list of b's of same length

a2b([],[]).

a2b([a|As],[b|Bs]) :-
        a2b(As,Bs).

% test list consists of numbers

list_of_numbers([]).

list_of_numbers([X|Xs]) :-
        number(X),list_of_numbers(Xs).
