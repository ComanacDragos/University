using System;
using System.Collections.Generic;
using System.Text;

namespace Library.Domain
{
    class ChildEntity<ID, ParentID>: Entity<ID>
    {
        public ParentID ParentId { get; set; }
    }
}
