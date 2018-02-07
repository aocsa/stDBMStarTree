set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
1	0.840000	0.000000	1.773916
2	1.555000	0.000000	3.166498
3	2.315000	0.000000	4.722234
4	3.050000	0.000000	6.206026
end
####################
1	1.000000	0.700000	1.300000
2	1.885000	1.319500	2.450500
3	2.830000	1.981000	3.679000
4	3.760000	2.632000	4.888000
end
####################

pause -1