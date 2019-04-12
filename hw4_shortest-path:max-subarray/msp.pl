max(X,Y,X):- X>Y,!.
max(X,Y,Y):- Y>=X.
assign(L,Z,Z):- L==[].
assign(L,Z,X):- L\=[],X=Z.
recur_maxsum([],X,Y,Unk):- Unk = Y.
recur_maxsum(L, Max_ending_here, M, Unk2):-
	L = [Head|Tail],
	max(Head, Head+Max_ending_here,P),
	%Head > Max_ending_here+Head -> Max_ending_here is Head;
	%Max_ending_here+Head > Head -> Max_ending_here is Max_ending_here+Head;
	max(M, P ,Z),
	%M > Max_ending_here -> M is M;
	%Max_ending_here > M -> M is Max_ending_here;
	recur_maxsum(Tail, P, Z, Unk1),
	assign(Tail, Unk1, Unk2).

maxsum(L, M):-
	L = [Head|Tail],
	%Max_ending_here = Head,
	max(0,Head,Max_ending_here),
	%M1 = Head,
	max(0,Head,M1),
	recur_maxsum(Tail, Max_ending_here, M1, Unk3),
	M = Unk3.
	

