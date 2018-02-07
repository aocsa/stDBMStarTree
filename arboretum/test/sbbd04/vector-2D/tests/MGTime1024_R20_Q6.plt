set title "Vector2D - Disjuntive Complex Queries D= 1.820000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	532
0.002000	656
0.005000	984
0.010000	1625
0.020000	3594
0.050000	14579
end
####################
0.001000	468
0.002000	516
0.005000	641
0.010000	891
0.020000	1547
0.050000	5328
end
####################

pause -1