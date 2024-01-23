% definition of negation as failure using fail

neg(G) :- G,!,fail.
neg(_).

man(joe).
man(bill).
% man(robin).

woman(jill).

person(jenny).
person(gill).
person(robin).
person(jill).

female(X) :- woman(X).

% default rule for female

female(F) :- person(F),
             \+ man(F).

% gen odd number between L and U L =< U L odd

gen_odd(L,U,L) :- L =< U.

gen_odd(L,U,X) :-
        L1 is L+2,
        L1 =< U,
        gen_odd(L1,U,X).

        
% composite number - i.e. N has divisor other than 1 and N

% gen odd number up to U , U >= 3

gen_odd_num_upto(U,X):-
       gen_odd(3,U,X).



% M divides N exactly

divides(M,N) :-
        N mod M =:= 0.

composite(N) :-
        N > 2, N1 is N-1,
        gen_odd_num_upto(N1,M),
        divides(M,N).

composite2(N) :-
        U is floor(sqrt(N)),
        gen_odd_num_upto(U,M),
        divides(M,N).

% prime if not composite

prime(P) :- \+ composite(P).

% prime if not composite

prime2(P) :- \+ composite2(P).

% check Mersenne prime 2^13-1        
