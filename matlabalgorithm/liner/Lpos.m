function [ pos ] = Lpos( list,value )
%LPOS �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
j = 1;
pos = [];
for i=1 : +1 : list.n
   if list.list(i) == value
       pos(j) = i; 
       j = j + 1;
   end    
end
end
