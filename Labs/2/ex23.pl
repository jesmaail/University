word(determiner, a).
word(determiner, every).
word(noun, criminal).
word(noun, 'big_kahuna_burger').
word(verb, eats).
word(verb, likes).

sentence(Word1, Word2, Word3, Word4, Word5) :-
	word(determiner, Word1),
	word(noun, Word2),
	word(verb, Word3),
	word(determiner, Word4),
	word(noun, Word5).

%sentence(a, criminal, eats, every, 'big_kahuna_burger').
%sentence(every, criminal, eats, a, 'big_kahuna_burger').

%sentence(A,B,C,D,E).