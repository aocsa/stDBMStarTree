set title "Vector2D - Disjuntive Complex Queries D= 4.670000  page=4096"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	2314
0.002000	2513
0.005000	2914
0.010000	3425
0.020000	4416
0.050000	8802
0.100000	21160
end
####################
0.001000	2253
0.002000	2414
0.005000	2694
0.010000	3034
0.020000	3676
0.050000	6139
0.100000	12378
end
####################

pause -1