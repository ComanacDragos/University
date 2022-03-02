public class Main {
    public static void main(String[] args) {
        Person person = PersonBuilder.builder()
                .setAge(20)
                .setName("name")
                .build();
        System.out.println(person);
    }
}
