set title "Vector2D - Disjuntive Complex Queries D= 1.830000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	101.194000
0.002000	106.688000
0.005000	119.648000
0.010000	135.694000
0.020000	160.760000
0.050000	219.800000
end
####################
0.001000	112.498000
0.002000	116.354000
0.005000	125.228000
0.010000	136.256000
0.020000	155.454000
0.050000	201.536000
end
####################

pause -1