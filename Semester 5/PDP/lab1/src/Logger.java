public class Logger {
    String context;

    public Logger(String context) {
        this.context = context;
    }

    public String getContext() {
        return context;
    }

    public void setContext(String context) {
        this.context = context;
    }

    public void log(String message){
        System.out.println(context + " : " + message);
    }
}
