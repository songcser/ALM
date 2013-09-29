namespace LibraryAutoExecutor
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.dgvReport = new System.Windows.Forms.DataGridView();
            this.Column3 = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.toolMain = new System.Windows.Forms.ToolStrip();
            this.tsbExport = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbSelectAll = new System.Windows.Forms.ToolStripButton();
            this.tsbDeselectAll = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbReplace = new System.Windows.Forms.ToolStripButton();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.tssCount = new System.Windows.Forms.ToolStripStatusLabel();
            ((System.ComponentModel.ISupportInitialize)(this.dgvReport)).BeginInit();
            this.toolMain.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // dgvReport
            // 
            this.dgvReport.AllowUserToResizeRows = false;
            this.dgvReport.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dgvReport.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvReport.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.DisplayedCells;
            this.dgvReport.BackgroundColor = System.Drawing.SystemColors.Window;
            this.dgvReport.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dgvReport.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dgvReport.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvReport.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column3,
            this.Column1,
            this.Column2});
            this.dgvReport.Location = new System.Drawing.Point(0, 28);
            this.dgvReport.Name = "dgvReport";
            this.dgvReport.RowHeadersVisible = false;
            this.dgvReport.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.dgvReport.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgvReport.Size = new System.Drawing.Size(844, 519);
            this.dgvReport.TabIndex = 0;
            this.dgvReport.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvReport_CellContentClick);
            // 
            // Column3
            // 
            this.Column3.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.Column3.FillWeight = 50F;
            this.Column3.HeaderText = "";
            this.Column3.Name = "Column3";
            this.Column3.Width = 50;
            // 
            // Column1
            // 
            this.Column1.DataPropertyName = "TestCaseName";
            this.Column1.FillWeight = 134.7716F;
            this.Column1.HeaderText = "Name";
            this.Column1.Name = "Column1";
            this.Column1.ReadOnly = true;
            // 
            // Column2
            // 
            this.Column2.DataPropertyName = "TestCaseResult";
            this.Column2.FillWeight = 134.7716F;
            this.Column2.HeaderText = "Result";
            this.Column2.Name = "Column2";
            this.Column2.ReadOnly = true;
            // 
            // toolMain
            // 
            this.toolMain.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbExport,
            this.toolStripSeparator1,
            this.tsbSelectAll,
            this.tsbDeselectAll,
            this.toolStripSeparator2,
            this.tsbReplace});
            this.toolMain.Location = new System.Drawing.Point(0, 0);
            this.toolMain.Name = "toolMain";
            this.toolMain.Size = new System.Drawing.Size(844, 25);
            this.toolMain.TabIndex = 0;
            this.toolMain.Text = "toolStrip1";
            // 
            // tsbExport
            // 
            this.tsbExport.Image = ((System.Drawing.Image)(resources.GetObject("tsbExport.Image")));
            this.tsbExport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbExport.Name = "tsbExport";
            this.tsbExport.Size = new System.Drawing.Size(60, 22);
            this.tsbExport.Text = "Export";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // tsbSelectAll
            // 
            this.tsbSelectAll.Image = ((System.Drawing.Image)(resources.GetObject("tsbSelectAll.Image")));
            this.tsbSelectAll.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbSelectAll.Name = "tsbSelectAll";
            this.tsbSelectAll.Size = new System.Drawing.Size(75, 22);
            this.tsbSelectAll.Text = "Select All";
            this.tsbSelectAll.Click += new System.EventHandler(this.tsbSelectAll_Click);
            // 
            // tsbDeselectAll
            // 
            this.tsbDeselectAll.Image = ((System.Drawing.Image)(resources.GetObject("tsbDeselectAll.Image")));
            this.tsbDeselectAll.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbDeselectAll.Name = "tsbDeselectAll";
            this.tsbDeselectAll.Size = new System.Drawing.Size(88, 22);
            this.tsbDeselectAll.Text = "Deselect All";
            this.tsbDeselectAll.Click += new System.EventHandler(this.tsbDeselectAll_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // tsbReplace
            // 
            this.tsbReplace.Image = ((System.Drawing.Image)(resources.GetObject("tsbReplace.Image")));
            this.tsbReplace.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbReplace.Name = "tsbReplace";
            this.tsbReplace.Size = new System.Drawing.Size(68, 22);
            this.tsbReplace.Text = "Replace";
            this.tsbReplace.Click += new System.EventHandler(this.tsbReplace_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tssCount});
            this.statusStrip1.Location = new System.Drawing.Point(0, 550);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(844, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // tssCount
            // 
            this.tssCount.Name = "tssCount";
            this.tssCount.Size = new System.Drawing.Size(46, 17);
            this.tssCount.Text = "Count: ";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(844, 572);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.toolMain);
            this.Controls.Add(this.dgvReport);
            this.Name = "MainForm";
            this.Text = "Test Report";
            this.Load += new System.EventHandler(this.MainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvReport)).EndInit();
            this.toolMain.ResumeLayout(false);
            this.toolMain.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvReport;
        private System.Windows.Forms.ToolStrip toolMain;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.DataGridViewCheckBoxColumn Column3;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.ToolStripButton tsbExport;
        private System.Windows.Forms.ToolStripButton tsbReplace;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton tsbSelectAll;
        private System.Windows.Forms.ToolStripButton tsbDeselectAll;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripStatusLabel tssCount;
    }
}

