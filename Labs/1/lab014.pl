killer(butch).
married(mia, marcellus).
dead(zed).
butchKills(X) :- givesFootMassage(X, mia).
loves(mia, X) :- goodDancer(X).
julesEats(X) :- nutritious(X); tasty(X).

givesFootMassage(vincent, mia).
givesFootMassage(butch, marcellus).
tasty(burger).
nutritious(bacon).
goodDancer(vincent).