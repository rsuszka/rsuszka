using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.IO;

namespace RecognitionOfEmoticons
{
    class MyPicture
    {
        private Bitmap inputData; //variable that stores bitmap

        public Bitmap InputBitmap //getter field inputData
        {
            get
            {
                return this.inputData;
            }
        }
        public MyPicture(string path) //constructor
        {
            this.inputData = new Bitmap(path);
        }
        public void SobellFilter() //method that applies a Sobel filter to bitmap
        {
            int width = this.inputData.Width - 1;
            int height = this.inputData.Height - 1;
            Bitmap tmp = new Bitmap(width, height);
            
            for (int i = 1; i < width; i++)
            {
                for (int j = 1; j < height; j++)
                {
                    Color color1y, color3y, color4y, color6y, color7y, color9y;
                    color1y = this.inputData.GetPixel(i - 1, j - 1);
                    color3y = this.inputData.GetPixel(i + 1, j - 1);
                    color4y = this.inputData.GetPixel(i - 1, j);
                    color6y = this.inputData.GetPixel(i + 1, j);
                    color7y = this.inputData.GetPixel(i - 1, j + 1);
                    color9y = this.inputData.GetPixel(i + 1, j + 1);
                    int colorRedY = color1y.R + color3y.R * (-1) + color4y.R * (2) + color6y.R * (-2) + color7y.R + color9y.R * (-1);
                    int colorGreenY = color1y.G + color3y.G * (-1) + color4y.G * (2) + color6y.G * (-2) + color7y.G + color9y.G * (-1);
                    int colorBlueY = color1y.B + color3y.B * (-1) + color4y.B * (2) + color6y.B * (-2) + color7y.B + color9y.B * (-1);
                    int avrY = (colorRedY + colorGreenY + colorBlueY) / 3;

                    Color color1x, color2x, color3x, color7x, color8x, color9x;
                    color1x = this.inputData.GetPixel(i - 1, j - 1);
                    color2x = this.inputData.GetPixel(i, j - 1);
                    color3x = this.inputData.GetPixel(i + 1, j - 1);
                    color7x = this.inputData.GetPixel(i - 1, j + 1);
                    color8x = this.inputData.GetPixel(i, j + 1);
                    color9x = this.inputData.GetPixel(i + 1, j + 1);
                    int colorRedX = color1x.R + color2x.R * (2) + color3x.R + color7x.R * (-1) + color8x.R * (-2) + color9x.R * (-1);
                    int colorGreenX = color1x.G + color2x.G * (2) + color3x.G + color7x.G * (-1) + color8x.G * (-2) + color9x.G * (-1);
                    int colorBlueX = color1x.B + color2x.B * (2) + color3x.B + color7x.B * (-1) + color8x.B * (-2) + color9x.B * (-1);
                    int avrX = (colorRedX + colorGreenX + colorBlueX) / 3;

                    int avr = Math.Abs(avrX) + Math.Abs(avrY);

                    if (avr > 255)
                    {
                        avr = 255;
                    }
                    if (avr < 0)
                    {
                        avr = 0;
                    }
                    tmp.SetPixel(i, j, Color.FromArgb(avr, avr, avr));
                }
            }
            this.inputData = tmp;
        }
        public void InvertColors() //method that changes white pixels to black pixels and black pixels to white pixels
        {
            Bitmap tmp = new Bitmap(this.inputData.Width, this.inputData.Height);
            for (int i = 0; i < this.inputData.Width; i++)
            {
                for (int j = 0; j < this.inputData.Height; j++)
                {
                    Color actuallyPixel = this.inputData.GetPixel(i, j);
                    if (actuallyPixel.R < 80)
                    {
                        tmp.SetPixel(i, j, Color.FromArgb(255, 255, 255));
                    }
                    else
                    {
                        tmp.SetPixel(i, j, Color.FromArgb(0, 0, 0));
                    }
                }
            }
            this.inputData = tmp;
        }
        public void Resize(int width, int height) //method that changes the size of the image
        {
            Bitmap tmp = new Bitmap(this.inputData, width, height);
            this.inputData = tmp;
        }
        public void CorrectCollors() //method that corrects colors on bitmap
        {
            Bitmap tmp = new Bitmap(this.inputData.Width, this.inputData.Height);
            for (int i = 0; i < this.inputData.Width; i++)
            {
                for (int j = 0; j < this.inputData.Height; j++)
                {
                    Color actuallyPixel = this.inputData.GetPixel(i, j);
                    if (actuallyPixel.R >= 250)
                    {
                        tmp.SetPixel(i, j, Color.FromArgb(255, 255, 255));
                    }
                    else
                    {
                        tmp.SetPixel(i, j, Color.FromArgb(0, 0, 0));
                    }
                    if (j > 5 && i < 5)
                    {
                        tmp.SetPixel(i, j, Color.FromArgb(255, 255, 255));
                    }
                    if (j > 5 && i > 25)
                    {
                        tmp.SetPixel(i, j, Color.FromArgb(255, 255, 255));
                    }
                }
            }
            this.inputData = tmp;
        }
        public int[] ToTable() //method that converts bitmap to a binary table 
        {
            int[] output = new int[this.inputData.Width * this.inputData.Height];
            int counter = 0;
            for (int i = 0; i < this.inputData.Height; i++)
            {
                for (int j = 0; j < this.inputData.Width; j++)
                {
                    Color actuallyPixelColor = this.inputData.GetPixel(j, i);
                    if (actuallyPixelColor.R == 0)
                    {
                        output[counter] = 1; //black
                    }
                    else
                    {
                        output[counter] = 0; //white
                    }
                    counter++;
                }
            }
            return output;
        }
        public void CropImage(int x, int y, int width, int height) //method that cropping bitmap
        {
            Rectangle crop = new Rectangle(x, y, width, height);

            var bmp = new Bitmap(crop.Width, crop.Height);
            using (var gr = Graphics.FromImage(bmp))
            {
                gr.DrawImage(this.inputData, new Rectangle(0, 0, bmp.Width, bmp.Height), crop, GraphicsUnit.Pixel);
            }

            this.inputData = bmp;
        }
    }
}