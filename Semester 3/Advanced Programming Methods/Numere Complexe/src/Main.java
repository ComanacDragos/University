public class Main {
    public static void main(String[] args) {
        try
        {
            ExpressionParser.validate(args);
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }

    }
}
