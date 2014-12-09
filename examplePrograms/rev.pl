:- use_module(library(random)).

% generate a random list of N integers in the range 1 to 100
gen_random_lst(0,[]).

gen_random_lst(N,[R|L]) :-
        N > 0,
        random(1,101,R),
        N1 is N-1,
        gen_random_lst(N1,L).

% procedures for timing

timer(T) :- statistics(runtime,[T|_]).

% reverse - standard definition and using acc param

reverse([],[]).

reverse([X|Xs],R) :-
        reverse(Xs,RXs),
        append(RXs,[X],R).


% now using acc parameter so tail rewcursive

% the three argument rev  with acc param

% acc returned in R when [] reached

reverse([],R,R).

reverse([X|Xs],A,R) :-
        reverse(Xs,[X|A],R).

% the acc reverse

reverse_acc(X,R) :- reverse(X,[],R).

% time the difference

test_revs(Sz) :-
        gen_random_lst(Sz,L),
        timer(U1),reverse(L,_),timer(V1),
        D1 is V1-U1,format('reverse took ~3d sec.~n',[D1]),   % print with 3dp and a newline
        timer(U2),reverse_acc(L,_),timer(V2),
        D2 is V2-U2,format('reverse_acc took ~3d sec.~n',[D2]).

% sum of elements in list using acc param

sum([],A,A).

sum([X|Xs],A,S) :-
        A1 is X+A,
        sum(Xs,A1,S).

sum_acc(L,S) :- sum(L,0,S).


% product of elements in list using acc param

prod([],A,A).

prod([X|Xs],A,P) :-
        A1 is X*A,
        prod(Xs,A1,P).

prod_acc(L,P) :- prod(L,1,P).  % notice it is 1 here in the acc parameter

% length from scratch

len([],0).

len([_|R],N) :-
        len(R,N1), N is N1+1.


% length using accumulator

len([],A,A). % value returned

len([_|Xs],A,L) :-
        A1 is A+1,
        len(Xs,A1,L).

% top  level call

len_acc(X,L) :- len(X,0,L).


% simple version of sum

sum1([],0).

sum1([X|Xs],S) :-
        number(X),
        sum1(Xs,S1),
        S is S1+X.

% average

average(L,A) :-
        sum1(L,S),
        len(L,N),
        A is S/N.

% standard deviation

sd(L,SD) :-
        average(L,A),
        sumsqr_minus(L,A,SS),
        SqrtSS is sqrt(SS),
        len(L,N),
        SD is SqrtSS/N.

% sum of sqrs of elts - A

sumsqr_minus([],_,0).

sumsqr_minus([X|Xs],A,SSM):-
        sumsqr_minus(Xs,A,SSMXs),
        SSM is (X-A)*(X-A) + SSMXs.

% normal max without accumulator

max([X],X).   % out case - assume don't call with empty list

max([X|Xs],M) :-
              max(Xs,MXs),
              (X > MXs -> M = X;
                          M = MXs).

% with accumulator

max([],R,R).
max([X|Xs],M,R) :-
        (X > M -> max(Xs,X,R);
                   max(Xs,M,R)).

max_acc([X|Xs],M) :-
        max(Xs,X,M).
