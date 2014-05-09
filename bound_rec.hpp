/*Copyright (c) 2014 Luca Castiglione

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE..*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <cv.h>
#include <highgui.h>


using namespace cv;

void help();
void usage();
void img_error();

class Img {
	private:
		Mat image;
		int *vx;
		int *vy;
		int points;

		void sampling();


	public:
		Img(const char *);
		void boundarize();
		//void setImg();
		void printv(int ) const;
		void print_rev(int ) const;
		const int getPoints() const { return points; }
		const Mat getImg() const { return image; }
		const int * getvx() const {return vx;}
		const int * getvy() const {return vy;}
		virtual ~Img();


};
