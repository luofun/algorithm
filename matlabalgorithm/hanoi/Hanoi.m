function [ count ] = Hanoi( number )
%HANOI �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
% count = 2^number - 1
if number == 1
    count =1;
else
    count = 2 * Hanoi(number - 1) + 1;
end
end

