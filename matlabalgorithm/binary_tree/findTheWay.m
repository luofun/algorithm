function route=findTheWay(path,lastindex)

route = [];
index = lastindex;
while(path(index)~=0)
    route = [route, path(index)];
    index = path(index);
end

 
