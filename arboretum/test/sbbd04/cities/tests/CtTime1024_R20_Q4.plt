set title "Cities - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	290
0.002000	351
0.005000	501
0.010000	691
0.020000	1052
0.050000	2273
0.100000	5007
end
####################
0.001000	321
0.002000	340
0.005000	431
0.010000	551
0.020000	751
0.050000	1342
0.100000	2724
end
####################

pause -1