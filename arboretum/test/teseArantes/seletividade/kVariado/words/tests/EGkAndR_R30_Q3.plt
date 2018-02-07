set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
1	2.030000	0.000000	7.466938
2	26.600000	0.000000	115.234299
3	225.215000	0.000000	882.917363
4	1084.105000	0.000000	3508.391039
end
####################
1	2.160000	1.512000	2.808000
2	29.205000	20.443500	37.966500
3	247.840000	173.488000	322.192000
4	1197.930000	838.551000	1557.309000
end
####################

pause -1