set title "Cities - Disjuntive Complex Queries D= 1.810000  page=2048"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	22.074000
0.002000	23.454000
0.005000	26.506000
0.010000	29.872000
0.020000	34.504000
0.050000	45.292000
0.100000	58.182000
end
####################
0.001000	26.354000
0.002000	27.650000
0.005000	30.366000
0.010000	33.742000
0.020000	38.168000
0.050000	48.770000
0.100000	61.712000
end
####################

pause -1