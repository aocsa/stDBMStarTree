set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	0.000000	0.000000	1.723949
0.002000	0.000000	0.000000	5.221494
0.005000	8.000000	0.000000	36.718182
0.010000	218.000000	0.000000	646.306850
end
####################
0.001000	0.000000	0.000000	0.000000
0.002000	0.000000	0.000000	0.000000
0.005000	0.332000	0.232400	0.431600
0.010000	1.000000	0.700000	1.300000
end
####################

pause -1