:- use_module([library(random),library(system)]).
% use for generating random list of birthdays

% see prob >0.5 if at least 23 people selected


% generate a random list of N integers in the range 1 to 365 i.e.a birthday
gen_random_bday_lst(0,[]).

gen_random_bday_lst(N,[R|L]) :-
        N > 0,
        random(1,366,R),
        N1 is N-1,
        gen_random_bday_lst(N1,L).

% test to see if duplicate number in a list

duplicate_in_list([X|Xs]) :-
        member(X,Xs),!.

duplicate_in_list([_|Xs]) :-
        duplicate_in_list(Xs).

% perform N tests and see how many produce a list with duplicates
% for lists of size M

test(0,_,0). % out case

test(N,M,X) :-
        N>0,N1 is N-1,
        test(N1,M,X1),
        gen_random_bday_lst(M,L),
        (duplicate_in_list(L) -> X is X1+1;
                                 X = X1).

        
% Get the estimated probability of two birthdays in N trials for lists of length M
        
trials(N,M,P) :-
                now(Seed),
                setrand(Seed),
                test(N,M,X),
                P is X/N.
