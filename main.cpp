//
//  main.cpp
//  test-opencv
//
//  Created by BAZZAOUI chaymae on 03/29/17.
//  Copyright © 2017 BAZZAOUI chaymae. All rights reserved.
//

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace cv;
int i,j, a;
Mat source, dest;

int ** A;

void copy_pixel(Vec3b pixel_source, Vec3b pixel_dest) {
    pixel_dest.val[0] = pixel_source.val[0];
    pixel_dest.val[1] = pixel_source.val[1];
    pixel_dest.val[2] = pixel_source.val[2];
}

int in_the_same_range(Vec3b pixel_source, Vec3b pixel_dest) {
    if (
        ( fabs(pixel_dest.val[0] - pixel_source.val[0]) <= 25) &&
        ( fabs(pixel_dest.val[1] - pixel_source.val[1]) <= 25) &&
        ( fabs(pixel_dest.val[2] - pixel_source.val[2]) <= 25)
        ) {
        return 1;
    }
    return 0;
}

void affectation(int i, int j) {
    
    
    if (A[i][j] != 0) {
        if ((i<source.rows-1) && (j >= 1)) {
            if (A[i+1][j-1] == 0) {
                if (in_the_same_range(source.at<Vec3b>(i+1,j-1), dest.at<Vec3b>(i,j))) {
                    A[i+1][j-1] = A[i][j];
                    copy_pixel(dest.at<Vec3b>(i,j), dest.at<Vec3b>(i+1,j-1));
                    affectation(i+1,j-1);
                }
            }
        }
        
        if ((i<source.rows-1)){
            if (A[i+1][j] == 0) {
                //cout << i << " " << j << endl;
                if (in_the_same_range(source.at<Vec3b>(i+1,j), dest.at<Vec3b>(i,j))) {
                    A[i+1][j] = A[i][j];
                    copy_pixel(dest.at<Vec3b>(i,j), dest.at<Vec3b>(i+1,j));
                    //cout << i << " " << j << endl;
                    affectation(i+1,j);
                }
            }
        }
        if ((i<source.rows-1) && (j<source.cols-1)) {
            if (A[i+1][j+1] == 0) {
                if (in_the_same_range(source.at<Vec3b>(i+1,j+1), dest.at<Vec3b>(i,j))) {
                    A[i+1][j+1] = A[i][j];
                    copy_pixel(dest.at<Vec3b>(i,j), dest.at<Vec3b>(i+1,j+1));
                    affectation(i+1,j+1);
                }
            }
        }
        
        if ((j >= 1)) {
            if (A[i][j-1] == 0) {
                if (in_the_same_range(source.at<Vec3b>(i,j-1), dest.at<Vec3b>(i,j))) {
                    A[i][j-1] = A[i][j];
                    copy_pixel(dest.at<Vec3b>(i,j), dest.at<Vec3b>(i,j-1));
                    affectation(i,j-1);
                }
            }
        }
        if ((j<source.cols-1)) {
            if (A[i][j+1] == 0) {
                if (in_the_same_range(source.at<Vec3b>(i,j+1), dest.at<Vec3b>(i,j))) {
                    A[i][j+1] = A[i][j];
                    copy_pixel(dest.at<Vec3b>(i,j), dest.at<Vec3b>(i,j+1));
                    affectation(i,j+1);
                }
            }
        }
        if ((j >= 1) && (i >= 1)) {
            if (A[i-1][j-1] == 0) {
                if (in_the_same_range(source.at<Vec3b>(i-1,j-1), dest.at<Vec3b>(i,j))) {
                    A[i-1][j-1] = A[i][j];
                    copy_pixel(dest.at<Vec3b>(i,j), dest.at<Vec3b>(i-1,j-1));
                    affectation(i-1,j-1);
                }
            }
        }
        if ((i >= 1)) {
            if (A[i-1][j] == 0) {
                if (in_the_same_range(source.at<Vec3b>(i-1,j), dest.at<Vec3b>(i,j))) {
                    A[i-1][j] = A[i][j];
                    copy_pixel(dest.at<Vec3b>(i,j), dest.at<Vec3b>(i-1,j));
                    affectation(i-1,j);
                }
            }
        }
        if ((i >= 1) && (j<source.cols-1)) {
            if (A[i-1][j+1] == 0) {
                if (in_the_same_range(source.at<Vec3b>(i-1,j+1), dest.at<Vec3b>(i,j))) {
                    A[i-1][j+1] = A[i][j];
                    copy_pixel(dest.at<Vec3b>(i,j), dest.at<Vec3b>(i-1,j+1));
                    affectation(i-1,j+1);
                }
            }

        }
        
        
    } else {
        a = a+1;
        A[i][j] = a;
        copy_pixel(source.at<Vec3b>(i,j),dest.at<Vec3b>(i,j));
        affectation(i,j);
    }
}



int main(int, char**)
{
    source = imread("test.jpg",1);
    dest = source.clone();
    
    
    A = new int* [source.rows];
    
    for(i=0;i<source.rows;i++) {
        A[i]= new int[source.cols];
    }
    
    for(i=0;i<source.rows;i++) {
        for(j=0;j<source.cols;j++) {
            A[i][j] = 0;
        }
    }

    
    if (source.empty()){
        cout <<"impossible de charger l'image "<<endl;
        return -1;
    }
    
    a = 1;
    A[0][0] = a;
    copy_pixel(0,0);
    
    for(i=0;i<=source.rows-1;i++) {
        for(j=0;j<=source.cols-1;j++) {
            
            affectation(i,j);
        }
    }
    
    for (int i=0; i < source.rows; i++) {
        
        for (int j=0; j < source.cols; j++)
            cout << A[i][j];
        cout << endl;
    }
    
    namedWindow("image source", WINDOW_AUTOSIZE);
    imshow("image source", dest);
    waitKey(0);
    return 0;
}

