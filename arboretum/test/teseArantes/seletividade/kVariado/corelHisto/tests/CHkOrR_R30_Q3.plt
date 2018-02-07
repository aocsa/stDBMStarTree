set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	1.534000	0.000000	20.424236
0.002000	3.298000	0.000000	40.473390
0.005000	16.772000	0.000000	105.832613
0.010000	238.118000	0.000000	635.074806
end
####################
0.001000	1.954000	1.367800	2.540200
0.002000	3.356000	2.349200	4.362800
0.005000	15.220000	10.654000	19.786000
0.010000	214.312000	150.018400	278.605600
end
####################

pause -1