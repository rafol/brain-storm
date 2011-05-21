mkdir net/
make
n=3
var=5
lim=200
echo n = $n
mkdir $n'n'
until [ $var = $lim ]; do
   ./brian $var $n < 2500/dataPixValid.txt > $n'n/Simp_'$n'n_'$var
   var=`expr $var + 5`
done
n=`expr $n + 2`
until [ $n = "25" ]; do
	var=5
	echo n = $n
	mkdir $n'n'
	until [ $var = $lim ]; do
	   ./brian $var $n < 2500/dataPixValid.txt > $n'n/Simp_'$n'n_'$var
	   var=`expr $var + 5`
	done
	n=`expr $n + 2`
	var=5
	echo n = $n
	mkdir $n'n'
	until [ $var = $lim ]; do
	   ./brian $var $n < 2500/dataPixValid.txt > $n'n/Simp_'$n'n_'$var
	   var=`expr $var + 5`
	done
	n=`expr $n + 3`
done
