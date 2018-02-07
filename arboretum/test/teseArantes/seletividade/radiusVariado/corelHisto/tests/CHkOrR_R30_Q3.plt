set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	177.106000	0.000000	443.881803
0.002000	336.464000	0.000000	812.511711
0.005000	797.338000	0.000000	1942.383035
0.010000	1582.208000	0.000000	4553.408906
end
####################
0.001000	67.000000	46.900000	87.100000
0.002000	135.000000	94.500000	175.500000
0.005000	338.000000	236.600000	439.400000
0.010000	677.000000	473.900000	880.100000
end
####################

pause -1