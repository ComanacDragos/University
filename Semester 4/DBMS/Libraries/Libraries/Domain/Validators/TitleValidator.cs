using System;
using System.Collections.Generic;
using System.Text;
using Libraries.Exceptions;

namespace Libraries.Domain.Validator
{
    public class TitleValidator : IValidator<Title>
    {
        public void Validate(Title entity)
        {
            if (entity.Name.Length == 0)
                throw new MyException("Title is void");
        }
    }
}
