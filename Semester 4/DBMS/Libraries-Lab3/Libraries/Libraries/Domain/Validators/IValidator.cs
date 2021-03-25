using System;
using System.Collections.Generic;
using System.Text;

namespace Libraries.Domain.Validator
{
    public interface IValidator<E>
    {
        void Validate(E entity);
    }
}
