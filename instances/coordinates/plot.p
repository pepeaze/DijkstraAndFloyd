reset
# This file is called   force.p
#set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
unset key
#unset tics
#unset border
unset xtics
unset ytics
set title "Flórida Tempo Difícil"
set xlabel "X"
set ylabel "Y"
set terminal png enhanced font "Helvetica,20"
set output 'output.png'
      #set key 0.01,100
      #set label "Yield Point" at 0.003,260
      #set arrow from 0.0028,250 to 0.003,280
      #set xr [0.0:0.022]
      #set yr [0:325]
plot    'USA-road-d.FLA.co' u 3:4 w d , \
      	'USA-road-t.FLA.Visited.123' u 3:4 w d, \
		'USA-road-t.FLA.Path.123' u 3:4


