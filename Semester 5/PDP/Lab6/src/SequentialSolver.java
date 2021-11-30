import java.util.ArrayList;
import java.util.List;

public class SequentialSolver extends Solver{

    public SequentialSolver(DirectedGraph graph) {
        super(graph);
    }

    public void bkt(List<Integer> path){
        path.add(0);
        for(int i=0;i<graph.getNoVertices();i++){
            path.set(path.size()-1, i);
            if(consistent(path)){
                if(solution(path))
                    solutions.add(new ArrayList<>(path));
                else
                    bkt(new ArrayList<>(path));
            }
        }
    }
}

