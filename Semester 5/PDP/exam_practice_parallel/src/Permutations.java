import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Permutations {
    final List<List<Integer>> permutations = new LinkedList<>();
    int n=7;

    public void run(){
        int noThreads = 4;
        System.out.println("Starting " + Thread.currentThread().getId());
        back(new ArrayList<>(), noThreads-1);
        /*permutations.stream().sorted((a, b)->{
            for(int i=0;i<a.size();i++){
                if(!a.get(i).equals(b.get(i)))
                    return a.get(i)-b.get(i);
            }
            return 0;
        }).forEach(System.out::println);
        */
        System.out.println("Total: " + permutations.size());
    }

    public void back(List<Integer> sol, int noThreads){
        if(sol.size()==n){
            synchronized (permutations){
                permutations.add(new ArrayList<>(sol));
            }
        }
        //if(noThreads>=2)
        //System.out.println(Thread.currentThread().getId() + " " + noThreads);
        List<Integer> temp = new LinkedList<>(sol);
        if(noThreads>=2){
            Thread t = new Worker(new ArrayList<>(sol), noThreads/2);
            t.start();
            for(int i=1;i<=n;i+=2){
                if(temp.contains(i))
                    continue;
                temp.add(i);
                back(temp, noThreads-noThreads/2);
                temp.remove(temp.size()-1);
            }
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }else{
            for(int i=1;i<=n;i++){
                if(temp.contains(i))
                    continue;
                temp.add(i);
                back(temp, noThreads);
                temp.remove(temp.size()-1);
            }
        }
    }

    class Worker extends Thread{
        List<Integer> temp;
        int noThreads;
        Worker(List<Integer> sol, int noThreads){
            this.temp = sol;
            this.noThreads = noThreads;
        }

        @Override
        public void run(){
            System.out.println("Starting " + getId() + " with " + noThreads);
            for(int i=2;i<=n;i+=2){
                if(temp.contains(i))
                    continue;
                temp.add(i);
                back(temp, noThreads);
                temp.remove(temp.size()-1);
            }
        }
    }
}
