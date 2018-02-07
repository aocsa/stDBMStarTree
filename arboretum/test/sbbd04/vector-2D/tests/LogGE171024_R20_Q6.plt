set title "Statistics for Queries LogGE171024_R20_Q6"
set xlabel "k"
set logscale x
set ylabel "# of Queries"
plot '-' title '(A) Zero Ring Call' with linespoints 1, '-' title '(B) One Ring Call' with linespoints 2, '-' title '(C) Two Ring Call' with linespoints 3, '-' title '(D) Three Ring Call' with linespoints 4

0.001000	417
0.002000	417
0.005000	417
0.010000	417
0.020000	417
0.050000	417
end
0.001000	83
0.002000	83
0.005000	83
0.010000	83
0.020000	83
0.050000	83
end
0.001000	1
0.002000	0
0.005000	0
0.010000	9
0.020000	1
0.050000	2
end
0.001000	0
0.002000	0
0.005000	0
0.010000	2
0.020000	0
0.050000	0
end


pause -1