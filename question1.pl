%Joseph Esmaail - 713992
%Christopher Lacey - 709297
%Patrick Schlumberger-Socha - 786153

%------------------------------------
% ---- Question 1 ----
%------------------------------------

%Question 1(a)
%-------------

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
%	descendant(A, queenmother).
%	A = elisabeth;
%	A = charles;
%	A = andrew;
%	A = anne;
%	A = edward;
%	A = william;
%	A = harry;
%	A = georgejun;
%	A = beatrice;
%	A = eugene;
%	A = peter;
%	A = zara.


%------------------------------------------------------------
%Question 1(b)
%-------------

%sibling/2
sibling(X,Y) :- 
		parent(A,X),
		parent(A,Y).
%Query: Who are the siblings of charles?
% 	sibling(charles,X).
% 	X = andrew;
% 	X = anne;
% 	X = edward;
% 	X = charles;
% 	X = andrew;
% 	X = edward.

%aunt/2
aunt(X,Y) :- 
		parent(Z,Y),
		sibling(X,Z),
		the_royal_females(X).

%------------------------------------------------------------
%Question 1(c)
%-------------
%Calling the reverse method will work,
%but it does not meet the requirements set out in the coursework :)

%palindrome_list(L) :- reverse(L,L).

palindrome_list([]).	%base case when empty
palindrome_list([_]).	%base case when singleton
palindrome_list([X|Xs]) :- 
		last_element([X], A, Xs),
		palindrome_list(A).

last_element(L,X,R) :- append(X,L,R).

%------------------------------------------------------------
%Question 1(d)
%-------------
% i- Recursive predicate
%% euclidsq([], [], 0).
%% euclidq(X, Y, ED).


% ii- A tail recursive predicate
%% equclidsqr_acc(X,Y,A,ED)