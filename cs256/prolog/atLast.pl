atLast(X,[X]).
atLast(X,[_|L]) :- atLast(X,L).