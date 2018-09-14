using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;

namespace RecognitionOfEmoticons
{
    class Neuron
    {
        private static Random n = new Random(Environment.TickCount); //static variable used in randomize neuron weights

        private double beta; //variable that stores beta coefficient
        private double value; //variable that stores actually neuron output
        private double delta; //variable that stores error
        private List<double> inputsWeights; //list that stores actually weights of subsequent neuron inputs
        private List<double> oldInputsWeights; //list that stores old weights of subsequent neuron inputs

        public Neuron() //constructor
        {
            this.beta = 0.5;
            this.inputsWeights = new List<double>();
            this.value = 0;
            this.delta = 0;
            this.oldInputsWeights = new List<double>();
        }
        public int InputsCount //getter that return number of inputs
        {
            get
            {
                return this.inputsWeights.Count;
            }
        }
        public double Value //getter field value
        {
            get
            {
                return this.value;
            }
        }
        public double Delta //getter and setter field delta
        {
            get
            {
                return this.delta;
            }
            set
            {
                this.delta = value;
            }
        }
        public double Beta //getter field beta
        {
            get
            {
                return this.beta;
            }
        }
        private double ActivationFunction(double s) //method that returns value of activation function
        {
            double value;
            value = 1.0 / (1.0 + (Math.Exp(beta*(-s))));
            return value;
        }
        public void AddInputs(int numbersOfInputs) //method that add inputs in the number given as its argument
        {
            for (int i = 0; i < numbersOfInputs; i++)
            {
                double weight = Neuron.n.NextDouble();
                this.inputsWeights.Add(weight);
                this.oldInputsWeights.Add(weight);
            }
        }
        public double GetOutput(List<double> inputs) //method that calculates and returns neuron  output
        {
            double tempValue = 0;
            double outputValue = 0;
            for (int i = 0; i < inputs.Count; i++)
            {
                tempValue += (this.inputsWeights[i] * inputs[i]);
            }
            outputValue = this.ActivationFunction(tempValue);
            this.value = outputValue;
            return outputValue;
        }
        public double GetOutput(List<int> inputs) //method that calculates and returns neuron  output
        {
            double tempValue = 0;
            double outputValue = 0;
            for (int i = 0; i < inputs.Count; i++)
            {
                tempValue += (double)(this.inputsWeights[i] * inputs[i]);
            }
            outputValue = this.ActivationFunction(tempValue);
            this.value = outputValue;
            return outputValue;
        }
        public void ChangeInputWeight(int numberOfInput, double newWeight) //method that change inputs weight on selected input
        {
            this.oldInputsWeights[numberOfInput] = this.inputsWeights[numberOfInput];
            this.inputsWeights[numberOfInput] = newWeight;
        }
        public double GetWeight(int numberOfInput) //method that returns actually weight on input given as its argument
        {
            return this.inputsWeights[numberOfInput];
        }
        public double GetOldWeight(int numberOfInput) //method that returns old weight on input given as its argument
        {
            return this.oldInputsWeights[numberOfInput];
        }
    }
}