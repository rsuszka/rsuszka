namespace RecognitionOfEmoticons
{
    partial class Form1
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
            this.tabControl_mainView = new System.Windows.Forms.TabControl();
            this.learningPage = new System.Windows.Forms.TabPage();
            this.numericUpDown_learning_epoches = new System.Windows.Forms.NumericUpDown();
            this.label_learning_epoches = new System.Windows.Forms.Label();
            this.label_learning_settings = new System.Windows.Forms.Label();
            this.label_learning_session2 = new System.Windows.Forms.Label();
            this.label_learning_session1 = new System.Windows.Forms.Label();
            this.label_learning_time2 = new System.Windows.Forms.Label();
            this.label_learning_time1 = new System.Windows.Forms.Label();
            this.progressBar_learning_progress = new System.Windows.Forms.ProgressBar();
            this.label_learning_actuallyPicture = new System.Windows.Forms.Label();
            this.pictureBox_learning_actuallyPicture = new System.Windows.Forms.PictureBox();
            this.label_learning_count = new System.Windows.Forms.Label();
            this.button_learning_start = new System.Windows.Forms.Button();
            this.button_learning_loadNetwork = new System.Windows.Forms.Button();
            this.button_learning_saveNetwork = new System.Windows.Forms.Button();
            this.programPage = new System.Windows.Forms.TabPage();
            this.label_program_outputs = new System.Windows.Forms.Label();
            this.label_program_results = new System.Windows.Forms.Label();
            this.dataGridView_program_output = new System.Windows.Forms.DataGridView();
            this.ColumnNumber = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnProbability = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.listBox_program_wages = new System.Windows.Forms.ListBox();
            this.button_program_run = new System.Windows.Forms.Button();
            this.button_program_path = new System.Windows.Forms.Button();
            this.textBox_program_path = new System.Windows.Forms.TextBox();
            this.label_program_path = new System.Windows.Forms.Label();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.tabControl_mainView.SuspendLayout();
            this.learningPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_learning_epoches)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_learning_actuallyPicture)).BeginInit();
            this.programPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_program_output)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl_mainView
            // 
            this.tabControl_mainView.Controls.Add(this.learningPage);
            this.tabControl_mainView.Controls.Add(this.programPage);
            this.tabControl_mainView.Location = new System.Drawing.Point(12, 12);
            this.tabControl_mainView.Name = "tabControl_mainView";
            this.tabControl_mainView.SelectedIndex = 0;
            this.tabControl_mainView.Size = new System.Drawing.Size(813, 397);
            this.tabControl_mainView.TabIndex = 0;
            // 
            // learningPage
            // 
            this.learningPage.Controls.Add(this.numericUpDown_learning_epoches);
            this.learningPage.Controls.Add(this.label_learning_epoches);
            this.learningPage.Controls.Add(this.label_learning_settings);
            this.learningPage.Controls.Add(this.label_learning_session2);
            this.learningPage.Controls.Add(this.label_learning_session1);
            this.learningPage.Controls.Add(this.label_learning_time2);
            this.learningPage.Controls.Add(this.label_learning_time1);
            this.learningPage.Controls.Add(this.progressBar_learning_progress);
            this.learningPage.Controls.Add(this.label_learning_actuallyPicture);
            this.learningPage.Controls.Add(this.pictureBox_learning_actuallyPicture);
            this.learningPage.Controls.Add(this.label_learning_count);
            this.learningPage.Controls.Add(this.button_learning_start);
            this.learningPage.Controls.Add(this.button_learning_loadNetwork);
            this.learningPage.Controls.Add(this.button_learning_saveNetwork);
            this.learningPage.Location = new System.Drawing.Point(4, 25);
            this.learningPage.Name = "learningPage";
            this.learningPage.Padding = new System.Windows.Forms.Padding(3);
            this.learningPage.Size = new System.Drawing.Size(805, 368);
            this.learningPage.TabIndex = 0;
            this.learningPage.Text = "Learning";
            this.learningPage.UseVisualStyleBackColor = true;
            // 
            // numericUpDown_learning_epoches
            // 
            this.numericUpDown_learning_epoches.Location = new System.Drawing.Point(279, 156);
            this.numericUpDown_learning_epoches.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numericUpDown_learning_epoches.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown_learning_epoches.Name = "numericUpDown_learning_epoches";
            this.numericUpDown_learning_epoches.Size = new System.Drawing.Size(68, 22);
            this.numericUpDown_learning_epoches.TabIndex = 23;
            this.numericUpDown_learning_epoches.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label_learning_epoches
            // 
            this.label_learning_epoches.AutoSize = true;
            this.label_learning_epoches.Location = new System.Drawing.Point(210, 158);
            this.label_learning_epoches.Name = "label_learning_epoches";
            this.label_learning_epoches.Size = new System.Drawing.Size(59, 17);
            this.label_learning_epoches.TabIndex = 22;
            this.label_learning_epoches.Text = "Epochs:";
            // 
            // label_learning_settings
            // 
            this.label_learning_settings.AutoSize = true;
            this.label_learning_settings.Location = new System.Drawing.Point(206, 129);
            this.label_learning_settings.Name = "label_learning_settings";
            this.label_learning_settings.Size = new System.Drawing.Size(63, 17);
            this.label_learning_settings.TabIndex = 21;
            this.label_learning_settings.Text = "Settings:";
            // 
            // label_learning_session2
            // 
            this.label_learning_session2.AutoSize = true;
            this.label_learning_session2.Location = new System.Drawing.Point(81, 280);
            this.label_learning_session2.Name = "label_learning_session2";
            this.label_learning_session2.Size = new System.Drawing.Size(16, 17);
            this.label_learning_session2.TabIndex = 20;
            this.label_learning_session2.Text = "0";
            // 
            // label_learning_session1
            // 
            this.label_learning_session1.AutoSize = true;
            this.label_learning_session1.Location = new System.Drawing.Point(23, 280);
            this.label_learning_session1.Name = "label_learning_session1";
            this.label_learning_session1.Size = new System.Drawing.Size(52, 17);
            this.label_learning_session1.TabIndex = 19;
            this.label_learning_session1.Text = "Epoch:";
            // 
            // label_learning_time2
            // 
            this.label_learning_time2.AutoSize = true;
            this.label_learning_time2.Location = new System.Drawing.Point(81, 301);
            this.label_learning_time2.Name = "label_learning_time2";
            this.label_learning_time2.Size = new System.Drawing.Size(16, 17);
            this.label_learning_time2.TabIndex = 18;
            this.label_learning_time2.Text = "0";
            // 
            // label_learning_time1
            // 
            this.label_learning_time1.AutoSize = true;
            this.label_learning_time1.Location = new System.Drawing.Point(32, 301);
            this.label_learning_time1.Name = "label_learning_time1";
            this.label_learning_time1.Size = new System.Drawing.Size(43, 17);
            this.label_learning_time1.TabIndex = 17;
            this.label_learning_time1.Text = "Time:";
            // 
            // progressBar_learning_progress
            // 
            this.progressBar_learning_progress.Location = new System.Drawing.Point(16, 236);
            this.progressBar_learning_progress.Name = "progressBar_learning_progress";
            this.progressBar_learning_progress.Size = new System.Drawing.Size(770, 23);
            this.progressBar_learning_progress.TabIndex = 16;
            // 
            // label_learning_actuallyPicture
            // 
            this.label_learning_actuallyPicture.AutoSize = true;
            this.label_learning_actuallyPicture.Location = new System.Drawing.Point(13, 129);
            this.label_learning_actuallyPicture.Name = "label_learning_actuallyPicture";
            this.label_learning_actuallyPicture.Size = new System.Drawing.Size(142, 17);
            this.label_learning_actuallyPicture.TabIndex = 15;
            this.label_learning_actuallyPicture.Text = "Actually Picture View:";
            // 
            // pictureBox_learning_actuallyPicture
            // 
            this.pictureBox_learning_actuallyPicture.Location = new System.Drawing.Point(16, 165);
            this.pictureBox_learning_actuallyPicture.Name = "pictureBox_learning_actuallyPicture";
            this.pictureBox_learning_actuallyPicture.Size = new System.Drawing.Size(20, 10);
            this.pictureBox_learning_actuallyPicture.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_learning_actuallyPicture.TabIndex = 14;
            this.pictureBox_learning_actuallyPicture.TabStop = false;
            // 
            // label_learning_count
            // 
            this.label_learning_count.AutoSize = true;
            this.label_learning_count.Location = new System.Drawing.Point(72, 158);
            this.label_learning_count.Name = "label_learning_count";
            this.label_learning_count.Size = new System.Drawing.Size(16, 17);
            this.label_learning_count.TabIndex = 13;
            this.label_learning_count.Text = "0";
            // 
            // button_learning_start
            // 
            this.button_learning_start.Location = new System.Drawing.Point(6, 10);
            this.button_learning_start.Name = "button_learning_start";
            this.button_learning_start.Size = new System.Drawing.Size(662, 78);
            this.button_learning_start.TabIndex = 12;
            this.button_learning_start.Text = "START LEARNING";
            this.button_learning_start.UseVisualStyleBackColor = true;
            this.button_learning_start.Click += new System.EventHandler(this.button1_Click);
            // 
            // button_learning_loadNetwork
            // 
            this.button_learning_loadNetwork.Location = new System.Drawing.Point(674, 10);
            this.button_learning_loadNetwork.Name = "button_learning_loadNetwork";
            this.button_learning_loadNetwork.Size = new System.Drawing.Size(112, 29);
            this.button_learning_loadNetwork.TabIndex = 11;
            this.button_learning_loadNetwork.Text = "Load Network";
            this.button_learning_loadNetwork.UseVisualStyleBackColor = true;
            this.button_learning_loadNetwork.Click += new System.EventHandler(this.button_load_learning_Click);
            // 
            // button_learning_saveNetwork
            // 
            this.button_learning_saveNetwork.Location = new System.Drawing.Point(674, 59);
            this.button_learning_saveNetwork.Name = "button_learning_saveNetwork";
            this.button_learning_saveNetwork.Size = new System.Drawing.Size(112, 29);
            this.button_learning_saveNetwork.TabIndex = 10;
            this.button_learning_saveNetwork.Text = "Save Network";
            this.button_learning_saveNetwork.UseVisualStyleBackColor = true;
            this.button_learning_saveNetwork.Click += new System.EventHandler(this.button_save_learning_Click);
            // 
            // programPage
            // 
            this.programPage.Controls.Add(this.label_program_outputs);
            this.programPage.Controls.Add(this.label_program_results);
            this.programPage.Controls.Add(this.dataGridView_program_output);
            this.programPage.Controls.Add(this.listBox_program_wages);
            this.programPage.Controls.Add(this.button_program_run);
            this.programPage.Controls.Add(this.button_program_path);
            this.programPage.Controls.Add(this.textBox_program_path);
            this.programPage.Controls.Add(this.label_program_path);
            this.programPage.Location = new System.Drawing.Point(4, 25);
            this.programPage.Name = "programPage";
            this.programPage.Padding = new System.Windows.Forms.Padding(3);
            this.programPage.Size = new System.Drawing.Size(805, 368);
            this.programPage.TabIndex = 1;
            this.programPage.Text = "Program";
            this.programPage.UseVisualStyleBackColor = true;
            // 
            // label_program_outputs
            // 
            this.label_program_outputs.AutoSize = true;
            this.label_program_outputs.Location = new System.Drawing.Point(514, 134);
            this.label_program_outputs.Name = "label_program_outputs";
            this.label_program_outputs.Size = new System.Drawing.Size(117, 17);
            this.label_program_outputs.TabIndex = 12;
            this.label_program_outputs.Text = "Network Outputs:";
            // 
            // label_program_results
            // 
            this.label_program_results.AutoSize = true;
            this.label_program_results.Location = new System.Drawing.Point(9, 134);
            this.label_program_results.Name = "label_program_results";
            this.label_program_results.Size = new System.Drawing.Size(117, 17);
            this.label_program_results.TabIndex = 11;
            this.label_program_results.Text = "Program Results:";
            // 
            // dataGridView_program_output
            // 
            this.dataGridView_program_output.AllowUserToAddRows = false;
            this.dataGridView_program_output.AllowUserToDeleteRows = false;
            this.dataGridView_program_output.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_program_output.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumnNumber,
            this.ColumnName,
            this.ColumnProbability});
            this.dataGridView_program_output.Location = new System.Drawing.Point(12, 157);
            this.dataGridView_program_output.Name = "dataGridView_program_output";
            this.dataGridView_program_output.ReadOnly = true;
            this.dataGridView_program_output.RowTemplate.Height = 24;
            this.dataGridView_program_output.Size = new System.Drawing.Size(499, 148);
            this.dataGridView_program_output.TabIndex = 10;
            // 
            // ColumnNumber
            // 
            this.ColumnNumber.HeaderText = "Number";
            this.ColumnNumber.Name = "ColumnNumber";
            this.ColumnNumber.ReadOnly = true;
            this.ColumnNumber.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.ColumnNumber.Width = 70;
            // 
            // ColumnName
            // 
            this.ColumnName.HeaderText = "Name";
            this.ColumnName.Name = "ColumnName";
            this.ColumnName.ReadOnly = true;
            this.ColumnName.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.ColumnName.Width = 220;
            // 
            // ColumnProbability
            // 
            this.ColumnProbability.HeaderText = "Probability";
            this.ColumnProbability.Name = "ColumnProbability";
            this.ColumnProbability.ReadOnly = true;
            this.ColumnProbability.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.ColumnProbability.Width = 165;
            // 
            // listBox_program_wages
            // 
            this.listBox_program_wages.FormattingEnabled = true;
            this.listBox_program_wages.ItemHeight = 16;
            this.listBox_program_wages.Location = new System.Drawing.Point(517, 157);
            this.listBox_program_wages.Name = "listBox_program_wages";
            this.listBox_program_wages.Size = new System.Drawing.Size(271, 148);
            this.listBox_program_wages.TabIndex = 9;
            // 
            // button_program_run
            // 
            this.button_program_run.Location = new System.Drawing.Point(676, 54);
            this.button_program_run.Name = "button_program_run";
            this.button_program_run.Size = new System.Drawing.Size(112, 29);
            this.button_program_run.TabIndex = 3;
            this.button_program_run.Text = "Run";
            this.button_program_run.UseVisualStyleBackColor = true;
            this.button_program_run.Click += new System.EventHandler(this.button_run_Click);
            // 
            // button_program_path
            // 
            this.button_program_path.Location = new System.Drawing.Point(558, 54);
            this.button_program_path.Name = "button_program_path";
            this.button_program_path.Size = new System.Drawing.Size(112, 29);
            this.button_program_path.TabIndex = 2;
            this.button_program_path.Text = "Set Path";
            this.button_program_path.UseVisualStyleBackColor = true;
            this.button_program_path.Click += new System.EventHandler(this.button_path_Click);
            // 
            // textBox_program_path
            // 
            this.textBox_program_path.Location = new System.Drawing.Point(56, 26);
            this.textBox_program_path.Name = "textBox_program_path";
            this.textBox_program_path.ReadOnly = true;
            this.textBox_program_path.Size = new System.Drawing.Size(732, 22);
            this.textBox_program_path.TabIndex = 1;
            // 
            // label_program_path
            // 
            this.label_program_path.AutoSize = true;
            this.label_program_path.Location = new System.Drawing.Point(9, 29);
            this.label_program_path.Name = "label_program_path";
            this.label_program_path.Size = new System.Drawing.Size(41, 17);
            this.label_program_path.TabIndex = 0;
            this.label_program_path.Text = "Path:";
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(838, 420);
            this.Controls.Add(this.tabControl_mainView);
            this.Name = "Form1";
            this.Text = "Recognition Of Emoticons";
            this.tabControl_mainView.ResumeLayout(false);
            this.learningPage.ResumeLayout(false);
            this.learningPage.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_learning_epoches)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_learning_actuallyPicture)).EndInit();
            this.programPage.ResumeLayout(false);
            this.programPage.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_program_output)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl_mainView;
        private System.Windows.Forms.TabPage learningPage;
        private System.Windows.Forms.TabPage programPage;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Label label_program_path;
        private System.Windows.Forms.TextBox textBox_program_path;
        private System.Windows.Forms.Button button_program_run;
        private System.Windows.Forms.Button button_program_path;
        private System.Windows.Forms.ListBox listBox_program_wages;
        private System.Windows.Forms.Button button_learning_saveNetwork;
        private System.Windows.Forms.Button button_learning_loadNetwork;
        private System.Windows.Forms.Button button_learning_start;
        private System.Windows.Forms.Label label_learning_count;
        private System.Windows.Forms.PictureBox pictureBox_learning_actuallyPicture;
        private System.Windows.Forms.Label label_learning_actuallyPicture;
        private System.Windows.Forms.ProgressBar progressBar_learning_progress;
        private System.Windows.Forms.Label label_learning_time2;
        private System.Windows.Forms.Label label_learning_time1;
        private System.Windows.Forms.Label label_learning_session2;
        private System.Windows.Forms.Label label_learning_session1;
        private System.Windows.Forms.DataGridView dataGridView_program_output;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnNumber;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnName;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnProbability;
        private System.Windows.Forms.Label label_program_outputs;
        private System.Windows.Forms.Label label_program_results;
        private System.Windows.Forms.NumericUpDown numericUpDown_learning_epoches;
        private System.Windows.Forms.Label label_learning_epoches;
        private System.Windows.Forms.Label label_learning_settings;
    }
}

