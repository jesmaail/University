%Joseph Esmaail - 713992
%Christopher Lacey - 
%Patrick Schlumberger-Socha - 

%[Total:57 marks]

%Question 1(a) - [5 marks]

%Program: ROYAL
parent(queenmother, elisabeth).
parent(elisabeth, charles).
parent(elisabeth, andrew).
parent(elisabeth, anne).
parent(elisabeth, edward).
parent(diana, william).
parent(diana, harry).
parent(sarah, beatrice).
parent(anne, peter).
parent(anne, zara).
parent(george, elisabeth).
parent(philip, charles).
parent(philip, andrew).
parent(philip, edward).
parent(charles, william).
parent(charles, harry).
parent(andrew, beatrice).
parent(andrew, eugene).
parent(mark, peter).
parent(mark, zara).
parent(william, georgejun).
parent(kate, georgejun).

%1
the_royal_females(X) :- member(X, [queenmother, elisabeth, anne, diana, sarah, beatrice, zara, kate]).
%2
the_royal_males(X) :- member(X, [charles, andrew, edward, william, harry, peter, george, philip, eugene, mark, georgejun]).
%3
the_royal_family(X) :- 
				the_royal_males(X);
				the_royal_females(X).

%4
mother(X,Y) :- 
			parent(X,Y),
			the_royal_females(X).

%5
has_child(X) :- parent(X,_).

%6
ancestor(X,Y) :- parent(X,Y).
ancestor(X,Y) :- 
				parent(X,Z),
				ancestor(Z,Y).

%7
descendant(X,Y) :- ancestor(Y,X).

%--Translate the following into queries--
%8 Who is the Mother of Beatrice?
	%mother(A, beatrice).
	%A = sarah.

%9 Who has a child (one or more)?
	%has_child(A).
	%A = queenmother;
	%A = elisabeth;
	%A = diana;
	%A = sarah;
	%A = anne;
	%A = george;
	%A = philip;
	%A = charles;
	%A = andrew;
	%A = mark;
	%A = william;
	%A = kate.
	%^note:duplicates ommitted.

%10 Who is a descendant of the Queenmother?
	%descendant(A, queenmother).
	%A = elisabeth;
	%A = charles;
	%A = andrew;
	%A = anne;
	%A = edward;
	%A = william;
	%A = harry;
	%A = georgejun;
	%A = beatrice;
	%A = eugene;
	%A = peter;
	%A = zara.


%------------------------------------------------------------
%Question 1(b) - [5 marks]
%Use predicates of Q1a to define predicates sibling/2 and aunt/2
%Query: Who are the siblings of charles?

sibling(X,Y) :- 
			parent(A,X),
			parent(A,Y).

aunt(X,Y) :- 
			parent(Z,Y),
			sibling(X,Z),
			the_royal_females(X).

%------------------------------------------------------------
%Question 1(c) - [5 marks]
%may have to do it the way she requests though? Double Check!
palindrome_list(L) :- reverse(L,L).

%------------------------------------------------------------
%Question 1(d) - [5 marks]
% i- Recursive predicate
%% euclidsq([], [], 0).
%% euclidq(X, Y, ED).


% ii- A tail recursive predicate
%% equclidsqr_acc(X,Y,A,ED)

%------------------------------------------------------------
%---- QUESTION 2 ----
%------------------------------------------------------------
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