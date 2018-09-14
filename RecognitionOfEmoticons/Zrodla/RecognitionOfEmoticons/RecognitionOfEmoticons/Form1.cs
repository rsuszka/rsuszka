using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace RecognitionOfEmoticons
{
    public partial class Form1 : Form
    {
        private string inputDataPath; //variable that stores path to input data
        private NeuronNetwork neuronNetwork; //variable that stores natural network
        private int learningEpoches = 1000; //variable that stores number of learning epochs

        public Form1() //constructor
        {
            InitializeComponent();

            this.neuronNetwork = new NeuronNetwork();
            this.neuronNetwork.CreateNetwork(200);
            numericUpDown_learning_epoches.Value = this.learningEpoches;
        }
        private void button_path_Click(object sender, EventArgs e) //method that it is called after pressing the button ‘Set Path’
        {
            openFileDialog.ShowDialog();
            string path = openFileDialog.FileName;
            textBox_program_path.Text = path;
            this.inputDataPath = path;
        }
        private void button_run_Click(object sender, EventArgs e) //method that it is called after pressing the button ‘Run’
        {
            if (this.inputDataPath != null)
            {
                MyPicture inputBitmap = new MyPicture(this.inputDataPath);
                inputBitmap.Resize(100, 100);
                inputBitmap.CropImage(20, 55, 65, 25);
                inputBitmap.Resize(31, 16);
                inputBitmap.SobellFilter();
                inputBitmap.InvertColors();
                inputBitmap.CorrectCollors();
                inputBitmap.Resize(20, 10);

                int[] inputData = inputBitmap.ToTable();
                List<double> output = this.neuronNetwork.RunNetwork(inputData);
                string[] classNames = this.neuronNetwork.ClassNames;
                int counter = 1;

                //show outputs
                listBox_program_wages.Items.Clear();
                dataGridView_program_output.Rows.Clear();
                foreach (double element in output)
                {
                    listBox_program_wages.Items.Add(element);
                    DataGridViewRow row = new DataGridViewRow();
                    row.Resizable = DataGridViewTriState.False;
                    if (element > 0.65)
                        row.DefaultCellStyle.BackColor = Color.Green;
                    else
                        row.DefaultCellStyle.BackColor = Color.Red;
                    row.Cells.Add(new DataGridViewTextBoxCell { Value = counter + "." });
                    row.Cells.Add(new DataGridViewTextBoxCell { Value = classNames[counter - 1] });
                    row.Cells.Add(new DataGridViewTextBoxCell { Value = Math.Round(element * 100, 2) + "%" });
                    dataGridView_program_output.Rows.Add(row);
                    counter++;
                }
                MessageBox.Show("Finished", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);

            }
            else
            {
                MessageBox.Show("The path to the file was not specified", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void button_save_learning_Click(object sender, EventArgs e) //method that it is called after pressing the button ‘Save Network’
        {
            this.neuronNetwork.SaveNetworkToFile();
            MessageBox.Show("Network saved successfully", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
        private void button_load_learning_Click(object sender, EventArgs e) //method that it is called after pressing the button ‘Load Network’
        {
            openFileDialog.Multiselect = false;
            openFileDialog.ShowDialog();
            string path = openFileDialog.FileName;
            this.neuronNetwork.LoadNetworkFromFile(path);
            MessageBox.Show("Network loaded successfully", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
        private void button1_Click_Task(MyPicture inputBitmap, int[] randomTable, string[] filesData, int i)
        {
            inputBitmap.Resize(100, 100);
            inputBitmap.CropImage(20, 55, 65, 25);
            inputBitmap.Resize(31, 16);
            inputBitmap.SobellFilter();
            inputBitmap.InvertColors();
            inputBitmap.CorrectCollors();
            inputBitmap.Resize(20, 10);

            int[] inputData = inputBitmap.ToTable();
            string[] correctOutputString = filesData[randomTable[i]].Split(' ');
            int[] correctOutputInt = new int[correctOutputString.Length];
            for (int j = 0; j < correctOutputString.Length; j++)
            {
                correctOutputInt[j] = int.Parse(correctOutputString[j]);
            }
            this.neuronNetwork.LearnNetwork(inputData, correctOutputInt);
        }
        private void button1_Click(object sender, EventArgs e) //method that it is called after pressing the button ‘START LEARNING’
        {
            this.learningEpoches = (int)numericUpDown_learning_epoches.Value;

            MessageBox.Show("Give input files", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
            openFileDialog.Multiselect = true;
            openFileDialog.ShowDialog();
            string[] inputFilesPath = openFileDialog.FileNames;
            MessageBox.Show("Give the expected outputs", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
            openFileDialog.Multiselect = false;
            openFileDialog.ShowDialog();
            string correctOutputFile = openFileDialog.FileName;

            string[] filesData = File.ReadAllLines(correctOutputFile);

            //progressBar
            progressBar_learning_progress.Maximum = filesData.Length;

            //randomize input files
            int[] randomTable = new int[inputFilesPath.Length];
            for (int i = 0; i < randomTable.Length; i++)
            {
                randomTable[i] = i;
            }
            Random n = new Random(Environment.TickCount);
            for (int i = 0; i < (randomTable.Length) * 2; i++)
            {
                int x = n.Next(0, randomTable.Length - 1);
                int y = n.Next(0, randomTable.Length - 1);
                int tmp = randomTable[x];
                randomTable[x] = randomTable[y];
                randomTable[y] = tmp;
            }

            //calculate start time
            DateTime timeStart = DateTime.Now;

            for (int ii = 0; ii < this.learningEpoches; ii++)
            {
                label_learning_session2.Text = (ii + 1).ToString();
                progressBar_learning_progress.Value = 0;
               
                for (int i = 0; i < inputFilesPath.Length; i++)
                {
                    MyPicture inputBitmap = new MyPicture(inputFilesPath[randomTable[i]]);

                    Task task = Task.Factory.StartNew(() => this.button1_Click_Task(inputBitmap, randomTable, filesData, i));
                    task.Wait();

                    label_learning_count.Text = (i + 1).ToString();
                    pictureBox_learning_actuallyPicture.Image = inputBitmap.InputBitmap;
                    label_learning_count.Refresh();
                    pictureBox_learning_actuallyPicture.Refresh();
                    progressBar_learning_progress.Value++;
                    TimeSpan timeSpan = DateTime.Now - timeStart;
                    label_learning_time2.Text = timeSpan.ToString();
                }
            }

            MessageBox.Show("Learning successful!", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}