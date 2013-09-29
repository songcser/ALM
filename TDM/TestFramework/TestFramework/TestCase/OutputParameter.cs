using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;

namespace TestFramework.TestCase
{

    public class OutputParameter : Parameter
    {
        private string tolerance;
        private string actualValue;

        public string Tolerance
        {
            get { return tolerance; }
            set { tolerance = value; }
        }

        [XmlIgnore]
        public string ActualValue
        {
            get { return actualValue; }
            set { actualValue = value; }
        }

        public bool Compare()
        {
            switch (this.Type)
            {
                case (ParameterType.Double):
                    double Dupper, Dlower = 0;
                    Dupper = double.Parse(this.Value) + double.Parse(tolerance);
                    Dlower = double.Parse(this.Value) - double.Parse(tolerance);

                    if (double.Parse(actualValue) >= Dlower && double.Parse(actualValue) <= Dupper)
                        return true;
                    else
                        return false;

                case (ParameterType.Int):
                    int Iupper, Ilower = 0;
                    Iupper = int.Parse(this.Value) + int.Parse(tolerance);
                    Ilower = int.Parse(this.Value) - int.Parse(tolerance);

                    if (double.Parse(actualValue) >= Ilower && double.Parse(actualValue) <= Iupper)
                        return true;
                    else
                        return false;

                case (ParameterType.String):
                    if (actualValue == this.Value)
                        return true;
                    else
                        return false;
                default:
                    return false;
            }
        }
    }
}
