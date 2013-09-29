using System;
using System.Collections.Generic;
using System.Windows.Forms;
using TestFramework;

namespace LibraryAutoExecutor
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            string argLibraryPath = null;
            string argTestCasePath = null;
            string argShowReport = null;

            if (args.Length > 1)
            {
                argLibraryPath = args[0];
                argTestCasePath = args[1];

                if (args.Length == 3)
                {
                    argShowReport = args[2];
                }
            }
            else
            {
                return;
            }

            TestProject project = new TestProject();
            project.TestObject = argLibraryPath;
            project.TestDataSource = argTestCasePath;

            project.Execute();

            if (argShowReport != null && argShowReport.Equals("report", StringComparison.CurrentCultureIgnoreCase))
            {                
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);

                MainForm mainForm = new MainForm();
                mainForm.Project = project;
                Application.Run(mainForm);
            }
        }
    }
}
