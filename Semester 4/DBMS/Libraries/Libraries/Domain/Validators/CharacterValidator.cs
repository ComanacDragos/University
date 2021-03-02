using System;
using System.Collections.Generic;
using System.Text;
using Libraries.Exceptions;

namespace Libraries.Domain.Validator
{
    public class CharacterValidator : IValidator<Character>
    {
        public void Validate(Character entity)
        {
            string errorMessage = "";

            if (entity.FullName.Length == 0)
                errorMessage += "Full name can't be void.";
            if (!(entity.CharacterRole.Equals("Primary") || entity.CharacterRole.Equals("Secondary")))
                errorMessage += "Character role must be primary or secondary";

            if (errorMessage.Length != 0)
                throw new MyException(errorMessage);
        }
    }
}
