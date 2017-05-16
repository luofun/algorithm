clc;

clear all;

f1  = 100e6; % 100MHz

f2 = 129e6; % 129MHz

Fs = 1e9;% Sampling frequency 1GHz

T = 100e-9; % Sampling time 100nS

N = floor(T*Fs); % Total points

n = 0:N-1;

s = exp(1j*2*pi*f1/Fs*n) + exp(1j*2*pi*f2/Fs*n);

plot(n/Fs*1e9,real(s))

xlabel('Time(nS)','fontsize', 14);

ylabel('Amplitude','fontsize', 14);

grid on;

figure;

[PSD,fp] = periodogram(s,[],'twosided',2^10,Fs);

plot(fp*1e-6,PSD)

xlabel('Frequency(MHz)','fontsize', 14);

ylabel('PSD','fontsize', 14);

grid on;
