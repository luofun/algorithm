clear all;
Fs = 1e10;
fpo=fopen('sin.txt','rt');

[temp,x]=fscanf(fpo,'%lf ',inf);

fclose(fpo);
temp=temp';

plot(temp);
figure;

[PSD,fp] = periodogram(temp,[],'twosided',2^10,Fs);
plot(fp*1e-6,PSD);

figure;
temp2 = awgn(temp,10);
plot(temp2);

figure;
[PSD2,fp2] = periodogram(temp2,[],'twosided',2^10,Fs);
plot(fp2*1e-6,PSD2);

fpw=fopen('backsin.txt','wt');

fprintf(fpw,'%f ',temp2);

fclose(fpw);