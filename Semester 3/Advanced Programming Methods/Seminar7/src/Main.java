import java.io.*;
import java.util.Arrays;
import java.util.List;
import java.util.function.Supplier;
import java.util.stream.Stream;

public class Main {
    public static void main(String[] args) {


    }

    static void runExamples(){
        p1();
        p2();
        p3();
        p4();
        p5();
        p6();
        p7();
        p8();
        p9();
        p10();
    }

    static void p1(){
        /*
        P1. Loop down the words and print each on a separate line, with two spaces in front of each word. Don’t use map.
         */
        System.out.println("P1");
        List<String> words = Arrays.asList("str1", "str2", "str3", "str4");

        words.forEach(s -> System.out.println("  " + s));

        System.out.println();
    }

    static void p2(){
        /*
        P2. Repeat the previous problem, but without the two spaces in front. This is trivial if you use the same
         approach as in P1, so the point is to use a method reference here, as opposed to an explicit lambda as in P1.
         */
        System.out.println("P2");
        List<String> words = Arrays.asList("str1", "str2", "str3", "str4");

        words.forEach(System.out::println);

        System.out.println();
    }

    static void p3(){
        /*
        P3. We assume that we have a method StringUtils.transformedList(List<String>, Function1<String>)
         where interface Function1<T> { T app(T);}and we produced transformed lists like this:
         • List<String> excitingWords = StringUtils.transformedList(words, s -> s + "!");
         • List<String> eyeWords = StringUtils.transformedList(words, s -> s.replace("i", "eye"));
         • List<String> upperCaseWords = StringUtils.transformedList(words, String::toUpperCase);
         Produce the same lists as above, but this time use streams and the builtin “map” method.
         */
        System.out.println("P3");
        List<String> words = Arrays.asList("str1", "str2 i", "str3", "string4");

        words.stream().map(s -> s + '!').forEach(System.out::println);

        System.out.println();

        words.stream().map(s -> s.replace("i", "eye")).forEach(System.out::println);

        System.out.println();

        words.stream().map(String::toUpperCase).forEach(System.out::println);

        System.out.println();
    }

    static void p4(){
        /*
        P4. We assume that we have the method StringUtils.allMatches(List<String>, Predicate1<String>) where  interface
         Predicate1<T> { boolean check(T);}and we produced filtered lists like this:
         • List<String> shortWords = StringUtils.allMatches(words, s -> s.length() < 4);
         • List<String> wordsWithB = StringUtils.allMatches(words, s -> s.contains("b"));
         • List<String> evenLengthWords = StringUtils.allMatches(words, s -> (s.length() % 2) == 0);
         Produce the same lists as above, but this time use “filter”.
         */
        System.out.println("P4");
        List<String> words = Arrays.asList("st", "str2 i", "bbb", "string4b");

        words.stream().filter(s -> s.length() < 4).forEach(System.out::println);

        System.out.println();

        words.stream().filter(s -> s.contains("b")).forEach(System.out::println);

        System.out.println();

        words.stream().filter(s -> s.length()%2 == 0).forEach(System.out::println);

        System.out.println();
    }

    static void p5(){
        /*
        P5. Turn the strings into uppercase, keep only the ones that are shorter than 4 characters,
        of what is remaining, keep only the ones that contain “E”, and print the first result.
        Repeat the process, except checking for a “Q” instead of an “E”. When checking for the “Q”, try to avoid
        repeating all the code from when you checked for an “E”.
        */
        System.out.println("P5");
        List<String> words = Arrays.asList("ste", "str2 i", "qeb", "string4b", "ebq");

        Supplier<Stream<String>> filteredStrings = () -> words.stream()
                .filter(s -> s.length() < 4)
                .filter(s -> s.contains("e"));

        filteredStrings.get().findFirst().ifPresent(System.out::println);

        System.out.println();

        filteredStrings.get().filter(s -> s.contains("q")).findFirst().ifPresent(System.out::println);

        System.out.println();
    }

    static void p6(){
        /*
        P6. Produce a single String that is the result of concatenating the uppercase versions of all of the Strings.
        Use a single reduce operation, without using map.
         */
        System.out.println("P6");
        List<String> words = Arrays.asList("ste", "str2 i", "qeb", "string4b", "ebq");

        String result = words.stream().reduce("", (a, b) -> a.toUpperCase() + b.toUpperCase());
        System.out.println(result);

        System.out.println();
    }

    static void p7(){
        /*
        P7. Produce the same String as above, but this time via a map operation that turns the words into uppercase,
        followed by a reduce operation that concatenates them.
         */
        System.out.println("P7");

        List<String> words = Arrays.asList("ste", "str2 i", "qeb", "string4b", "ebq");

        String result = words.stream().map(String::toUpperCase).reduce("", (a, b) -> a+b);
        System.out.println(result);

        System.out.println();
    }

    static void p8(){
        /*
        P8. Produce a String that is all the words concatenated together, but with commas in between.
        E.g., the result should be "hi,hello,...". Note that there is no comma at the beginning, before “hi”,
        and also no comma at the end, after the last word. Major hint: there are two versions of reduce discussed in
        the notes.
         */
        System.out.println("P8");
        List<String> words = Arrays.asList("ste", "str2 i", "qeb", "string4b", "ebq");
        words.stream().reduce((a, b) -> a + ',' + b).ifPresent(System.out::println);
        System.out.println();
    }

    static void p9(){
        /*
        P9. Find the total number of characters (i.e., sum of the lengths) of the strings in the List.
         */
        System.out.println("P9");
        List<String> words = Arrays.asList("str1", "str2", "str3", "str4");

        words.stream().map(String::length).reduce(Integer::sum).ifPresent(System.out::println);

        System.out.println();
    }

    static void p10(){
        /*
        P10. Find the number of words that contain an “h”.
         */
        System.out.println("P10");
        List<String> words = Arrays.asList("strh1", "str2", "strh3", "str4");

        System.out.println(words.stream().filter(s -> s.contains("h")).count());

        System.out.println();
    }
}
