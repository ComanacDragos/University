using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Libraries.Service;
using Libraries.Domain;


namespace Libraries
{
    public static class ServiceFactory
    {
        public static OneToManyService<int, Entity<int>, int, ChildEntity<int, int>> getService(String parentTable, String childTable)
        {
            return null;
        }
    }
}
