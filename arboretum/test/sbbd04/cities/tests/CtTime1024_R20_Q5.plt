set title "Cities - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	290
0.002000	341
0.005000	491
0.010000	681
0.020000	1041
0.050000	2254
0.100000	4958
end
####################
0.001000	301
0.002000	340
0.005000	421
0.010000	530
0.020000	721
0.050000	1281
0.100000	2573
end
####################

pause -1