function [ list ] = Ladd( list,pos,value )
%LADD 此处显示有关此函数的摘要
%   此处显示详细说明
if pos <= 0
    fprintf('wowowo\n');
    list.error = 1;    
else
    if pos > list.n
        list.list(pos)=value;
        list.n=pos;
    else 
        list.n = list.n + 1;
        for i = list.n : -1 : pos+1
            list.list(i) = list.list(i-1);
        end
        list.list(pos) = value;
    end
end
end
