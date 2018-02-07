set title "Cidades Brasileiras - Estimativa de Seletividade  page=1024"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y 
plot '-' title '(A) Cardinalidade usando Seletividade XX' with linespoints 1, '-' title '(B) Cardinalidade Real' with linespoints 2, '-' title '(C) Erro Acima' with linespoints 3, '-' title '(D) Erro Abaixo' with linespoints 4

####################
25	24.510210
81	74.966132
137	112.717713
193	144.588322
249	173.128114
305	198.548254
361	220.537781
417	240.594303
473	260.009064
529	278.100133
end
####################
25	21.438000
81	67.524000
137	114.056000
193	161.382000
249	209.534000
305	257.922000
361	304.788000
417	350.806000
473	397.480000
529	444.944000
end
####################
25	31.863273
81	97.455972
137	146.533027
193	187.964818
249	225.066548
305	258.112731
361	286.699116
417	312.772594
473	338.011783
529	361.530173
end
####################
25	17.157147
81	52.476292
137	78.902399
193	101.211825
249	121.189680
305	138.983778
361	154.376447
417	168.416012
473	182.006345
529	194.670093
end
####################

pause -1