using System;
using System.Collections.Generic;
using System.Text;

namespace TestFramework.TestCase
{
    public class OutputParameterCollection : List<OutputParameter>
    {
        public List<object> ToParamArray()
        {
            List<object> paramList = new List<object>(this.Count);
            for (int idx = 0; idx < this.Count; idx++)
            {
                paramList.Add(null);
            }
            return paramList;
        }
    }
}
