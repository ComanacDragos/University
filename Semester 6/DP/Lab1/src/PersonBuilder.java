public class PersonBuilder {
    private String name;
    private Integer age;

    private PersonBuilder(){}

    public static PersonBuilder builder(){
        return new PersonBuilder();
    }

    public PersonBuilder setName(String name) {
        this.name = name;
        return this;
    }

    public PersonBuilder setAge(Integer age) {
        this.age = age;
        return this;
    }

    public Person build(){
        return new Person(name, age);
    }
}
