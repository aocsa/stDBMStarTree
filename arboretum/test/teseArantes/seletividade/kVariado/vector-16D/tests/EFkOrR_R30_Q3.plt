set title "Vector16D - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	0.494000	0.000000	1.351925
0.002000	0.500000	0.000000	1.366025
0.005000	0.538000	0.000000	1.522603
0.010000	1.390000	0.000000	5.209437
0.020000	43.164000	0.000000	127.390095
0.050000	1621.398000	0.000000	3717.884576
0.100000	5338.716000	0.000000	11398.044544
end
####################
0.001000	1.000000	0.700000	1.300000
0.002000	1.000000	0.700000	1.300000
0.005000	1.022000	0.715400	1.328600
0.010000	1.610000	1.127000	2.093000
0.020000	39.172000	27.420400	50.923600
0.050000	1472.422000	1030.695400	1914.148600
0.100000	4841.402000	3388.981400	6293.822600
end
####################

pause -1