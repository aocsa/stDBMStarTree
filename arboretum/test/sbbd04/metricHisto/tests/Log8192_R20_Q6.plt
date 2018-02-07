set title "Statistics for Queries Log8192_R20_Q6"
set xlabel "k"
set logscale x
set ylabel "# of Queries"
plot '-' title '(A) Zero Ring Call' with linespoints 1, '-' title '(B) One Ring Call' with linespoints 2, '-' title '(C) Two Ring Call' with linespoints 3, '-' title '(D) Three Ring Call' with linespoints 4

0.000100	389
0.000200	389
0.000500	398
0.001000	390
0.002000	387
0.005000	360
0.010000	349
0.020000	333
0.050000	282
0.100000	272
end
0.000100	111
0.000200	111
0.000500	102
0.001000	110
0.002000	113
0.005000	140
0.010000	151
0.020000	167
0.050000	218
0.100000	228
end
0.000100	111
0.000200	111
0.000500	96
0.001000	1
0.002000	1
0.005000	0
0.010000	0
0.020000	0
0.050000	0
0.100000	0
end
0.000100	32
0.000200	32
0.000500	7
0.001000	0
0.002000	0
0.005000	0
0.010000	0
0.020000	0
0.050000	0
0.100000	0
end


pause -1