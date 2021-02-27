using System;
using System.Collections.Generic;
using System.Text;

namespace Library.Domain.Validator
{
    abstract class IValidator<E>
    {
        public abstract void Validate(E entity);
    }
}
