

a=[  4     8    13    19     7     9    20     4    15     6    17
    3    16     8     3    15    10    17     9     8    15     7]';
b=pdist(a);
n=length(a);
k=1;
for i=1:10
    for j=i+1:11
        d(1:2,k)=[i,j];
        k=k+1;
    end
end
d=[d;b];

[T c]=Krusf(d,1)
L=length(T);
for j=1:L
    x=[a(T(1,j),1),a(T(2,j),1)];
    y=[a(T(1,j),2),a(T(2,j),2)];
    plot(x, y,  '--rs','MarkerSize',10);
    hold on;
end