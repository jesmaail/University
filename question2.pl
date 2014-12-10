%Joseph Esmaail - 713992
%Christopher Lacey - 709297
%Patrick Schlumberger-Socha - 786153

%------------------------------------
% ---- Question 2 ----
%------------------------------------

%Question 2(a) - [4 marks]
%% member_rem(X,[X|Xs],Xs).
%% member_rem(Y,[X|Xs],[X|R]) :- member_rem(Y,Xs,R).
member_rem(E,L,R) :- select(E, L, R).

%------------------------------------------------------------
%Question 2(b) - [4 marks]

gen_list_n(0,_,[]).
gen_list_n(N,D,[X|Xs]) :-
		N >0,
		N1 is N-1,
		member_rem(X,D,R),
		gen_list_n(N1,R,Xs).

gen4(L) :- gen_list_n(4,[1,2,3,4],L).

%------------------------------------------------------------
%Question 2(c) - [4 marks]

distinct_in_entries([],[]).
distinct_in_entries([X|Xs], [Y|Ys]) :- 
		X =\= Y,
		distinct_in_entries(Xs,Ys).

%------------------------------------------------------------
%Question 2(d) - [5 marks]

gen_poss_sln(R1,R2,R3,R4) :-
		gen4(R1),
		gen4(R2),
		gen4(R3),
		gen4(R4),
		distinct_in_entries(R1,R2),
		distinct_in_entries(R1,R3),
		distinct_in_entries(R1,R4),
		distinct_in_entries(R2,R3),
		distinct_in_entries(R2,R4),
		distinct_in_entries(R3,R4).

%------------------------------------------------------------
%Question 2(e) - [5 marks]

solve([R1,R2,R3,R4]) :-
		gen_poss_sln(R1,R2,R3,R4),
		R1=[R11,R12,_,_],
		R2=[R21,R22,_,R24],
		R3=[R31,R32,R33,R34],
		R4=[_,_,R43,R44],
		R11 > R12,
		R21 < R22,
		R24 > R34,
		R31 > R32,
		R33 < R34,
		R43 < R44.