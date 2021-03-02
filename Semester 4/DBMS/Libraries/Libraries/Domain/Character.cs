using System;
using System.Collections.Generic;
using System.Text;

namespace Libraries.Domain
{
    public class Character: ChildEntity<int, int>
    {
        public int TitleId
        { get
            {
                return ParentId;
            }
            set
            {
                ParentId = value;
            }
        }
        public string FullName { get; set; }
        public string CharacterRole { get; set; }

        public Character(int characterId, int titleId, string fullName, string characterRole)
        {
            Id = characterId;
            TitleId = titleId;
            FullName = fullName;
            CharacterRole = characterRole;
        }

        public override bool Equals(object obj)
        {
            return obj is Character character &&
                   Id == character.Id;
        }

        

        public override string ToString()
        {
            return Id + ". " + TitleId + ", " + FullName + ", " + CharacterRole;
        }

        public override int GetHashCode()
        {
            var hashCode = -1048809701;
            hashCode = hashCode * -1521134295 + TitleId.GetHashCode();
            hashCode = hashCode * -1521134295 + EqualityComparer<string>.Default.GetHashCode(FullName);
            hashCode = hashCode * -1521134295 + EqualityComparer<string>.Default.GetHashCode(CharacterRole);
            return hashCode;
        }
    }
}
