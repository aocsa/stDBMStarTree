set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
1	0.000000	0.000000	2.501999
2	8.000000	0.000000	53.595669
3	81.000000	0.000000	428.341906
4	1174.000000	0.000000	3588.174556
end
####################
1	201.250000	140.875000	261.625000
2	700.710000	490.497000	910.923000
3	1454.060000	1017.842000	1890.278000
4	2441.320000	1708.924000	3173.716000
end
####################

pause -1