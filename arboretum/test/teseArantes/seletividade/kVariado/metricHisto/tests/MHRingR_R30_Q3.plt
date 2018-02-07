set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	0.000000	0.000000	0.126491
0.002000	0.000000	0.000000	0.303315
0.005000	0.000000	0.000000	1.596246
0.010000	1.000000	0.000000	7.044998
0.020000	7.000000	0.000000	35.789755
0.050000	55.000000	0.000000	160.981027
0.100000	278.000000	0.000000	650.501144
end
####################
0.001000	0.000000	0.000000	0.000000
0.002000	0.000000	0.000000	0.000000
0.005000	0.000000	0.000000	0.000000
0.010000	0.332000	0.232400	0.431600
0.020000	1.332000	0.932400	1.731600
0.050000	6.332000	4.432400	8.231600
0.100000	22.996000	16.097200	29.894800
end
####################

pause -1