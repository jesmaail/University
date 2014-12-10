%Joseph Esmaail - 713992
%Christopher Lacey - 709297
%Patrick Schlumberger-Socha - 786153

%------------------------------------
% ---- Question 2 ----
%------------------------------------

%Question 2(a)
%-------------
%% member_rem(X,[X|Xs],Xs).
%% member_rem(Y,[X|Xs],[X|R]) :- member_rem(Y,Xs,R).
member_rem(E,L,R) :- select(E,L,R).

%------------------------------------------------------------
%Question 2(b)
%-------------
gen_list_n(0,_,[]).
gen_list_n(N,D,[X|Xs]) :-
		N > 0,
		N1 is N-1,
		member_rem(X,D,R),
		gen_list_n(N1,R,Xs).

gen4(L) :- gen_list_n(4,[1,2,3,4],L).

%------------------------------------------------------------
%Question 2(c)
%-------------
distinct_in_entries([],[]).				%stops when lists are empty.
distinct_in_entries([X|Xs], [Y|Ys]) :- 
		X =\= Y,						%Checks that the heads of the list is the same.
		distinct_in_entries(Xs,Ys).		%Recurses through with the tail.

%------------------------------------------------------------
%Question 2(d)
%-------------
gen_poss_sln([R1,R2,R3,R4]) :-
		gen4(R1),						%Generate the Lists.
		gen4(R2),
		gen4(R3),
		gen4(R4),
		distinct_in_entries(R1,R2),		%Ensure they are distinct by comparing to each other.
		distinct_in_entries(R1,R3),
		distinct_in_entries(R1,R4),
		distinct_in_entries(R2,R3),
		distinct_in_entries(R2,R4),
		distinct_in_entries(R3,R4).

%------------------------------------------------------------
%Question 2(e)
%-------------
solve([R1,R2,R3,R4]) :-
		gen_poss_sln([R1,R2,R3,R4]),	%Generate a possible solution with distinct.
		R1 = [R11,R12,_,_],				%Define elements that have constraints.
		R2 = [R21,R22,_,R24],
		R3 = [R31,R32,R33,R34],
		R4 = [_,_,R43,R44],
		R11 > R12,						%Define the constaints on the elements defined above.
		R21 < R22,
		R24 > R34,
		R31 > R32,
		R33 < R34,
		R43 < R44.

%% 	solve([R1,R2,R3,R4]).
%% 	R1 = [3, 2, 4, 1],
%% 	R2 = [1, 4, 2, 3],
%% 	R3 = [4, 3, 1, 2],
%% 	R4 = [2, 1, 3, 4];

%------------------------------------------------------------
%Question 2(f)
%-------------
solve_in_steps([R1,R2,R3,R4]) :-		%Same Solution as above however does each row one by one.
		gen4(R1),
		R1 = [R11,R12,_,_],
		R11 > R12,

		gen4(R2),
		distinct_in_entries(R1,R2),
		R2 = [R21,R22,_,R24],
		R21 < R22,

		gen4(R3),						%R24 constraint is defined here as it relies on an element in Row 3.
		distinct_in_entries(R1,R3),
		distinct_in_entries(R2,R3),
		R3 = [R31,R32,R33,R34],
		R24 > R34,
		R31 > R32,
		R33 < R34,

		gen4(R4),
		distinct_in_entries(R1,R4),
		distinct_in_entries(R2,R4),
		distinct_in_entries(R3,R4),
		R4 = [_,_,R43,R44],
		R43 < R44.