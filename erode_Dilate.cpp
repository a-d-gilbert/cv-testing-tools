#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat original,eroded,dilated;//picture and value storage for thresholding
    int eKSize = 3, dKSize = 3, shape = 0;
    //Point anchor = Point(-1,-1);

    bool loop = true;//value to change to exit loop

    while( loop == true)
    {

        namedWindow("Sharpened", CV_WINDOW_AUTOSIZE );//window to show filtered image
        namedWindow("Original Image", CV_WINDOW_AUTOSIZE);//window to show unfiltered image

        createTrackbar("Erosion kernel size","Sharpened",&eKSize,13,0);//creating trackbars for values
        createTrackbar("erosion shape","Sharpened",&shape,2,0);
        createTrackbar("Dilation kernel size","Sharpened",&dKSize,13,0);
        createTrackbar("Dilation shape","Sharpened",&shape,2,0);

        if(eKSize % 2 == 0 && eKSize <= 12)
            eKSize += 1;

        if(dKSize % 2 == 0 && dKSize <= 12)
            dKSize += 1;

        try{
            original = imread("/home/alexander/Pictures/usable test images/path markers/546.png");//insert file path here
            //for whatever image you would                                                                                             //would like to test against
            erode(original,eroded,getStructuringElement(shape,Size(eKSize,eKSize)));
            dilate(eroded,dilated,getStructuringElement(shape,Size(dKSize,dKSize)));

            imshow("Sharpened",dilated);
            imshow("Original Image",original);
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
