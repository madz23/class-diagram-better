/**


   - Construct images from C-style arrays:
       - <tt>CImg<int> img(data_buffer,256,256);</tt> constructs a 256x256 greyscale image from a \c int* buffer
       \c data_buffer (of size 256x256=65536).
       - <tt>CImg<unsigned char> img(data_buffer,256,256,1,3);</tt> constructs a 256x256 color image
       from a \c unsigned \c char* buffer \c data_buffer (where R,G,B channels follow each others).

       The complete list of constructors can be found <a href="#constructors">here</a>.

   \par Most useful functions

   The \c CImg<T> class contains a lot of functions that operates on images.
   Some of the most useful are:

   - operator()(): Read or write pixel values.
   - display(): displays the image in a new window.
**/
#pragma once

// Horse is not vehicle and does not require any car parts
class Horse{
  private:
    double timeEaten;
    int timesPooped;
  public:
    Horse(double t, int p);
    Horse();

    //Setters
    void setWhenAte(double t){ timeEaten = t; }
    void setTimesPooped(int p){ timesPooped = p; }

    // Getters
    double getLastTimeEaten() const { return timeEaten; }
    int getTimesPooped() const { return timesPooped; }
}