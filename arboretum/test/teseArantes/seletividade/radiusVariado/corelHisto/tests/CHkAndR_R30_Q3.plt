set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	47.330000	0.000000	95.092354
0.002000	95.984000	0.000000	192.991293
0.005000	242.134000	0.000000	487.020555
0.010000	489.650000	0.000000	986.695354
end
####################
0.001000	4.102000	2.871400	5.332600
0.002000	5.058000	3.540600	6.575400
0.005000	6.866000	4.806200	8.925800
0.010000	8.936000	6.255200	11.616800
end
####################

pause -1