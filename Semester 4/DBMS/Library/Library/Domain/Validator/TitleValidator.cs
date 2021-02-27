using System;
using System.Collections.Generic;
using System.Text;
using Library.Exceptions;

namespace Library.Domain.Validator
{
    class TitleValidator : IValidator<Title>
    {
        public override void Validate(Title entity)
        {
            if (entity.Name.Length == 0)
                throw new MyException("Title is void");
        }
    }
}
