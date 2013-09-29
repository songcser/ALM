using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Text.RegularExpressions;
using System.IO;
using System.Xml.Serialization;

namespace TestFramework.TestCase
{
    public class TestCase
    {
        private string name;
        private string className;
        private string methodName;
        private InputParameterCollection constructorParams;
        private InputParameterCollection inputParams;
        private OutputParameterCollection outputParams;
        private TestResult result;

        public TestCase()
        {
            constructorParams = new InputParameterCollection();
            inputParams = new InputParameterCollection();
            outputParams = new OutputParameterCollection();
            result = new TestResult();
        }

        [XmlIgnore]
        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string ClassName
        {
            get { return className; }
            set { className = value; }
        }

        public string MethodName
        {
            get { return methodName; }
            set { methodName = value; }
        }

        public InputParameterCollection ConstructorParams
        {
            get { return constructorParams; }
        }

        public InputParameterCollection InputParams
        {
            get { return inputParams; }
        }

        public OutputParameterCollection OutputParams
        {
            get { return outputParams; }
        }

        [XmlIgnore]
        public TestResult Result
        {
            get { return result; }
            set { result = value; }
        }

        public void Execute(string assembly)
        {
            try
            {
                Assembly myassembly = Assembly.LoadFrom(assembly);

                Type typearr = myassembly.GetType(className);

                Object obj;
                if (constructorParams.Count == 0)
                    obj = Activator.CreateInstance(typearr);
                else
                    obj = Activator.CreateInstance(typearr, this.constructorParams.ToParamArray());

                List<object> paramList = new List<object>();
                paramList.AddRange(this.inputParams.ToParamArray());
                if (this.outputParams.Count == 0)
                {
                    object[] paramArray = paramList.ToArray();
                    typearr.InvokeMember(methodName, BindingFlags.InvokeMethod, null, obj, paramArray);
                }
                else
                {
                    paramList.AddRange(this.outputParams.ToParamArray());
                    object[] paramArray = paramList.ToArray();

                    typearr.InvokeMember(methodName, BindingFlags.InvokeMethod, null, obj, paramArray);
                    for (int i = 0; i < outputParams.Count; i++)
                    {
                        outputParams[i].ActualValue = paramArray[paramList.Count - outputParams.Count + i].ToString();
                    }
                }

                for (int i = 0; i < outputParams.Count; i++)
                {
                    if (outputParams[i].Compare())
                    {
                        result.ResultCode = TestResultCode.Right;
                    }
                    else
                    {
                        result.ResultCode = TestResultCode.Wrong;
                        List<String> errorMessage=new List<String>();
                        foreach (OutputParameter item in outputParams)
                        {
                            errorMessage.Add(string.Format("{0}: Actual Value = {1}; Expected Value = {2}; Tolerance = {3}",
                                item.Name, item.ActualValue, item.Value, item.Tolerance));
                        }

                        result.ErrorMessage = string.Join("\r\n", errorMessage);
                    }
                }
            }
            catch (Exception ex)
            {
                if (ex.InnerException != null)
                {                   
                    result.ErrorMessage = ex.InnerException.Message;
                }
                else
                {
                    result.ErrorMessage = ex.Message;
                }

                result.ResultCode = TestResultCode.Exception;
            }
        }

        public void Replace()
        {
            if (result.ResultCode == TestResultCode.Wrong)
            {
                foreach (OutputParameter item in outputParams)
                {
                    item.Value = item.ActualValue;
                }
            }
        }

        public static TestCase ReadFromXml(string filename)
        {      
            FileStream fileStream = new FileStream(filename, FileMode.Open);
            XmlSerializer xs = new XmlSerializer(typeof(TestCase));
            TestCase testCase = xs.Deserialize(fileStream) as TestCase;
            fileStream.Flush();
            fileStream.Close();
            return testCase;
        }

        public static void WriteToXml(TestCase testCase, string filename)
        {
            FileStream fileStream = File.Create(filename);
            XmlSerializer xs = new XmlSerializer(typeof(TestCase));
            xs.Serialize(fileStream, testCase);
            fileStream.Flush();
            fileStream.Close();
        }
    }
}
