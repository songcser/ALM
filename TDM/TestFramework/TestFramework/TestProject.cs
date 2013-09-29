using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml.Serialization;
using TestFramework.TestCase;

namespace TestFramework
{
    public class TestProject
    {        
        private string testObject;
        private string testDataSource;
        private TestCaseCollection testCases;

        public TestProject()
        {
            testCases = new TestCaseCollection();
        }

        public TestCaseCollection TestCases
        {
            get { return testCases; }
        }

        public string TestDataSource
        {
            get { return testDataSource; }
            set { testDataSource = value; }
        }

               
        public string TestObject
        {
            get { return testObject; }
            set { testObject = value; }
        }
            
        public void Execute()
        {
            LoadTestCase();

            foreach (TestFramework.TestCase.TestCase item in testCases)
            {
                item.Execute(testObject);
            }                        
        }

        private void LoadTestCase()
        {
            List<string> testCaseFileList = new List<string>();
            GetFiles(testDataSource, "*.xml", testCaseFileList);

            foreach (string item in testCaseFileList)
            {
                try
                {
                    TestCase.TestCase testCase = TestCase.TestCase.ReadFromXml(item);
                    testCase.Name = item;

                    testCases.Add(testCase);
                }
                catch (Exception)
                { }
            }
        }

        public TestReport GenerateReport()
        {
            TestReport testReport = new TestReport();

            foreach (TestCase.TestCase item in testCases)
            {
                if (item.Result.ResultCode != TestResultCode.Right)
                {
                    TestReportItem reportItem = new TestReportItem();
                    reportItem.TestCaseName = item.Name;
                    reportItem.TestCaseResult = item.Result.ErrorMessage;
                    reportItem.UserData = item;

                    testReport.ReportItems.Add(reportItem);
                }
            }

            return testReport;
        }

        private void GetFiles(string folderPath, string extension, List<string> fileList)
        {               
            string[] files = Directory.GetFiles(folderPath, extension);
            int count = files != null ? files.Length : 0;
            for (int idx = 0; idx < count; idx++)
            {
                fileList.Add(files[idx]);
            }

            DirectoryInfo directoryInfo = new DirectoryInfo(folderPath);
            foreach (DirectoryInfo subDirectoryInfo in directoryInfo.GetDirectories())
            {
                GetFiles(subDirectoryInfo.FullName, extension, fileList);
            }            
        }        
    }
}
