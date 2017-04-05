function [ count ] = Hanoi( number )
%HANOI 此处显示有关此函数的摘要
%   此处显示详细说明
% count = 2^number - 1
if number == 1
    count =1;
else
    count = 2 * Hanoi(number - 1) + 1;
end
end

