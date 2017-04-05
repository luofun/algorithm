function [ long ] = countgao( gao1,gao2 )
%COUNTGAO 此处显示有关此函数的摘要
%   此处显示详细说明
long=0;
for i=1:length(gao1)-1
    long = long + sqrt((gao1(i)-gao1(i+1))^2+(gao2(i)-gao2(i+1))^2);
end


end

