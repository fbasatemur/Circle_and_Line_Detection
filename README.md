# Circle and Line Detection With Hough Transform

* GUI: C++/CLR

## Destination:
Line and circle detection with Canny Edge Detection and Hough Space on the image.

## Steps:
1.	Apply Gaussian Filter[3x3] on Intensity image
2.	Magnitude and Direction info calculate
3.	Calculate Histogram using Magnitude Image
4.	Canny Edge Detection :
    - 4.1	Apply Non Maximal Suppression and thinning the edges.
    - 4.2	Edges are determined according to the values given to Hysteresis Threashold.
5.	Get the maximum number of edges and circles to be detected with TextBox.
6.	LINE Detection:
    - 6.1.	Apply Hough Transform for Edge Detection
    - 6.2.	Find the maximum number of edges
    - 6.3.	Mark maximum edges on image
7.	CIRCLE Detection:
    - 7.1.	Circle yarıçapını textBox’tan oku
    - 7.2.	Apply Hough Transform for Circle Detection
    - 7.3.	Find the maximum number of circles
    - 7.4.	Mark maximum circles on image

## Sample screenshots 
Sample 1 is Circle Detection

   ![alt text](https://github.com/fbasatemur/circle_and_line_detection_with_Hough_Transform/blob/master/screenshots/circle_ss1.png "Circle ScreenShot 1")
  
Sample 2 is Circle Detection 

  ![alt text](https://github.com/fbasatemur/circle_and_line_detection_with_Hough_Transform/blob/master/screenshots/circle_ss2.png "Circle ScreenShot 2")
  
Sample 3 is Line Detection 

  ![alt text](https://github.com/fbasatemur/circle_and_line_detection_with_Hough_Transform/blob/master/screenshots/line_ss.png "Line ScreenShot")
