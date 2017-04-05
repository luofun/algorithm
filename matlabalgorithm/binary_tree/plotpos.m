function plotpos(pos)

len=size(pos,2);
valVect = len:-1:1;
v=zeros(3,len);
for i=3:-1:1
    %v(i,(find(pos==i))) = valVect(find(pos==i));
    tem = valVect(find(pos==i));
    v(i,1:length(tem)) = tem;
end

subplot(1,3,1); bar(v(1,:));axis([0 len+1 0 len+1]);
subplot(1,3,2); bar(v(2,:));axis([0 len+1 0 len+1]);
subplot(1,3,3); bar(v(3,:));axis([0 len+1 0 len+1]);

 