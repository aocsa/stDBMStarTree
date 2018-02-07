set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
1	2.560000	0.000000	9.422390
2	33.085000	0.000000	144.046107
3	278.340000	0.000000	1091.012926
4	1332.725000	0.000000	4313.632686
end
####################
1	584.000000	408.800000	759.200000
2	2032.000000	1422.400000	2641.600000
3	4216.000000	2951.200000	5480.800000
4	7077.000000	4953.900000	9200.100000
end
####################

pause -1