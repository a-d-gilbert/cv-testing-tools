#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat original, gauss, laplacian, final;//picture and value storage for thresholding
    int kSize = 3, lKsize = 3, scale = 5, delta = 31, ddepth = CV_16S;
    int sigX = 0, sigY = 0;

    bool loop = true;//value to change to exit loop

    while( loop == true)
    {
        namedWindow("Trackbars",CV_WINDOW_AUTOSIZE);//window for trackbars
        namedWindow("laplacian filter", CV_WINDOW_AUTOSIZE );//window to show filtered image
        namedWindow("Original Image", CV_WINDOW_AUTOSIZE);//window to show unfiltered image

        createTrackbar("gaussian kernel size","Trackbars",&kSize,13,0);//creating trackbars for values
        createTrackbar("Sigma X","Trackbars",&sigX,31,0);
        createTrackbar("Sigma Y","Trackbars",&sigY,31,0);
        createTrackbar("laplacian kernel size","Trackbars",&lKsize,13,0);
        createTrackbar("Scale","Trackbars",&scale,5,0);
        createTrackbar("Delta","Trackbars",&delta,31,0);

        if(kSize % 2 == 0 && kSize <= 12)
            kSize += 1;

        if(lKsize % 2 == 0 && lKsize <= 12)
            lKsize += 1;

        try{
            original = imread("/home/alexander/Pictures/usable test images/path markers/546.png");//insert file path here
                                                                                                 //for whatever image you would                                                                                             //would like to test against
            GaussianBlur( original, gauss, Size(kSize,kSize), sigX, sigY, BORDER_DEFAULT );
            cvtColor( gauss, gauss, CV_RGB2GRAY );
            Laplacian( gauss, laplacian, ddepth, lKsize, scale, delta, BORDER_DEFAULT );
            convertScaleAbs( laplacian, final);

            imshow("Original Image",original);//showing unaltered then original image
            imshow("laplacian filter", final);
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
