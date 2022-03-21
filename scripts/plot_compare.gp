reset
set xlabel 'F(n)'
set ylabel 'time (ns)'
set title 'Fibonacci runtime compare'
set term png enhanced font 'Verdana,10'
set output 'plot_compare.png'
set grid
plot [0:92][0:300] \
'plot_input' using 1:2 with linespoints linewidth 2 title "fib recursion",\
'' using 1:3 with linespoints linewidth 2 title "fib fast doubling"