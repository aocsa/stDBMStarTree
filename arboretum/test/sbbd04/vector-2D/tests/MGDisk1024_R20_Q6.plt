set title "Vector2D - Disjuntive Complex Queries D= 1.820000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	202.228000
0.002000	214.786000
0.005000	240.410000
0.010000	270.908000
0.020000	315.982000
0.050000	412.120000
end
####################
0.001000	222.954000
0.002000	231.998000
0.005000	251.250000
0.010000	274.582000
0.020000	310.564000
0.050000	391.212000
end
####################

pause -1