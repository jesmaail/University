% factorial function

% normal definition

fact(0,1).  % 0! = 1

fact(N,F) :-
        N>0,
        N1 is N-1,
        fact(N1,F1),
        F is N*F1.


% with accumulating parameter

fact_a(0,R,R).

fact_a(N,A,R) :-
        N1 is N-1,
        A1 is N*A,
        fact_a(N1,A1,R).

fact2(N,F) :- fact_a(N,1,F).


% sum of first N natural numbers

sum_to_n(0,0).

sum_to_n(N,S) :-
        N>0,
        N1 is N-1,
        sum_to_n(N1,S1),
        S is S1+N.

% with accumulating parameter

sum_a(0,A,A).  % this is where the result gets returned

sum_a(N,A,R) :-
        N > 0,
        A1 is N+A,
        N1 is N-1,
        sum_a(N1,A1,R).

sum2(N,S) :- sum_a(N,0,S).


% sum of inverse squares 1+1/4+1/9+...

sum_sq_a(0,R,R).

sum_sq_a(N,A,R) :-
        N > 0,
        N1 is N-1,
        A1 is A+1/(N*N),
        sum_sq_a(N1,A1,R).
                 
sum_sq(N,S) :- sum_sq_a(N,0,S).

                   
% pi^2/6

pisq6(P) :- P is (4*atan(1))*(4*atan(1))/6.

% product of list of numbers

prod([],1).
prod([X|Xs],P) :- number(X),prod(Xs,PXs),P is X*PXs.

% with accumulator

prod([],P,P). % how result returned

prod([X|Xs],A,P) :-
        A1 is X*A,
        prod(Xs,A1,P).

prod_a(L,P) :- prod(L,1,P).