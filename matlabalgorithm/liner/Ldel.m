function [ list ] = Ldel( list,pos )
%LDEL �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
if pos <= 0
    fprintf('wowowo\n');
    list.error = 1;
elseif pos > list.n
    fprintf('no element in here\n');
elseif pos <= list.n
    list.list(pos)=[];
    list.n = list.n - 1;
end
end

