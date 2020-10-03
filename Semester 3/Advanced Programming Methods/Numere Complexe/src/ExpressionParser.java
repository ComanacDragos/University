public class ExpressionParser {
    public static void validate(String[] args)
    {
        if(args.length < 3)
        {
            System.out.println("Bad expression");
        }
        else
        {
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
                        ComplexExpression subtraction = factory.createExpression(ComplexExpression.Operation.SUBSTRACTION, new NumarComplex[]{current, next});
                        current = subtraction.execute();
                    }
            }
            System.out.println(current);
        }
    }

    static NumarComplex string2complex(String s)
    {
        if(!s.matches("([1-9]+[0-9]*)?[-+]?(([1-9]+[0-9]*\\*)?i)?"))
            throw new NumberFormatException("Bad expression");

        int re = Integer.parseInt(s.split("[-+]")[0]);
        int im;
        String aux = s.split("[-+]")[1];

        if(aux.compareTo("i") == 0)
            im = 1;
        else
        {
            im = Integer.parseInt(aux.split("\\*")[0]);

            if(s.contains("-"))
                im *= -1;
        }
        return new NumarComplex(re, im);
    }
}
