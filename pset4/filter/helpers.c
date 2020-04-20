#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, avg = 0; j < width; j++)
        {
            avg = round(((double)image[i][j].rgbtRed + (double)image[i][j].rgbtBlue + (double)image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        int opsd = 1; // used to calculate the oposite side
        // swap the half sides (from 0 to middle [width / 2])
        for (int j = 0, middle = floor(width / 2); j < middle; j++)
        {
            tmp[i][j] = image[i][j];
            image[i][j] = image[i][width - opsd];
            image[i][width - opsd] = tmp[i][j];
            opsd++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    int avgRed, avgGreen, avgBlue, count;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for each pixel...
            avgBlue = 0;
            avgGreen = 0;
            avgRed = 0;
            count = 0;
            for (int r = i - 1; r <= i + 1; r++)
            {
                for (int c = j - 1; c <= j + 1; c++)
                {
                    if (r >= 0 && r < height && c >= 0 && c < width)
                    {
                        count++;
                        avgBlue += image[r][c].rgbtBlue;
                        avgGreen += image[r][c].rgbtGreen;
                        avgRed += image[r][c].rgbtRed;
                    }
                }
            }
            avgBlue = round((double)avgBlue / (double)count);
            avgGreen = round((double)avgGreen / (double)count);
            avgRed = round((double)avgRed / (double)count);
            // save into a temp image
            tmp[i][j].rgbtBlue = avgBlue;
            tmp[i][j].rgbtGreen = avgGreen;
            tmp[i][j].rgbtRed = avgRed;
        }
    }
    // swap from temp image to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    RGBTRIPLE tmp[height][width];
    double newRed, newGreen, newBlue;
    int gxR, gxG, gxB, gyR, gyG, gyB;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for each pixel...
            gxR = gxG = gxB = gyR = gyG = gyB = newRed = newGreen = newBlue = 0;
            for (int l = 0; l < 3; l++) // row of Gx and Gy
            {
                for (int c = 0; c < 3; c++) // col of Gx and Gy
                {
                    if (i + l - 1 >= 0 && i + l - 1 < height && j + c - 1 >= 0 && j + c - 1 < width) // if into the image array limits
                    {
                        gxR += gx[l][c] * image[i + l - 1][j + c - 1].rgbtRed;
                        gxG += gx[l][c] * image[i + l - 1][j + c - 1].rgbtGreen;
                        gxB += gx[l][c] * image[i + l - 1][j + c - 1].rgbtBlue;
                        gyR += gy[l][c] * image[i + l - 1][j + c - 1].rgbtRed;
                        gyG += gy[l][c] * image[i + l - 1][j + c - 1].rgbtGreen;
                        gyB += gy[l][c] * image[i + l - 1][j + c - 1].rgbtBlue;
                    }
                }
            }
            // calculate new pixels colors
            newRed = sqrt((gxR * gxR) + (gyR * gyR));
            newRed = newRed > 255 ? 255 : round(newRed);
            newGreen = sqrt((gxG * gxG) + (gyG * gyG));
            newGreen = newGreen > 255 ? 255 : round(newGreen);
            newBlue = sqrt((gxB * gxB) + (gyB * gyB));
            newBlue = newBlue > 255 ? 255 : round(newBlue);
            // save into a temp image
            tmp[i][j].rgbtRed = newRed;
            tmp[i][j].rgbtGreen = newGreen;
            tmp[i][j].rgbtBlue = newBlue;
        }
    }
    // swap from temp image to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
        }
    }
    return;
}
