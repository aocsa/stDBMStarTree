set title "Cidades Brasileiras - Estimativa de Seletividade  page=1024"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y
plot '-' title '(A) Cardinalidade usando Seletividade XX' with linespoints 1, '-' title '(B) Cardinalidade Real' with linespoints 2, '-' title '(C) Erro Acima' with linespoints 3, '-' title '(D) Erro Abaixo' with linespoints 4

####################
25	24.904059
81	80.286209
137	125.273718
193	163.812289
249	197.365008
305	227.024312
361	252.905367
417	276.566723
473	299.340209
529	320.770327
end
####################
25	25.000000
81	81.000000
137	137.000000
193	193.000000
249	249.000000
305	305.000000
361	361.000000
417	417.000000
473	473.000000
529	529.000000
end
####################
25	32.375277
81	104.372072
137	162.855833
193	212.955976
249	256.574511
305	295.131605
361	328.776977
417	359.536740
473	389.142271
529	417.001426
end
####################
25	17.432841
81	56.200346
137	87.691603
193	114.668602
249	138.155506
305	158.917018
361	177.033757
417	193.596706
473	209.538146
529	224.539229
end
####################

pause -1