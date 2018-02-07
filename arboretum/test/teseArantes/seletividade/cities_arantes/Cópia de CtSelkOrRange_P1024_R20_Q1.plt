set title "Cidades Brasileiras - Estimativa de Seletividade  page=1024"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y
plot '-' title '(A) Cardinalidade usando Seletividade XX' with linespoints 1, '-' title '(B) Cardinalidade Real' with linespoints 2, '-' title '(C) Erro Acima' with linespoints 3, '-' title '(D) Erro Abaixo' with linespoints 4

####################
25	78.823130
81	146.808115
137	200.198383
193	252.346377
249	305.392402
305	357.794735
361	409.778351
417	461.422566
473	513.067326
529	565.589528
end
####################
25	35.244000
81	117.460000
137	195.560000
193	271.202000
249	355.494000
305	445.420000
361	528.830000
417	605.632000
473	682.752000
529	758.404000
end
####################
25	102.470068
81	190.850550
137	260.257898
193	328.050290
249	397.010123
305	465.133156
361	532.711856
417	599.849336
473	666.987524
529	735.266387
end
####################
25	55.176191
81	102.765681
137	140.138868
193	176.642464
249	213.774682
305	250.456315
361	286.844846
417	322.995796
473	359.147128
529	395.912670
end
####################

pause -1