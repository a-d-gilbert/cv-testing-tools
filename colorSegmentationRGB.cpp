#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat original, thresholded;//picture and value storage for thresholding
    int Rmin = 0, Gmin = 0, Bmin = 0;
    int Rmax = 0, Gmax = 0, Bmax = 0;
    bool loop = true;//value to change to exit loop

    while( loop == true)
    {
        namedWindow("Thresh Test", CV_WINDOW_AUTOSIZE );//window to show filtered image
        namedWindow("Original Image", CV_WINDOW_AUTOSIZE);//window to show unfiltered image

        createTrackbar("B-min","Thresh Test",&Bmin,255,0);//creating trackbars for values
        createTrackbar("G-min","Thresh Test",&Gmin,255,0);
        createTrackbar("R-min","Thresh Test",&Rmin,255,0);
        createTrackbar("B-max","Thresh Test",&Bmax,255,0);
        createTrackbar("G-max","Thresh Test",&Gmax,255,0);
        createTrackbar("R-max","Thresh Test",&Rmax,255,0);

        Scalar thresholdMin(Bmin,Gmin,Rmin);
        Scalar thresholdMax(Bmax,Gmax,Rmax);

        try{
            original = imread("/home/alexander/Pictures/usable test images/path markers/546.png");//insert file path here
                                                                                                 //for whatever image you would
                                                                                                //like to test against
            inRange(original,thresholdMin,thresholdMax,thresholded);

            imshow("Original Image",original);//showing unaltered then original image
            imshow("Thresh Test", thresholded);
        }

        catch (Exception& e)//error checking
        {
            const char* err_msg = e.what();
            cout << "exception caught: \n" << err_msg << std::endl;
        }

        char key = waitKey(33) & 0xFF;//checking for key press

        if (key == 27)//press esc to quit
        {
            loop = false;
        }

    }

    return 0;
}

