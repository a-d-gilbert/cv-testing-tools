#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat original, hsv, thresholded;//picture and value storage for thresholding
    int Hmin = 0, Smin = 0, Vmin = 0;
    int Hmax = 0, Smax = 0, Vmax = 0;
    bool loop = true;//value to change to exit loop

    while( loop == true)
    {
        namedWindow("Thresh Test", CV_WINDOW_AUTOSIZE );//window to show filtered image
        namedWindow("Original Image", CV_WINDOW_AUTOSIZE);//window to show unfiltered image

        createTrackbar("H-min", "Thresh Test", &Hmin, 255, 0);//creating trackbars for values
        createTrackbar("S-min", "Thresh Test", &Smin, 255, 0);
        createTrackbar("V-min", "Thresh Test", &Vmin, 255, 0);
        createTrackbar("H-max", "Thresh Test", &Hmax, 255, 0);
        createTrackbar("S-max", "Thresh Test", &Smax, 255, 0);
        createTrackbar("V-max", "Thresh Test", &Vmax, 255, 0);

        Scalar thresholdMin(Hmin, Smin, Vmin);
        Scalar thresholdMax(Hmax, Smax, Vmax);

        try{
            original = imread("/home/alexander/Pictures/usable test images/path markers/546.png");//insert file path here
                                                                                                 //for whatever image you would
                                                                                                //like to test against
            cvtColor(original,hsv,CV_BGR2HSV);
            inRange(hsv,thresholdMin,thresholdMax,thresholded);

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
