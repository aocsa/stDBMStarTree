set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
1	1.270000	0.000000	6.362887
2	5.190000	0.000000	21.121174
3	8.495000	0.000000	35.394386
4	11.395000	0.000000	45.077443
end
####################
1	342.580000	239.806000	445.354000
2	941.460000	659.022000	1223.898000
3	1185.335000	829.734500	1540.935500
4	1374.010000	961.807000	1786.213000
end
####################

pause -1