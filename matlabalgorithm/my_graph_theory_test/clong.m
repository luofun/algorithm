function [ long ] = clong( templong,xylocation )
%CLONG �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
long=0;

for i=1:length(xylocation)-1
    long = long+templong(xylocation(i),xylocation(i+1));
end
end

