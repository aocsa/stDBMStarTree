set title "Cidades Brasileiras - Estimativa de Seletividade  page=1024"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y 
plot '-' title '(A) Cardinalidade usando Seletividade XX' with linespoints 1, '-' title '(B) Cardinalidade Real' with linespoints 2, '-' title '(C) Erro Acima' with linespoints 3, '-' title '(D) Erro Abaixo' with linespoints 4

####################
25	67.085209
81	129.792629
137	184.004000
193	237.466305
249	290.826345
305	343.404032
361	395.878085
417	448.094318
473	500.342633
529	553.417607
end
####################
25	30.582000
81	99.510000
137	165.910000
193	233.418000
249	305.714000
305	379.348000
361	448.182000
417	515.156000
473	582.360000
529	649.196000
end
####################
25	87.210771
81	168.730418
137	239.205200
193	308.706197
249	378.074248
305	446.425242
361	514.641510
417	582.522613
473	650.445423
529	719.442889
end
####################
25	46.959646
81	90.854840
137	128.802800
193	166.226414
249	203.578441
305	240.382823
361	277.114659
417	313.666022
473	350.239843
529	387.392325
end
####################

pause -1