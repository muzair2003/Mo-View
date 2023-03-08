#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int function_call(string Method) {
    Mat Original;// Contains original image
    Mat Output;// Contains output image
    //string Method; // Contains user choice of filter

    cout << "Choose between Laplacian or Canny or Gray or Contrast or Brightness" << endl; //ask user what they would like to do with the image
   // cin >> Method;

    Original = imread("tower.jpg");// open image

    if (Original.empty()) { // if unable to open image
        cout << "error: image not read from file";// show error message
        return 0;
    }
    if (Method == "Canny") { // if user chooses canny edge detection
        
        cvtColor(Original, Output, COLOR_BGR2GRAY);// convert to grayscale

        GaussianBlur(Output,// input image
            Output,// output image
            Size(5, 5),// smoothing pixels
            1.5);//how much the image is blurred

        Canny(Original,// input image
            Output,// output image
            100,// min threshold
            200);// max threshold
    }
    if (Method == "Gray") {// if user choose grayscale

        cvtColor(Original, Output, COLOR_BGR2GRAY);// convert to grayscale
    }
    if (Method == "Contrast") { // if the user wants to vary the contrast

        float Percentage; // percentage of contrast variation
        string vary; // contains if the user wants an increase or decrease

        cout << "Would you like to increase or decrease you Contrast" << endl;
        cin >> vary;

        cout << "What Percentage would you like to increase the contrast by?" << endl; // ask the user how much the would like to vary contrast
        cin >> Percentage; // stores the user contrast value

        if (vary == "decrease") { // if the user wants to decrease the contrast

            // decreases contrast
            Original.convertTo(Output, // Output image
                -1,// matrix type
                (1 - (Percentage / 100)), // scale factor
                0); // added to the scale value
        }
        if (vary == "increase") { //if the user wants to increase the contrast

            Original.convertTo(Output, -1, (Percentage / 50), 0); // increase contrast
        }
    }
    if (Method == "Brightness") {// if the user wants to vary the brightness

        float Percentage; // percentage of brightness variation
        string vary; // stores type of variation chosen by user

        cout << "Would you like to increase or decrease the Contrast" << endl;
        cin >> vary; // stores user variation type

        cout << "What Percentage Brightness Would you Like?" << endl; //ask user how much decrease they would like
        cin >> Percentage;

        if (vary == "increase") { // if user wants to increase brightness

            Original.convertTo(Output, -1, 1, Percentage); // increases brightness

        }
        if (vary == "decrease") { // if user wants to decrease brightness

            Original.convertTo(Output, -1, 1, -Percentage); // decreases brightness
        }
    }
    if (Method == "Laplacian") { // if user chooses Laplacian edge detection

        Mat Laplacian_edge; // Stores laplacian image

        GaussianBlur(Original, Output, Size(5, 5), 0, 0, BORDER_DEFAULT); // blurs the image

        cvtColor(Output, Output, COLOR_RGB2GRAY); // makes the image into grayscale

        //Laplacian edge detection method
        Laplacian(Output,// input image
            Laplacian_edge,// output image
            CV_16S, // depth of destination image
            3, // kernel size
            1, //scale value
            0, //delta value
            BORDER_DEFAULT); // border type

        convertScaleAbs(Laplacian_edge, Output); // converts image into 8-bit

    }
    namedWindow("Original", WINDOW_AUTOSIZE);// resizes windows for original image
    namedWindow("Output", WINDOW_AUTOSIZE);// resizes windows for output image

    imshow("Original", Original); // displays original image
    imshow("Output", Output); // displays output image

    waitKey(0);// window stays open until a key is pressed

    return 0;
}