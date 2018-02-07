set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set xrange [0.001:0.1]
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	0.492000	0.000000	4.763077
0.002000	0.528000	0.000000	5.497373
0.005000	0.758000	0.000000	9.861929
0.010000	1.130000	0.000000	16.198589
0.020000	2.154000	0.000000	27.294428
0.050000	9.852000	0.000000	73.348985
0.100000	106.078000	0.000000	309.482863
end
####################
0.001000	0.348000	0.243600	0.452400
0.002000	0.348000	0.243600	0.452400
0.005000	0.350000	0.245000	0.455000
0.010000	0.394000	0.275800	0.512200
0.020000	0.680000	0.476000	0.884000
0.050000	6.208000	4.345600	8.070400
0.100000	100.282000	70.197400	130.366600
end
####################

pause -1