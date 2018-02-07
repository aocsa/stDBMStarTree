set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	0.680000	0.000000	1.704539
0.002000	0.748000	0.000000	1.928895
0.005000	1.472000	0.000000	5.185610
0.010000	4.132000	0.000000	17.081975
0.020000	18.056000	0.000000	79.743921
0.050000	120.418000	0.000000	401.432441
0.100000	572.018000	0.000000	1292.196938
end
####################
0.001000	0.644000	0.450800	0.837200
0.002000	0.668000	0.467600	0.868400
0.005000	0.722000	0.505400	0.938600
0.010000	0.784000	0.548800	1.019200
0.020000	2.508000	1.755600	3.260400
0.050000	16.856000	11.799200	21.912800
0.100000	65.690000	45.983000	85.397000
end
####################

pause -1