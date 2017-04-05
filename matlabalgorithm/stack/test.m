function [  ] = test( stack )
%TEST 此处显示有关此函数的摘要
%   此处显示详细说明
fprintf('hello\n');
if stack.error ==1
    fprintf('error\n');
    %error('bad');

end

