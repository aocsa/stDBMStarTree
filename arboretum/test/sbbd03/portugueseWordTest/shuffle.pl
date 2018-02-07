sub InitMap{
   local($w);

   for ($w = 0; $w < 5000; $w++){
      $map[$w] = int($w / 250);
   }#end for
}#end InitMap

sub ShuffleMap{
   local($w);
   local($i);
   local($j);
   local($tmp);

   for ($w = 0; $w < ($#map + 1) * 3; $w++){
      $i = rand($#map + 1);
      $j = rand($#map + 1);

      $tmp = $map[$i];
      $map[$i] = $map[$j];
      $map[$j] = $tmp;
   }#end for
}#end Shuffle

InitMap();
ShuffleMap();

open(out1, ">cidades500.txt");
open(out2, ">cidadesresto.txt");

for ($v = 0; $v <= $#map; $v++){
   if ($map[$v] == 0) {
      printf(out1 "$v to File 1\n");
   } else {
      if ($map[$v] == 1) {
         printf(out1 "$v to File 1 & 2\n");
         printf(out2 "$v to File 1 & 2\n");
      } else {
         printf(out2 "$v to File 2\n");
      }#end if
   }# end if
}#end for
close(out1);
close(out2);
