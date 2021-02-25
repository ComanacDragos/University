using System;
using System.Collections.Generic;
using System.Text;

namespace Library.Exceptions
{
    class MyException: ApplicationException
    {
        MyException(string message) : base(message) { }
    }
}
