function [ind1,ind2]=findLeast2Val(v)
len=length(v);

if len==2
    ind1=1; ind2=2;
    return;
end


MIN2=100;
MIN1=99;
ind1=1; ind2=1;
for i=1:len
    if v(i)<MIN2, ind2=i; MIN2=v(ind2);end
    if v(i)<MIN1, 
        MIN2 = MIN1; ind2=ind1; 
        MIN1 = v(i); ind1=i;
    end
end



% ind1=1; %最小的数值的下标
% ind2=2; %第二小的数值的下标
% if v(ind1)>v(ind2) tem=ind1; ind1=ind2; ind2=tem; end
% 
% 
% for i=2:len
%     if v(ind2)>v(i) 
%         ind2=i;
%         if v(ind1)>v(ind2) tem=ind1; ind1=ind2; ind2=tem; end
%     end
% end
