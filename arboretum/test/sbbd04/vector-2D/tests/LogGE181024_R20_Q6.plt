set title "Statistics for Queries LogGE181024_R20_Q6"
set xlabel "k"
set logscale x
set ylabel "# of Queries"
plot '-' title '(A) Zero Ring Call' with linespoints 1, '-' title '(B) One Ring Call' with linespoints 2, '-' title '(C) Two Ring Call' with linespoints 3, '-' title '(D) Three Ring Call' with linespoints 4

0.001000	16667
0.002000	16667
0.005000	16667
0.010000	16667
0.020000	16667
0.050000	16667
end
0.001000	3333
0.002000	3333
0.005000	3333
0.010000	3333
0.020000	3333
0.050000	3333
end
0.001000	13
0.002000	0
0.005000	0
0.010000	0
0.020000	0
0.050000	2956
end
0.001000	0
0.002000	0
0.005000	0
0.010000	0
0.020000	0
0.050000	613
end


pause -1