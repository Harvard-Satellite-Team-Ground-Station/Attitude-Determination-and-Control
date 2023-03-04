
function endPoint = VectorAddition()
    ave = sum(x(:))/numel(x); 
end

quiver3(0,0,0,1,1,1);hold on;
quiver3(0,0,0,1,0,0);hold on;
quiver3(0,0,0,0,1,0);hold on;
quiver3(0,0,0,0,0,1);hold on;



