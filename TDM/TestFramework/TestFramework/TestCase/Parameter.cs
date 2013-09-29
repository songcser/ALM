using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Text.RegularExpressions;

namespace TestFramework.TestCase
{
    public enum ParameterType
    {
        Int,
        Double,
        String
    }

    public class Parameter
    {
        private ParameterType type;
        private string name;
        private string value;

        public ParameterType Type
        {
            get { return type; }
            set { type = value; }
        }
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        public string Value
        {
            get { return value; }
            set { this.value = value; }
        }
    }
}
