function [ stack,value ] = Spop( stack )
%SPOP �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
if stack.n == 0
    fprintf('no element to pop');
    value =0;
else
    value = stack.list(stack.n);
    stack.list(stack.n) = [];
    stack.n = stack.n - 1;
    
end
end

