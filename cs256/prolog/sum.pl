sum([], 0]).
sum([H|T], N) :- sum(T, M), N is H + M.