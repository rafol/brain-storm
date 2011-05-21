mkdir net/
make
n=20
var=95
lim=200
echo n = $n
mkdir $n'n'
until [ $var = $lim ]; do
   ./brian $var $n < 2500/dataPixValid.txt > $n'n/Simp_'$n'n_'$var
   var=`expr $var + 5`
done
