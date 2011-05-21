system "mkdir gotas"
offset = 0
(1..29).each{ |i| 
	prefix = "gotas/"
	system "./contaGotas Terrestre29/Terrestre" + i.to_s + ".bmp gotas/mask" + i.to_s + ".bmp gotas/ " + offset.to_s + " .bmp 10 17 > " + prefix + "log" + i.to_s + ".txt"
	$stdout.write "next offset: "
	offset = gets.chomp.to_i
}
