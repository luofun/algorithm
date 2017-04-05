function index=pos2path(pos,LEN)
index=sum((pos-1).*3.^(LEN-1:-1:0))+1;
end

  