function [ stack ] = Spush( stack,value )
%SPUSH �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
stack.n = stack.n + 1;
stack.list(stack.n) = value;

end

