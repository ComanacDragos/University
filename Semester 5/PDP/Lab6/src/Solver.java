import java.util.ArrayList;
import java.util.List;

public abstract class Solver {
    protected DirectedGraph graph;
    protected List<List<Integer>> solutions = new ArrayList<>();

    public Solver(DirectedGraph graph){
        this.graph = graph;
    }

    public List<List<Integer>> solve(){
        bkt(new ArrayList<>());
        return solutions;
    }

    public boolean consistent(List<Integer> path){
        if(path.size() > graph.getNoVertices()+1)
            return false;
        if(path.size() == 0 || (path.size() == 1 && path.get(0).equals(0)))
            return true;
        if(!path.get(0).equals(0))
            return false;

        if(path.size() != graph.getNoVertices()+1){
            for(int i=0;i<path.size()-1;i++)
                if(path.get(i).equals(path.get(path.size()-1)))
                    return false;
        }
        return graph.isEdge(path.get(path.size()-2), path.get(path.size()-1));
    }

    public boolean solution(List<Integer> path){
        if(path.size()<3)
            return false;
        return path.get(0).equals(path.get(path.size() - 1)) && path.size() == graph.getNoVertices() + 1;
    }

    public abstract void bkt(List<Integer> path);
}
