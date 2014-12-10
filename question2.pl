%Joseph Esmaail - 713992
%Christopher Lacey - 
%Patrick Schlumberger-Socha - 

%------------------------------------
% ---- Question 2 ----
%------------------------------------

%Question 2(a) - [4 marks]
%% member_rem(X,[X|Xs],Xs).
%% member_rem(Y,[X|Xs],[X|R]) :- member_rem(Y,Xs,R).
member_rem(E,L,R) :-
    select(E, L, R).

%------------------------------------------------------------
%Question 2(b) - [4 marks]
%gen_list_n(N,D,L),
%which generates a list(L) of N distinct elements,
%from the List D, where length of D is >= N

gen_list_n(0,[], _).
gen_list_n(N,[X|Xs],L) :-
		N > 0,				
		N1 is N-1,
		member_rem(X,L,R),		%Remove X from list and store in R
		\+(member(R, L)),			%if member(R, L) is false
		gen_list_n(N1, Xs, R).		%Recursively call back

gen_n(0,_,[]).
gen_n(N,D,[X|Xs]) :-
		N >0,
		N1 is N-1,
		member_rem(X,D,D1),
		gen_n(N1,D1,Xs).

%All above is probably wrong - majorlymindfucked.

%------------------------------------------------------------
%Question 2(c) - [4 marks]