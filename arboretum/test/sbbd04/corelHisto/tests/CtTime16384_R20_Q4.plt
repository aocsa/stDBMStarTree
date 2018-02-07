set title "Vector2D - Disjuntive Complex Queries D= 0.682200  page=16384"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	72524
0.002000	78173
0.005000	91021
0.010000	118069
0.020000	235419
0.050000	889499
end
####################
0.001000	76801
0.002000	82488
0.005000	92963
0.010000	114325
0.020000	211274
0.050000	714518
end
####################

pause -1