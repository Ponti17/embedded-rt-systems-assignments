load 'out_arch_left.txt'
load 'in_arch_left.txt'
x=[1:1:size(in_arch_left)]; 
figure(2)
plot(x,in_arch_left,x,out_arch_left,'r')
xlabel('Sample N')
ylabel('Fixed point')
title('Architecture Level')
