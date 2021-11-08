using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;


namespace Lab4
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            var urls = new List<string>()
            {
                "www.cs.ubbcluj.ro/~rlupsa/edu/pdp/progs/srv-begin-end.cs",
                "www.cs.ubbcluj.ro/~rlupsa/edu/pdp/progs/srv-task.cs",
                "www.cs.ubbcluj.ro/~rlupsa/edu/pdp/progs/srv-await.cs"
            }; 
            new CallbackParser(urls);
            new TaskParser(urls);
            new AwaitParser(urls);
        }
    }
}