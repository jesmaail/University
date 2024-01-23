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
the_royal_family(X) :- 			%A royal family member will be part of the list of either males or females.
		the_royal_males(X);		
		the_royal_females(X).

%4
mother(X,Y) :- 					%A mother is defined as a parent who is a female.
		parent(X,Y),
		the_royal_females(X).

%5
has_child(X) :- parent(X,_).	%A member has a child if they are a parent.

%6
ancestor(X,Y) :- parent(X,Y).	%Ancestor is either a parent, or a parent of a parent, etc.
ancestor(X,Y) :- 
		parent(X,Z),
		ancestor(Z,Y).

%7
descendant(X,Y) :- ancestor(Y,X).	%A descendant works the opposite way to an ancestor.

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

% -- sibling/2 --
sibling(X,Y) :- 		%Two members are siblings so long as they have a common parent.
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

% -- aunt/2 --
aunt(X,Y) :- 			%One member is the aunt of another if they are the sibling of the parent and also female.
		parent(Z,Y),
		sibling(X,Z),
		the_royal_females(X).

%------------------------------------------------------------
%Question 1(c)
%-------------
%Calling the reverse method will work,
%but it does not meet the requirements set out in the coursework :)

%palindrome_list(L) :- reverse(L,L).

palindrome_list([]).		%base case when empty
palindrome_list([_]).		%base case when singleton
palindrome_list([X|Xs]) :- 
		last_element([X], A, Xs),
		palindrome_list(A).

last_element(L,X,R) :- append(X,L,R).

%------------------------------------------------------------
%Question 1(d)
%-------------
% i- Recursive predicate
euclidsqr([],[],0).
euclidsqr([X|Xs],[Y|Ys],ED) :-
		euclidsqr(Xs,Ys,ED1),
		ED is ED1+(X-Y)*(X-Y).

% ii- A tail recursive predicate
euclidsqr_acc([],[],0,0).
euclidsqr_acc([X|Xs],[Y|Ys],A,ED) :-
		euclidsqr_acc(Xs,Ys,A1,ED1),	
		A is A1+(X-Y)*(X-Y),		%Stores intermediate calculations
		ED is ED1+1.				%Count for length of the lists
		