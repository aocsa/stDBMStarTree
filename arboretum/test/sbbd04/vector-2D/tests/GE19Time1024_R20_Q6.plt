set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	6687
0.002000	8218
0.005000	12860
0.010000	22687
0.020000	49688
0.050000	228453
end
####################
0.001000	5641
0.002000	6360
0.005000	8359
0.010000	12360
0.020000	23437
0.050000	88203
end
####################

pause -1