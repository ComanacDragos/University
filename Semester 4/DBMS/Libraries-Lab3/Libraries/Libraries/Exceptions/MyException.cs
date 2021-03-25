using System;
using System.Collections.Generic;
using System.Text;

namespace Libraries.Exceptions
{
    public class MyException: ApplicationException
    {
        public MyException(string message) : base(message) { }
    }
}
