function [ long ] = clong( templong,xylocation )
%CLONG 此处显示有关此函数的摘要
%   此处显示详细说明
long=0;

for i=1:length(xylocation)-1
    long = long+templong(xylocation(i),xylocation(i+1));
end
end

