% fibonacci with memoing
:- dynamic fib_sav/2.

%  Inefficent recursive version

fib(0,1).
fib(1,1).

fib(N,F) :-
        N > 1,
        N1 is N-1,
        N2 is N-2,
        fib(N1,F1),
        fib(N2,F2),
        F is F1+F2.



% with memo

fibm(N,F) :-
        fib_sav(N,F),!. % see if we have it saved.

fib_sav(0,1).
fib_sav(1,1).

fibm(N,F) :-
       N > 1,
       N1 is N-1,
       N2 is N-2,
       fibm(N1,F1),
       fibm(N2,F2),
       F is F1+F2,
       assert(fib_sav(N,F)).
      

