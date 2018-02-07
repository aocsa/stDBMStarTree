set title "Vector6D - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	75.592000	0.000000	152.557398
0.002000	152.078000	0.000000	306.101522
0.005000	375.566000	0.000000	754.497924
0.010000	744.076000	0.000000	1495.712460
0.020000	1472.820000	0.000000	2959.786400
0.050000	3580.032000	0.000000	7194.018955
end
####################
0.001000	49.000000	34.300000	63.700000
0.002000	99.000000	69.300000	128.700000
0.005000	248.000000	173.600000	322.400000
0.010000	497.000000	347.900000	646.100000
0.020000	995.000000	696.500000	1293.500000
0.050000	2487.000000	1740.900000	3233.100000
end
####################

pause -1