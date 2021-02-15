interface IEvent{
    public Class<?> getInner();
}

class Event<T> implements IEvent{
    T data;

    public Event(T data) {
        this.data = data;
    }

    public T getData() {
        return data;
    }

    public Class<?> getInner(){
        return data.getClass();
    }
}

class A{

}

class B extends A{
    @Override
    public String toString() {
        return "I am b";
    }
}

class C implements IEvent{
    @Override
    public Class<?> getInner() {
        return null;
    }
}
class Main{
    public static void main(String[] args) {
        A a = new A();
        System.out.println(a.getClass());

        IEvent event = new Event<>(a);

        if(event.getInner().getName().equals("B")){
            if(event instanceof Event) {
                System.out.println(((Event<B>) event).getData());
            }
        }else{
            System.out.println("I am not B");
        }
    }
}