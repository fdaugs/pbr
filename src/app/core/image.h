//
// Created by Martin Eisemann on 25.10.18.
//

#ifndef INHERITANCE_IMAGE_H
#define INHERITANCE_IMAGE_H

#include <string>
#include <opencv/cv.hpp>
#include <iostream>

typedef cv::Vec3d Pixel;

/**
 * Basic image class
 * Internal data representation is 3 channels with double values
 * Save function scales the values by 255 to conveniently save the data as PNGs
 */
class Image {

public:
    cv::Mat img;
    int rows = 0;
    int cols = 0;

    Image(const int xres, int yres)
            : rows(yres), cols(xres)
    {
        img = cv::Mat(yres, xres, CV_64FC3);
    };

    Pixel& at(const int x, const int y){
        return img.at<Pixel>(rows-1-y,x);
    };

    static void onMouse(int event, int x, int y, int flags, void* image){
        cv::Mat* m = static_cast<cv::Mat*>(image);
        const Pixel& p = m->at<Pixel>(y,x);

        std::cout << p << std::endl;
    }

    void show(std::string title){
        //cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
        cv::imshow(title, img);

        cv::setMouseCallback( title, onMouse, &img );

        cv::waitKey(0);
    };

    void save(const std::string title){
        cv::Mat tmp = img.clone() * 255.0;
        cv::imwrite(title, tmp);
    };
};


#endif //INHERITANCE_IMAGE_H
