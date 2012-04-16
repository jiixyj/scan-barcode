#include <iostream>

#include <cv.h>
#include <highgui.h>

#include <zbar.h>

int main()
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Could not open camera" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat image;
    cv::namedWindow("image", 1);

    for (;;) {
        cv::Mat frame;
        cap >> frame;

        cv::cvtColor(frame, image, CV_BGR2GRAY);
        // image = cv::imread("/home/jan/Documents/barcode.png", 0);
        // cv::equalizeHist(image, image);
        // image = image > 128;

        { cv::Mat tmp;
          cv::GaussianBlur(image, tmp, cv::Size(0, 0), 3);
          cv::addWeighted(image, 1.5, tmp, -0.5, 0, tmp);
          image = tmp; }
        //
        // cv::equalizeHist(image, image);

        // for( int y = 0; y < image.rows; y++ ) {
        //     for( int x = 0; x < image.cols; x++ ) {
        //         image.at<uchar>(y,x) = cv::saturate_cast<uchar>( 2*( image.at<uchar>(y,x) ) + -128 );
        //     }
        // }

        zbar::ImageScanner scanner;
        scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

        zbar::Image zimage(image.cols, image.rows, "Y800", image.data, image.cols * image.rows);

        int n = scanner.scan(zimage);

        for (zbar::Image::SymbolIterator symbol = zimage.symbol_begin();
             symbol != zimage.symbol_end();
             ++symbol) {
            std::cout << "decoded "   << symbol->get_type_name()
                      << " symbol \"" << symbol->get_data() << '"' << std::endl;
        }

        zimage.set_data(NULL, 0);

        cv::imshow("image", image);

        if (cv::waitKey(10) >= 0) {
            break;
        }
    }

    return EXIT_SUCCESS;
}
