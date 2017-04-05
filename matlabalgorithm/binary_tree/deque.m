function que=deque(que)

if size(que.shuzu,1)==1
    que.shuzu = [];
else
    que.shuzu=que.shuzu(2:size(que.shuzu,1),:);
    que.n = que.n-1;
end

end
 