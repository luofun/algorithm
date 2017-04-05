function pos=path2pos(index,LEN)

pos=ones(1,LEN);
shang = index-1;

i=0;
while(shang~=0)
    pos(LEN-i)=rem(shang,3)+1;
    shang = fix(shang/3);
    i=i+1;
end 