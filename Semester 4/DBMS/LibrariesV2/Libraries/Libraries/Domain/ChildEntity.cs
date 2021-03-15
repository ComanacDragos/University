using System;
using System.Collections.Generic;
using System.Text;

namespace Libraries.Domain
{
    public class ChildEntity<ID, ParentID>: Entity<ID>
    {
        public ParentID ParentId { get; set; }
    }
}
