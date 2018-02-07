set title "Statistics for Queries LogEF4096_R20_Q4"
set xlabel "k"
set logscale x
set ylabel "# of Queries"
plot '-' title '(A) Zero Ring Call' with linespoints 1, '-' title '(B) One Ring Call' with linespoints 2, '-' title '(C) Two Ring Call' with linespoints 3, '-' title '(D) Three Ring Call' with linespoints 4

0.001000	375
0.002000	375
0.005000	375
0.010000	375
0.020000	375
0.050000	375
0.100000	375
end
0.001000	125
0.002000	125
0.005000	125
0.010000	125
0.020000	125
0.050000	125
0.100000	125
end
0.001000	1
0.002000	0
0.005000	0
0.010000	0
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