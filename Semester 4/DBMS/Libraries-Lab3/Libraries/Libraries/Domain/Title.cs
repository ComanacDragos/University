using System;
using System.Collections.Generic;
using System.Text;

namespace Libraries.Domain
{
    public class Title: Entity<int>
    {
        public string Name { get; set; }

        public Title(int id, string name)
        {
            this.Id = id;
            this.Name = name;
        }


        public override string ToString()
        {
            return this.Id + ". " + this.Name;
        }

        public override bool Equals(object obj)
        {
            return obj is Title title &&
                Id == title.Id;
        }

        public override int GetHashCode()
        {
            return 539060726 + EqualityComparer<string>.Default.GetHashCode(Name);
        }
    }
}
