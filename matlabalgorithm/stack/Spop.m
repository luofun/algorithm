function [ stack,value ] = Spop( stack )
%SPOP 此处显示有关此函数的摘要
%   此处显示详细说明
if stack.n == 0
    fprintf('no element to pop');
    value =0;
else
    value = stack.list(stack.n);
    stack.list(stack.n) = [];
    stack.n = stack.n - 1;
    
end
end

