% code for printing out a term in simple tree format

% print N spaces
spaces(0).
spaces(N) :-
     N>0,
     write(' '),N1 is N-1,
     spaces(N1).

% print the tree 
% don't expand if atomic or func(A) where A atomic
 p_tree(Tm,D) :-
       (atomic(Tm);(Tm =.. [_,A],atomic(A))),!,
       spaces(D),write(Tm).

p_tree(Tm,D) :-
      Tm =.. [F|Args],
      spaces(D),write(F),write('('),nl,
      D1 is D+3,
      p_tree_lst(Args,D1),
      spaces(D),write(')').

% print a list of trees

p_tree_lst([Tm],D) :- !,
      p_tree(Tm,D),nl.

p_tree_lst([Tm|Tms],D) :- !,
      p_tree(Tm,D),write(','),nl,
      p_tree_lst(Tms,D).
