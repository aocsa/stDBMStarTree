set title "Cidades Brasileiras - Estimativa de Seletividade  page=1024"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y 
plot '-' title '(A) Cardinalidade usando Seletividade XX' with linespoints 1, '-' title '(B) Cardinalidade Real' with linespoints 2, '-' title '(C) Erro Acima' with linespoints 3, '-' title '(D) Erro Abaixo' with linespoints 4

####################
25	24.645072
81	76.433419
137	114.406239
193	146.431767
249	174.835847
305	199.886923
361	221.784992
417	241.847652
473	261.064769
529	279.122769
end
####################
25	22.374000
81	71.090000
137	120.510000
193	170.562000
249	221.480000
305	271.716000
361	320.854000
417	369.790000
473	419.246000
529	469.952000
end
####################
25	32.038593
81	99.363444
137	148.728111
193	190.361297
249	227.286601
305	259.853000
361	288.320490
417	314.401948
473	339.384200
529	362.859599
end
####################
25	17.251550
81	53.503393
137	80.084367
193	102.502237
249	122.385093
305	139.920846
361	155.249494
417	169.293357
473	182.745339
529	195.385938
end
####################

pause -1