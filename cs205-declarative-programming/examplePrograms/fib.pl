% fibonacci

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



a(N,A) :-
        fib(N,F),
        N1 is N-1,
        fib(N1,F1),
        A is F/F1.

golden(G) :-
        G is (1+sqrt(5))/2.

% more fficient version

fib(0,_,_,1).
fib(1,1,0,1).

fib(N,FN1,FN2,FN) :-
        N>1,
        N1 is N-1,
        fib(N1,FN2,_,FN1),
        FN is FN1+FN2.

% new fib function


nfib(N,F) :- fib(N,_,_,F).

% using a list to store fib values i.e. [Fn,Fn-1,Fn-2,....1]

fib_lst(0,[1]).
fib_lst(1,[1,1]).

fib_lst(N,[F3,F2,F1|X]) :-
        N > 1,
        N1 is N-1,
        fib_lst(N1,[F2,F1|X]),
        F3 is F2+F1.

% fib now just takes head of list

nnfib(N,F) :- fib_lst(N,[F|_]).


aa(N,A) :-
        fib(N,F1,_,F),
        A is F/F1.
        

fib3(N,F) :-
        fib_lst(N,[F|_]).


