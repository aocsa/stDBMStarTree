sub InitMap{
   local($w);

   for ($w = 0; $w < 21473; $w++){
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

open(inp, "<port.txt");
open(out1, ">port250.txt");
open(out2, ">port_resto.txt");

for ($v = 0; $v <= $#map; $v++){
#for ($v = 0; $v <= 20; $v++){
	$word = <inp>;
	chop($word);
	# printf("$word\n");
   if ($map[$v] == 0) {
	   # 250 removidos
      printf(out1 "$word\n");
   } else {
		if ($map[$v] == 1){
	   	# 250 comuns
	   	printf(out1 "$word\n");
	   	printf(out2 "$word\n");
   	}else{
	   	# Resto
      	printf(out2 "$word\n");
      }#end if
   }# end if
}#end for

close(inp);
close(out1);
close(out2);
