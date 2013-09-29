using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using TestFramework;
using TestFramework.TestCase;

namespace LibraryAutoExecutor
{
    public partial class MainForm : Form
    {
        private TestProject project;

        public TestProject Project
        {            
            set { project = value; }
        }

        public MainForm()
        {
            project = null;

            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            dgvReport.DefaultCellStyle.WrapMode = DataGridViewTriState.True;
            dgvReport.AutoGenerateColumns = false;
            TestReport testReport = project.GenerateReport();
            dgvReport.DataSource = testReport.ReportItems;

            tssCount.Text = String.Format("Count: {0}", testReport.ReportItems.Count);
        }

        private void tsbSelectAll_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < dgvReport.Rows.Count; i++)
            {
                dgvReport.Rows[i].Cells[0].Value = true;
            }  
        }

        private void tsbDeselectAll_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < dgvReport.Rows.Count; i++)
            {
                dgvReport.Rows[i].Cells[0].Value = false;
            }  
        }

        private void tsbReplace_Click(object sender, EventArgs e)
        {
            TestReport testReport = project.GenerateReport();
            for (int i = 0; i < dgvReport.Rows.Count; i++)
            {
                if (Convert.ToBoolean(dgvReport.Rows[i].Cells[0].Value))
                {
                    TestCase item = testReport.ReportItems[i].UserData as TestCase;
                    item.Replace();
                    TestCase.WriteToXml(item, item.Name);
                }
            }
        }

        private void dgvReport_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 0)
            {
                if (dgvReport.Rows[e.RowIndex].Cells[0].Value == null)
                {
                    dgvReport.Rows[e.RowIndex].Cells[0].Value = true;
                }
                else if (Convert.ToBoolean(dgvReport.Rows[e.RowIndex].Cells[0].Value))
                {
                    dgvReport.Rows[e.RowIndex].Cells[0].Value = true;
                }
                else
                {
                    dgvReport.Rows[e.RowIndex].Cells[0].Value = false;
                }
            }
        }        
    }
}
