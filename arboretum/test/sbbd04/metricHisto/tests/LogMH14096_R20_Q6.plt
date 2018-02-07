set title "Statistics for Queries LogMH14096_R20_Q6"
set xlabel "k"
set logscale x
set ylabel "# of Queries"
plot '-' title '(A) Zero Ring Call' with linespoints 1, '-' title '(B) One Ring Call' with linespoints 2, '-' title '(C) Two Ring Call' with linespoints 3, '-' title '(D) Three Ring Call' with linespoints 4

0.001000	392
0.002000	390
0.005000	369
0.010000	329
0.020000	313
0.050000	252
0.100000	219
end
0.001000	108
0.002000	110
0.005000	131
0.010000	171
0.020000	187
0.050000	248
0.100000	281
end
0.001000	4
0.002000	6
0.005000	4
0.010000	2
0.020000	2
0.050000	0
0.100000	0
end
0.001000	0
0.002000	2
0.005000	0
0.010000	0
0.020000	0
0.050000	0
0.100000	0
end


pause -1