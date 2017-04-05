clear;
clc;

testx=[4 8 13 19 7 9 20 4 15 6 17];
testy=[3 16 8 3 15 10 17 9 8 15 7];

xylong = zeros(length(testx),length(testy));

for i=1:length(testx)
    for j=1:length(testy)
        xylong(i,j)=long(testx(i),testy(i),testx(j),testy(j));
    end
    xylong(i,i)=inf;
end

xylong(3,9)=inf;
xylong(9,3)=inf;
xylong(5,10)=inf;
xylong(10,5)=inf;
sum=0;
tempg=xylong;

tempmin=min(min(xylong));

[tminx,tminy]=find(xylong==tempmin);
sum=sum+xylong(tminx(1),tminy(1));

xylong(tminx(1),tminy(1))=inf;
xylong(tminy(1),tminx(1))=inf;

xzb=[testx(tminx(1)),testx(tminy(1))];
yzb=[testy(tminx(1)),testy(tminy(1))];
in=[tminx(1),tminy(1)];
plot(xzb,yzb,'--rs','MarkerSize',10);
hold on;%first try

while(length(in)~=11)
    in1=0;
    in2=0;
    input=0;
    tempmin=min(min(xylong));
    [tminx,tminy]=find(xylong==tempmin);
    for i=1:length(in)
        if tminx(1)==in(i)
            in1=1;
        end
        if tminy(1)==in(i)
            in2=1;
        end
    end
    if (in1==1&&in2~=1) || (in1~=1&&in2==1)
        input=1;
    end
    
    if(input==1)
        if(in1==1)
            in=[in,tminy(1)];
        else
            in=[in,tminx(1)];
        end
        xzb=[testx(tminx(1)),testx(tminy(1))];
        yzb=[testy(tminx(1)),testy(tminy(1))];
        plot(xzb,yzb,'--rs','MarkerSize',10);
        hold on;
        xylong=tempg;
        sum=sum+xylong(tminx(1),tminy(1));
        xylong(tminx(1),tminy(1))=inf;
        xylong(tminy(1),tminx(1))=inf;
        tempg=xylong;
    else
        xylong(tminx(1),tminy(1))=inf;
        xylong(tminy(1),tminx(1))=inf;
    end
end
    
    
    
