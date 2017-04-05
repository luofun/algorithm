
%v = [0.8147 0.9058 0.1270 0.9134 0.6324 0.0975 0.2785 0.5469 0.9575 0.9649 0.1576 0.9706  0.9572 0.4854 0.8003];
origv = rand(1,7); 
v=origv;


MAXVAL = 100;
ov = zeros(size(v));
numOL = length(v);

vv = zeros(1, numOL*2-1);
tv = vv;
vv(numOL:length(tv)) = v; 

for i=numOL-1:-1:1
    [i1,i2] = findLeast2Val(v+ov);
    vv(i) = v(i1)+v(i2);
    ov(i1) = MAXVAL;
    ov(i2) = MAXVAL;
    tv(i1+i)=i;
    tv(i2+i)=i;
    v = [vv(i),v];
    ov = [0,ov];
end
drawtree(tv);
