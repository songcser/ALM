using System;
using System.Collections.Generic;
using System.Text;

namespace TestFramework.TestCase
{
    public enum TestResultCode
    {
        Right,
        Wrong,
        Exception,
    }

    public class TestResult
    {
        private string errorMessage;
        private TestResultCode resultCode;

        public string ErrorMessage
        {
            get { return errorMessage; }
            set { errorMessage = value; }
        }

        public TestResultCode ResultCode
        {
            get { return resultCode; }
            set { resultCode = value; }
        }

        public TestResult()
        {
            errorMessage = "";
            resultCode = TestResultCode.Wrong;
        }
    }
}