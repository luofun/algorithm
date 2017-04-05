

function flag=checkValueSwap(pos, sStkSN, tStkSN, posValueHis,sijinzhi)
indexS = find(pos==sStkSN,1,'last');
indexT = find(pos==tStkSN,1,'last');

if isempty(indexS)
    flag = 0;
elseif isempty(indexT)
    indexT = indexS;
    pos(indexT) = tStkSN;
    if find(posValueHis==sum(pos.*sijinzhi))
        flag=0;
    else
        flag = 1;
    end
elseif indexS<indexT
    flag = 0;
elseif indexS>indexT
    indexT = indexS;
    pos(indexT) = tStkSN;
    if find(posValueHis==sum(pos.*sijinzhi))
        flag=0;
    else
        flag = 1;
    end    
else
    disp('WHAT HAPPEN??!!')
end
    



