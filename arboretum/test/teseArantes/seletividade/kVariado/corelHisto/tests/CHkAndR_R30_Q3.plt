set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	1.218000	0.000000	17.571857
0.002000	2.564000	0.000000	31.840848
0.005000	13.818000	0.000000	88.094950
0.010000	194.498000	0.000000	520.270099
end
####################
0.001000	0.362000	0.253400	0.470600
0.002000	0.394000	0.275800	0.512200
0.005000	0.716000	0.501200	0.930800
0.010000	3.926000	2.748200	5.103800
end
####################

pause -1