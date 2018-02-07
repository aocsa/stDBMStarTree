set title "corelHisto - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	141.910000	0.000000	391.537725
0.002000	265.206000	0.000000	702.631977
0.005000	615.718000	0.000000	1662.406247
0.010000	1211.248000	0.000000	4031.041393
end
####################
0.001000	1.896000	1.327200	2.464800
0.002000	2.340000	1.638000	3.042000
0.005000	3.228000	2.259600	4.196400
0.010000	4.228000	2.959600	5.496400
end
####################

pause -1