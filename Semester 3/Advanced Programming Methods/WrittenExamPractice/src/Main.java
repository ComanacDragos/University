import java.util.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        //second();
        third();
    }

    static void first(){
        List<Integer> numbers = Arrays.asList(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
        System.out.println(
                numbers.stream()
                        .filter(e->e%2==0 && e%3==0)
                        .map(e->"At"+(e+1) + "km")
                        .collect(Collectors.joining())
        );
    }

    static void second(){
        List<Integer> numbers = Arrays.asList(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);

        System.out.println(
                numbers.stream()
                    .filter(e->!(e%3==0 || e%7==0))
                    .map(e->e-1)
                    .reduce(0,(a,b)->(a+b)%5)
        );
    }

    static void third(){
        List<Integer> numbers = Arrays.asList(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
        List<Integer> list = Arrays.asList(numbers.stream()
                .filter(e->e%4==0)
                .map(e->e+1)
                .reduce(0, (a,b)->(a+b)%2)
        );

        System.out.println(list);
    }

}
