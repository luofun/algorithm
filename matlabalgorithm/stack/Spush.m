function [ stack ] = Spush( stack,value )
%SPUSH 此处显示有关此函数的摘要
%   此处显示详细说明
stack.n = stack.n + 1;
stack.list(stack.n) = value;

end

