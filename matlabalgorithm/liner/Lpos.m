function [ pos ] = Lpos( list,value )
%LPOS 此处显示有关此函数的摘要
%   此处显示详细说明
j = 1;
pos = [];
for i=1 : +1 : list.n
   if list.list(i) == value
       pos(j) = i; 
       j = j + 1;
   end    
end
end
