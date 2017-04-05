function drawtree(treeVec)

treeplot2(treeVec);

count = size(treeVec,2);   [x,y] = treelayout(treeVec);  
x = x';   y = y';    
name1 = cellstr(num2str((1:count)'));    
text(x(:,1), y(:,1), name1, 'VerticalAlignment','bottom','HorizontalAlignment','right')   
title({'Level Lines'},'FontSize',12,'FontName','Times New Roman');
end
