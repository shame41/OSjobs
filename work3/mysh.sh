str_insert="#LY4E# $USER `date +%Y-%m-%d,%H:%M:%S`"
for ofile in $1/*.txt
do
	if [ `grep -c "#LY4E#" $ofile` -eq 0 ];then
		echo $str_insert >> $ofile
	else
		sed -i "/#LY4E#/c $str_insert" $ofile
	fi
done 
