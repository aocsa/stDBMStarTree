set title "Cidades Brasileiras - Estimativa de Seletividade  page=1024"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y
plot '-' title '(A) Cardinalidade usando Seletividade XX' with linespoints 1, '-' title '(B) Cardinalidade Real' with linespoints 2, '-' title '(C) Erro Acima' with linespoints 3, '-' title '(D) Erro Abaixo' with linespoints 4

####################
25	24.763586
81	77.740769
137	116.049249
193	147.884889
249	175.939000
end
####################
25	25.000000
81	81.000000
137	137.000000
193	193.000000
249	249.000000
end
####################
25	29.716303
81	93.288923
137	139.259099
193	177.461866
249	211.126800
end
####################
25	19.810869
81	62.192615
137	92.839399
193	118.307911
249	140.751200
end
####################

pause -1