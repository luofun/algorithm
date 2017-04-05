clear
LEN=3;

posnow=ones(1,LEN); 
sijinzhi=4.^(LEN-1:-1:0);
posValueHis=sum(posnow.*sijinzhi);

que.n=0;
que.shuzu=[];
que=enque(que,posnow);

path=zeros(1,LEN^(ceil(LEN/2)+1));%storage for the path number

count=0;
while(~all(frontque(que)==3))
    count=count+1;
    %disp('---------------------');
    %disp(count);
    
    pos = frontque(que);
    que = deque(que);
    posnow = pos;
    
    for colNum=1:3
        for j=LEN:-1:1
            if pos(j)==colNum
                for colOther=1:3
                    if colOther~=colNum
                        if checkValueSwap(pos,colNum,colOther,posValueHis,sijinzhi)
                            pos(j)=colOther;
                            que=enque(que,pos);
                            posValueHis = [posValueHis,sum(pos.*sijinzhi)];
                            path(pos2path(pos,LEN))=pos2path(posnow,LEN);
                            
                            if all(pos==3)
                                disp('+++++++++++')
                                disp(count);
                                disp('+++++++++++')
                            end
                            
                            pos = posnow;
                        end
                    end
                end
                break;
            end
        end
    end


end



showbar=1;
if showbar==1    
    lastindex=pos2path(ones(1,LEN)*3,LEN);
    route=findTheWay(path,lastindex);
    route=fliplr(route);
    for i=1:length(route)
        pos=path2pos(route(i),LEN);
        plotpos(pos);  pause;
    end
    plotpos(ones(1,LEN)*3);
end
