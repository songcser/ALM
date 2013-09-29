using System;
using System.Collections.Generic;
using System.Text;

namespace TestFramework.TestCase
{
    public class InputParameterCollection : List<InputParameter>
    {
        public List<object> ToParamArray()
        {
            List<object> paramList = new List<object>();
            foreach (InputParameter item in this)
            {
                object param = null;

                switch (item.Type)
                {
                    case ParameterType.Double:
                        param = double.Parse(item.Value);
                        break;
                    case ParameterType.Int:
                        param = int.Parse(item.Value);
                        break;
                    case ParameterType.String:
                        param = item.Value.ToString();
                        break;
                }

                paramList.Add(param);
            }

            return paramList;
        }
    }
}
