#!/bin/bash
#
# Generate "left" animation json for all animations
# in an "<entity>/animations" directory. 
#
# Launch from that directory !

for d in `ls | grep right`; do
	e=`echo $d | sed 's/right/left/g'`
	mkdir -p $e
	j=$e/animation.json
	if ! test -f $j; then
		echo '{"flip":"../'$d'"}' > $j
	fi
done
