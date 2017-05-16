clear all;
fpo=fopen('backmat.txt','rt');

[temp,x]=fscanf(fpo,'%lf ',inf);

fclose(fpo);
temp=temp';
plot(temp);