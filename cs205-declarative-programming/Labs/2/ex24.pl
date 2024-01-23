word(astante, a,s,t,a,n,t,e).
word(astoria, a,s,t,o,r,i,a).
word(baratto, b,a,r,a,t,t,o).
word(cobalto, c,o,b,a,l,t,o).
word(pistola, p,i,s,t,o,l,a).
word(statale, s,t,a,t,a,l,e).

crossword(V1,V2,V3,H1,H2,H3) :-
    word(V1,_,A,_,B,_,C,_),
    word(V2,_,D,_,E,_,F,_),
    word(V3,_,G,_,H,_,I,_),
    word(H1,_,A,_,D,_,G,_),
    word(H2,_,B,_,E,_,H,_),
    word(H3,_,C,_,F,_,I,_),
    V1 \= H1,
    V2 \= H2,
    V3 \= H3.