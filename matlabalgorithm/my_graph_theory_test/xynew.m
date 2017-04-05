clear;
clc;
x=[4,8,13,19,7,9,20,4,15,6,17];
y=[3,16,8,3,15,10,17,9,8,15,7];
xzb=[];
yzb=[];
xylong = zeros(length(x),length(y));
templong =xylong;
for i=1:length(x)
    for j=1:length(y)
        xylong(i,j)=long(x(i),y(i),x(j),y(j));
    end
    xylong(i,i)=255;
end

templong=xylong;
minlong=min(min(xylong));
[xm,ym]=find(xylong==minlong);
xzb=[x(xm(1)),x(ym(1))];
yzb=[y(xm(1)),y(ym(1))];
xylong(xm(1),ym(1))=255;
xylong(ym(1),xm(1))=255;
xylen=2;
xylocation=[xm(1),ym(1)];
insign1=0;
insign2=0;
sign=0;


templocation=xm;
tempg=xylong;

while((min(min(xylong)) ~= 255) || (length(xylocation)~=11))
sign=0;
insign1=0;
insign2=0;
mark1=0;
mark2=0;

minlong=min(min(xylong));
[xm,ym]=find(xylong==minlong);
%for i=1:xylen
   if xm(1)==xylocation(1) || xm(1)==xylocation(xylen)
       insign1=1;
       mark1= (xm(1)==xylocation(1));
   end
   if ym(1)==xylocation(1) || ym(1)==xylocation(xylen)
       insign2=1;
       mark2= (ym(1)==xylocation(1));
   end
   if insign1==1 || insign2==1
       sign=1;
   end
   if insign1==1 && insign2==1
       sign = 0;
       mark1=0;
       mark2=0;
       insign1=0;
       insign2=0;
   end
   if xylen>=3 
    for i=2:xylen-1
       if xm(1)==xylocation(i) || ym(1)==xylocation(i)
           sign = 0;
           mark1=0;
           mark2=0;
           insign1=0;
           insign2=0;
       end
     end
    end
if sign==1
    xylen=xylen+1;
    if insign1==1
        if mark1==1
            xzb=[x(ym(1)),xzb];
            yzb=[y(ym(1)),yzb];
            xylocation=[ym(1),xylocation];
        else
            xzb=[xzb,x(ym(1))];
            yzb=[yzb,y(ym(1))];
             xylocation=[xylocation,ym(1)];
        end
    elseif insign2==1
        if mark2==1
            xzb=[x(xm(1)),xzb];
            yzb=[y(xm(1)),yzb];
            xylocation=[xm(1),xylocation];
        else
            xzb=[xzb,x(xm(1))];
            yzb=[yzb,y(xm(1))];
            xylocation=[xylocation,xm(1)];
        end
    end
    xylong=tempg;
    xylong(xm(1),ym(1))=255;
    xylong(ym(1),xm(1))=255;
    tempg=xylong;
else
    xylong(xm(1),ym(1))=255;
    xylong(ym(1),xm(1))=255;
end
end%%%idea stepback means fuzhi