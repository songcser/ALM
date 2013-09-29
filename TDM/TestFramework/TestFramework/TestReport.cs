using System;
using System.Collections.Generic;
using System.Text;

namespace TestFramework
{
    public class TestReportItem
    {
        private string testCaseName;
        private string testCaseResult;
        private object userData;

        public string TestCaseName
        {
            get { return testCaseName; }
            set { testCaseName = value; }
        }

        public string TestCaseResult
        {
            get { return testCaseResult; }
            set { testCaseResult = value; }
        }

        public object UserData
        {
            get { return userData; }
            set { userData = value; }
        }

    }

    public class TestReport
    {
        private List<TestReportItem> reportItems;

        public List<TestReportItem> ReportItems
        {
            get { return reportItems; }            
        }

        public TestReport()
        {
            reportItems = new List<TestReportItem>();
        }
    }
}
