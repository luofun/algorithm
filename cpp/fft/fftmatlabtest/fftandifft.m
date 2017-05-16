clear all;
temp2i=[];
temp2r=[];
fp=fopen('t1.txt','rt');
fp2=fopen('t2.txt','rt');
[temp,x]=fscanf(fp,'%lf ',inf);
temp=temp';
[temp2,x2]=fscanf(fp2,'%lf%lf%*c ',inf);
for i=1:x2
   if mod(i,2)==0
       temp2i=[temp2i,temp2(i)];
   else
       temp2r=[temp2r,temp2(i)];
   end
end
n=0:0.1:200;

y=sin(2*pi*0.2*n)+sin(2*0.213*n);
%disp(y(1));
y=y(1:1024);
%disp(size(y));
fpw=fopen('t3.txt','wt');

fprintf(fpw,'%f ',y);

fclose(fpw);
plot(y);
figure;
y2 = awgn(y,20);
fpw=fopen('t4.txt','wt');

fprintf(fpw,'%f ',y);

fclose(fpw);
plot(y2);
%hold on;%disp(temp);
%disp(temp2);
%plot(temp);

fclose(fp);
fclose(fp2);