public class ExpressionParser {
    public static void validate(String[] args)
    {
        if(args.length < 3)
            throw new NumberFormatException("Bad Expression");

        NumarComplex current = ExpressionParser.string2complex(args[0]);
        ExpressionFactory factory = new ExpressionFactory();

        for(int i=1;i<args.length;i+=2)
        {
            if(!args[i].matches("[-+/*]"))
                throw new NumberFormatException("Bad expression");

            NumarComplex next = ExpressionParser.string2complex(args[i+1]);

            if(args[i].compareTo("+") == 0)
            {
                ComplexExpression addition = factory.createExpression(ComplexExpression.Operation.ADDITION, new NumarComplex[]{current, next});
                current = addition.execute();
            }
            else
                if(args[i].compareTo("-") == 0)
                {
                    ComplexExpression subtraction = factory.createExpression(ComplexExpression.Operation.SUBTRACTION, new NumarComplex[]{current, next});
                    current = subtraction.execute();
                }
        }
        System.out.println(current);
    }

    static NumarComplex string2complex(String s) {
        if (!s.matches("([-+]?[1-9]+[0-9]*)?[-+]?(([1-9]+[0-9]*\\*)?i)?"))
            throw new NumberFormatException("Bad expression");

        double re, im;

        if(s.contains("+"))
        {
            String[] tokens = s.split("\\+");
            re = Double.parseDouble(tokens[0]);

            if(tokens[1].compareTo("i") == 0)
                im = 1;
            else
                im = Double.parseDouble(tokens[1].split("\\*")[0]);
        }
        else
        {
            String[] tokens = s.split("-");
            if(s.charAt(0) == '-')
            {
                re = -Double.parseDouble(tokens[1]);

                if(tokens[2].compareTo("i") == 0)
                    im = -1;
                else
                    im = -Double.parseDouble(tokens[2].split("\\*")[0]);
            }
            else
            {
                re = Double.parseDouble(tokens[0]);

                if(tokens[1].compareTo("i") == 0)
                    im = -1;
                else
                    im = -Double.parseDouble(tokens[1].split("\\*")[0]);
            }
        }
        return new NumarComplex(re,im);
    }
}
