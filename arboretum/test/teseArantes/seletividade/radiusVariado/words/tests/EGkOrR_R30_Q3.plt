set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
1	1.945000	0.000000	7.014924
2	6.330000	0.000000	22.710241
3	10.080000	0.000000	37.581793
4	13.435000	0.000000	48.069172
end
####################
1	723.440000	506.408000	940.472000
2	1987.060000	1390.942000	2583.178000
3	2501.890000	1751.323000	3252.457000
4	2900.245000	2030.171500	3770.318500
end
####################

pause -1