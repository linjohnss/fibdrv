reset
set xlabel 'F(n)'
set ylabel 'time (ns)'
set title 'Fibonacci runtime'
set term png enhanced font 'Verdana,10'
set output 'plot_output.png'
set grid
plot [0:92][0:2000] \
'plot_input' using 1:2 with linespoints linewidth 2 title "fib interative kernel",\
'' using 1:3 with linespoints linewidth 2 title "fib interative user"