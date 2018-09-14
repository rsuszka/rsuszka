using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace RecognitionOfEmoticons
{
    class NeuronNetwork
    {
        private List<int> inputLayer; //list that stores network inputs
        private List<Neuron> hiddenLayerFirst; //list that stores network neurons from first hidden layer
        private List<Neuron> hiddenLayerSecond; //list that stores network neurons from second hidden layer
        private List<Neuron> outputLayer; //list that stores network neurons from output layer
        private int numberOfNeuronsInInputLayer = 0; //variable that stores number of neurons in input layer
        private int numberOfNeuronsInHiddenLayerFirst = 40; //variable that stores number of neurons in first hidden layer
        private int numberOfNeuronsInHiddenLayerSecond = 15; //variable that stores number of neurons in second hidden layer
        private int numberOfNeuronsInOutputLayer = 5; //variable that stores number of neurons in output layer
        private double eta = 0.2; //variable that stores eta parameter
        private double alfa = 0.6; //variable that stores alfa parameter
        private string[] classNames; //table that stores names of output classes

        public NeuronNetwork() //constructor
        {
            this.inputLayer = new List<int>();
            this.hiddenLayerFirst = new List<Neuron>();
            this.hiddenLayerSecond = new List<Neuron>();
            this.outputLayer = new List<Neuron>();

            //class names
            this.classNames = new string[5];
            classNames[0] = "Smile";
            classNames[1] = "Sadness";
            classNames[2] = "Tongue";
            classNames[3] = "Surprise";
            classNames[4] = "Strong smile";
        }
        public void CreateNetwork(int neuronsInInputLayer) //method that creates natural network
        {
            //create input layer
            this.numberOfNeuronsInInputLayer = neuronsInInputLayer;

            //create first hidden layer
            for (int i = 0; i < this.numberOfNeuronsInHiddenLayerFirst; i++)
            {
                Neuron neuron = new Neuron();
                neuron.AddInputs(this.numberOfNeuronsInInputLayer);
                this.hiddenLayerFirst.Add(neuron);
            }

            //create second hidden layer
            for (int i = 0; i < this.numberOfNeuronsInHiddenLayerSecond; i++)
            {
                Neuron neuron = new Neuron();
                neuron.AddInputs(this.numberOfNeuronsInHiddenLayerFirst);
                this.hiddenLayerSecond.Add(neuron);
            }

            //create output layer
            for (int i = 0; i < this.numberOfNeuronsInOutputLayer; i++)
            {
                Neuron neuron = new Neuron();
                neuron.AddInputs(this.numberOfNeuronsInHiddenLayerSecond);
                this.outputLayer.Add(neuron);
            }
        }
        public List<double> RunNetwork(int[] inputData) //method that returns outputs of the natural network based on given inputs as argument
        {
            //copy data to input layer
            this.inputLayer.Clear();
            for (int i = 0; i < this.numberOfNeuronsInInputLayer; i++)
            {
                this.inputLayer.Add(inputData[i]);
            }

            //calculate outputs first hidden layer
            List<double> hiddenLayerFirstOutputs = new List<double>();
            foreach (Neuron neuron in this.hiddenLayerFirst)
            {
                double output = neuron.GetOutput(this.inputLayer);
                hiddenLayerFirstOutputs.Add(output);
            }

            //calculate outputs second hidden layer
            List<double> hiddenLayerSecondOutputs = new List<double>();
            foreach (Neuron neuron in this.hiddenLayerSecond)
            {
                double output = neuron.GetOutput(hiddenLayerFirstOutputs);
                hiddenLayerSecondOutputs.Add(output);
            }

            //calculate outputs of network
            List<double> outputLayerOutputs = new List<double>();
            foreach (Neuron neuron in this.outputLayer)
            {
                double output = neuron.GetOutput(hiddenLayerSecondOutputs);
                outputLayerOutputs.Add(output);
            }

            return outputLayerOutputs;
        }
        public void LearnNetwork(int[] inputData, int[] correctOutputData) //method that learn natural network
        {
            int tmpCounter = 0;
            double ERMS = 1.0;

            while (ERMS > 0.2)
            {
                //process signal via the network
                List<double> outputData = this.RunNetwork(inputData);

                //calculate output delta
                List<double> delta = new List<double>(correctOutputData.Length);
                for (int i = 0; i < correctOutputData.Length; i++)
                {
                    delta.Add((double)correctOutputData[i] - outputData[i]);
                }

                //calculate delta in output layer
                for (int i = 0; i < this.numberOfNeuronsInOutputLayer; i++)
                {
                    Neuron neuron = this.outputLayer[i];
                    neuron.Delta = (((double)correctOutputData[i] - neuron.Value) * neuron.Value * (1.0 - neuron.Value) * neuron.Beta); //dodanie bety do wzoru
                }

                //calculate delta in second hidden layer
                for (int i = 0; i < this.numberOfNeuronsInHiddenLayerSecond; i++)
                {
                    Neuron neuron = this.hiddenLayerSecond[i];
                    neuron.Delta = 0.0;
                    for (int j = 0; j < this.numberOfNeuronsInOutputLayer; j++)
                    {
                        neuron.Delta += (neuron.Value * (1.0 - neuron.Value) * this.outputLayer[j].Delta * this.outputLayer[j].GetWeight(i) * this.outputLayer[j].Beta);
                    }
                }

                //calculate delta in first hidden layer
                for (int i = 0; i < this.numberOfNeuronsInHiddenLayerFirst; i++)
                {
                    Neuron neuron = this.hiddenLayerFirst[i];
                    neuron.Delta = 0.0;
                    for (int j = 0; j < this.numberOfNeuronsInHiddenLayerSecond; j++)
                    {
                        neuron.Delta += (neuron.Value * (1.0 - neuron.Value) * this.hiddenLayerSecond[j].Delta * this.hiddenLayerSecond[j].GetWeight(i) * this.hiddenLayerSecond[j].Beta);
                    }
                }

                //correction weights in first hidden layer
                for (int i = 0; i < this.numberOfNeuronsInHiddenLayerFirst; i++)
                {
                    Neuron neuron = this.hiddenLayerFirst[i];
                    for (int j = 0; j < this.numberOfNeuronsInInputLayer; j++)
                    {
                        double newWeight, actuallyWeight, oldWeight;
                        actuallyWeight = neuron.GetWeight(j);
                        oldWeight = neuron.GetOldWeight(j);
                        newWeight = ((this.eta * neuron.Delta * (double)this.inputLayer[j]) + (this.alfa * (actuallyWeight - oldWeight)));
                        neuron.ChangeInputWeight(j, (actuallyWeight + newWeight));

                    }
                }

                //correction weights in second hidden layer
                for (int i = 0; i < this.numberOfNeuronsInHiddenLayerSecond; i++)
                {
                    Neuron neuron = this.hiddenLayerSecond[i];
                    for (int j = 0; j < this.numberOfNeuronsInHiddenLayerFirst; j++)
                    {
                        double newWeight, actuallyWeight, oldWeight;
                        actuallyWeight = neuron.GetWeight(j);
                        oldWeight = neuron.GetOldWeight(j);
                        newWeight = ((this.eta * neuron.Delta * this.hiddenLayerFirst[j].Value) + (this.alfa * (actuallyWeight - oldWeight)));
                        neuron.ChangeInputWeight(j, (actuallyWeight + newWeight));

                    }
                }

                //correction weights in output layer
                for (int i = 0; i < this.numberOfNeuronsInOutputLayer; i++)
                {
                    Neuron neuron = this.outputLayer[i];
                    for (int j = 0; j < this.numberOfNeuronsInHiddenLayerSecond; j++)
                    {
                        double newWeight, actuallyWeight, oldWeight;
                        actuallyWeight = neuron.GetWeight(j);
                        oldWeight = neuron.GetOldWeight(j);
                        newWeight = ((this.eta * neuron.Delta * this.hiddenLayerSecond[j].Value) + (this.alfa * (actuallyWeight - oldWeight)));
                        neuron.ChangeInputWeight(j, (actuallyWeight + newWeight));
                    }       
                }

                //calculate RMS
                double RMS = 0.0;
                for (int i = 0; i < this.outputLayer.Count; i++)
                {
                    RMS += (((double)correctOutputData[i] - this.outputLayer[i].Value) * ((double)correctOutputData[i] - this.outputLayer[i].Value));
                }
                ERMS = Math.Sqrt(RMS / (double)this.outputLayer.Count);

                tmpCounter++;
                if (tmpCounter >= 1500)
                    break;
            }
        }
        public void SaveNetworkToFile() //method that saves natural network to file
        {
            string path = DateTime.Now.ToString(@"dd\-MM\-yyyy HH.mm.ss") + ".txt";

            FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write);
            StreamWriter writer = new StreamWriter(fs);

            //save network parameters
            writer.Write("Network parameters:" + Environment.NewLine);
            writer.Write(this.numberOfNeuronsInInputLayer);
            writer.Write(" ");
            writer.Write(this.numberOfNeuronsInHiddenLayerFirst);
            writer.Write(" ");
            writer.Write(this.numberOfNeuronsInHiddenLayerSecond);
            writer.Write(" ");
            writer.Write(this.numberOfNeuronsInOutputLayer);
            writer.Write(" ");
            writer.Write(this.eta);
            writer.Write(" ");
            writer.Write(this.alfa);
            writer.Write(Environment.NewLine + Environment.NewLine);

            //save weights in first hidden layer
            writer.Write("First hidden layer:" + Environment.NewLine);
            for (int i = 0; i < this.numberOfNeuronsInHiddenLayerFirst; i++)
            {
                Neuron neuron = this.hiddenLayerFirst[i];
                for (int j = 0; j < this.numberOfNeuronsInInputLayer; j++)
                {
                    writer.Write(neuron.GetWeight(j));
                    writer.Write(" ");
                }
                writer.Write(Environment.NewLine);
            }
            writer.Write(Environment.NewLine);

            //save weights in second hidden layer
            writer.Write("Second hidden Layer:" + Environment.NewLine);
            for (int i = 0; i < this.numberOfNeuronsInHiddenLayerSecond; i++)
            {
                Neuron neuron = this.hiddenLayerSecond[i];
                for (int j = 0; j < this.numberOfNeuronsInHiddenLayerFirst; j++)
                {
                    writer.Write(neuron.GetWeight(j));
                    writer.Write(" ");
                }
                writer.Write(Environment.NewLine);
            }
            writer.Write(Environment.NewLine);

            //save weights in output layer
            writer.Write("Output Layer:" + Environment.NewLine);
            for (int i = 0; i < this.numberOfNeuronsInOutputLayer; i++)
            {
                Neuron neuron = this.outputLayer[i];
                for (int j = 0; j < this.numberOfNeuronsInHiddenLayerSecond; j++)
                {
                    writer.Write(neuron.GetWeight(j));
                    writer.Write(" ");
                }
                writer.Write(Environment.NewLine);
            }

            writer.Close();
            fs.Close();
        }
        public void LoadNetworkFromFile(string path) //method that loads natural network from file
        {
            FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read);
            StreamReader reader = new StreamReader(fs);

            //read network parameters
            reader.ReadLine();
            string networkParameters = reader.ReadLine();
            string[] networkParametersSplited = networkParameters.Split(' ');
            this.numberOfNeuronsInInputLayer = int.Parse(networkParametersSplited[0]);
            this.numberOfNeuronsInHiddenLayerFirst = int.Parse(networkParametersSplited[1]);
            this.numberOfNeuronsInHiddenLayerSecond = int.Parse(networkParametersSplited[2]);
            this.numberOfNeuronsInOutputLayer = int.Parse(networkParametersSplited[3]);
            this.eta = double.Parse(networkParametersSplited[4]);
            this.alfa = double.Parse(networkParametersSplited[5]);
            reader.ReadLine();

            //read weights in first hidden layer
            reader.ReadLine();
            for (int i = 0; i < this.numberOfNeuronsInHiddenLayerFirst; i++)
            {
                string weights = reader.ReadLine();
                string[] weightsSplited = weights.Split(' ');
                for (int j = 0; j < this.numberOfNeuronsInInputLayer; j++)
                {
                    double weight = double.Parse(weightsSplited[j]);
                    this.hiddenLayerFirst[i].ChangeInputWeight(j, weight);
                }
            }
            reader.ReadLine();

            //read weights in second hidden layer
            reader.ReadLine();
            for (int i = 0; i < this.numberOfNeuronsInHiddenLayerSecond; i++)
            {
                string weights = reader.ReadLine();
                string[] weightsSplited = weights.Split(' ');
                for (int j = 0; j < this.numberOfNeuronsInHiddenLayerFirst; j++)
                {
                    double weight = double.Parse(weightsSplited[j]);
                    this.hiddenLayerSecond[i].ChangeInputWeight(j, weight);
                }
            }
            reader.ReadLine();

            //read weights in output layer
            reader.ReadLine();
            for (int i = 0; i < this.numberOfNeuronsInOutputLayer; i++)
            {
                string weights = reader.ReadLine();
                string[] weightsSplited = weights.Split(' ');
                for (int j = 0; j < this.numberOfNeuronsInHiddenLayerSecond; j++)
                {
                    double weight = double.Parse(weightsSplited[j]);
                    this.outputLayer[i].ChangeInputWeight(j, weight);
                }
            }
            reader.ReadLine();

            reader.Close();
            fs.Close();
        }
        public string[] ClassNames //getter field classNames
        {
            get
            {
                return this.classNames;
            }
        }
    }
}