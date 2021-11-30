import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class DirectedGraph {
    Map<Integer, Set<Integer>> dictOut = new HashMap<>();
    Integer noVertices, noEdges;

    public DirectedGraph(String file){
        try(BufferedReader reader = new BufferedReader(new FileReader(file))){
            List<String> lines = reader.lines().collect(Collectors.toList());
            String[] tokens = lines.get(0).split(" ");
            noVertices = Integer.parseInt(tokens[0]);
            noEdges = Integer.parseInt(tokens[1]);
            for(int i=0;i<noVertices;i++)
                dictOut.put(i, new HashSet<>());
            for(int i=1;i<=noEdges;i++){
                tokens = lines.get(i).split(" ");
                Integer left = Integer.parseInt(tokens[0]);
                Integer right = Integer.parseInt(tokens[1]);
                dictOut.get(left).add(right);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public DirectedGraph(int vertices, int edges){
        this.noVertices = vertices;
        this.noEdges = edges;
        int remainingEdges = edges;
        for(int i=0;i<noVertices;i++)
            dictOut.put(i, new HashSet<>());

        Random random = new Random();
        while(remainingEdges > 0){
            int left = random.nextInt(noVertices);
            int right = random.nextInt(noVertices);
            if(!dictOut.get(left).contains(right)) {
                dictOut.get(left).add(right);
                remainingEdges--;
            }
        }
        try(PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter("data/" + vertices + "_" + edges + ".txt")))){
            writer.println(vertices + " " + edges);
            dictOut.entrySet().forEach(entry-> entry.getValue().forEach(
                    end -> writer.println(entry.getKey() + " " + end)
            ));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Map<Integer, Set<Integer>> getDictOut() {
        return dictOut;
    }

    public boolean isEdge(Integer x, Integer y){
        return dictOut.get(x).contains(y);
    }

    public Integer getNoVertices() {
        return noVertices;
    }

    public Integer getNoEdges() {
        return noEdges;
    }
}
