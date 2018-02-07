set title "Statistics for Queries LogCt2048_R20_Q5"
set xlabel "k"
set logscale x
set ylabel "# of Queries"
plot '-' title '(A) Zero Ring Call' with linespoints 1, '-' title '(B) One Ring Call' with linespoints 2, '-' title '(C) Two Ring Call' with linespoints 3, '-' title '(D) Three Ring Call' with linespoints 4

0.001000	400
0.002000	400
0.005000	400
0.010000	400
0.020000	400
0.050000	400
0.100000	400
end
0.001000	100
0.002000	100
0.005000	100
0.010000	100
0.020000	100
0.050000	100
0.100000	100
end
0.001000	0
0.002000	6
0.005000	1
0.010000	1
0.020000	0
0.050000	0
0.100000	0
end
0.001000	0
0.002000	0
0.005000	0
0.010000	0
0.020000	0
0.050000	0
0.100000	0
end


pause -1