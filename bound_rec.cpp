#include "bound_rec.hpp"

/*
* This code is part of yabdt open source software.
* Please see the LICENSE (or the header) file for more license details
*/

Img::Img(const char *fn) {
	 image = imread( fn, 1 );
		
	 if(image.empty())
		img_error();

	 vx = new int[1];
	 vy = new int[1];
	 points = 0;
	 
}

void Img::boundarize() {
	Mat image_gray, canny_output, nonzeros;
	int thresh = 100;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	RNG rng(12345);
	
	cvtColor( this->image, image_gray, CV_BGR2GRAY );
	blur( image_gray, image_gray, Size(3,3) );

	Canny( image_gray, canny_output, thresh, thresh*2, 3 );
	findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	this->image =   Mat::zeros( canny_output.size(), CV_8UC3 );

	for( unsigned int i = 0; i< contours.size(); i++ )
	{
	       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
	       drawContours( this->image, contours, i, color, 2, 8, hierarchy, 0, Point() );
	}

	cvtColor( this->image, this->image, CV_BGR2GRAY );
	threshold( this->image, this->image, 0, 255,0 );
	findNonZero(this->image, nonzeros);
	
	this->points = nonzeros.rows;
	
	delete [] vx;
	delete [] vy;

	std::cout << "\n[+] Initiallizing vectors : "<<points<<" points detected";
<<<<<<< HEAD
	
=======

>>>>>>> a2faf243070692899d28948e063d2c49d968289f
	vx = new int[points+1];
	std::cout << "\n[+] Vx initiallized";
	vy = new int[points+1];
	std::cout << "\n[+] Vy Initiallized";
	
	this->sampling();
	
	
}

void Img::sampling() {
	//Questo algoritmo di campionamento fa abbastanza schifo

	int c = 0;
	bool first = false;

	std::cout << "\n[+] Starting contours sampling  (U->D)\n";

	for(int y=0; y<this->image.rows-1; y++)
	{
		first = false;
		int x = 0;
		while(!first && x<this->image.cols-1)
		{
			if((int)(this->image.at<uchar>(y,x)) != 0)
			{
				vx[c] = x;
				vy[c] = y;
				first = true;
				c++;
			}
			x++;
		}
	}
	
	std::cout << "\n[+] Starting contours sampling (L->R)\n";
	for(int x=0; x<this->image.cols-1; x++)
	{
		first = false;
		int y = 0;
		while(!first && y<this->image.rows-1)
		{
			if((int)(this->image.at<uchar>(y,x)) != 0)
			{
				vx[c] = x;
				vy[c] = y;
				first = true;
				c++;
			}
			y++;
		}
	}
	
	std::cout << "\n[+] Starting contours sampling (R->U)\n";

	for(int y=this->image.rows-1; y>0 ; y--)
	{
		first = false;
		int x = this->image.cols-1;
		while(!first && x>0)
		{
			if((int)(this->image.at<uchar>(y,x)) != 0)
			{
				vx[c] = x;
				vy[c] = y;
				first = true;
				c++;
			}
			x--;
		}
	}

	std::cout << "\n[+] Starting contours sampling (R->L)\n";

	for(int x=this->image.cols-1; x>0 ; x--)
	{
		first = false;
		int y = this->image.rows-1;
		while(!first && y>0)
		{
			if((int)(this->image.at<uchar>(y,x)) != 0)
			{
				vx[c] = x;
				vy[c] = y;
				first = true;
				c++;
			}
			y--;
		}
	}
	
	this->points = c-1;	

}

void Img::printv(int acc ) const {

	std::cout<< std:: endl;
	std::cout<<"XT=[";
  	for(int i = 0; i<this->points; i++) 
	{
	  std::cout << (float)(vx[i])/100 << " ";
	  i += acc;
  	}
  	std::cout<<"]/fs;";
  	std::cout<<std::endl;
  	
	std::cout<<std::endl;
  	std::cout<<"YT=[";
  	for(int i = 0; i<this->points; i++) 
	{
  	  std::cout << (float)(vy[i])/100 << " ";
  	  i += acc;
    	}
  	std::cout<<"]/fs;";

  	std::cout<< std:: endl;



}
void Img::print_rev(int acc) const {
	std::cout<< std:: endl;
	std::cout<<"XT=[";
  	for(int i = this->points; i>= 0; i--)
	{
	  std::cout << (float)(vx[i])/100 << " ";
	  i += acc;
  	}
  	std::cout<<"]/fs;";
  	std::cout<<std::endl;
  	
	std::cout<<std::endl;
  	std::cout<<"YT=[";
  	for(int i = this->points; i>= 0; i--) 
	{
  	  std::cout << (float)(vy[i])/100 << " ";
  	  i += acc;
    	}
  	std::cout<<"]/fs;";

  	std::cout<< std:: endl;


}
Img::~Img() {
	image.~Mat();
}

void help() {
	std::cout << "\n********************************************************************************************* \n";
	std::cout << "\nYABDT: Yet another boundary detection tool - Version 1.0.0 \n\n";
	std::cout << "Yabdt processes images (tested on jpg and png but should work on other formats too) to \n";
	std::cout << "exract external boundary points and prints their coordinates (xy space) according to \n";
	std::cout << "Matlab vector syntax. \n";
	std::cout << "\nThis program uses opencv libs to perform the boundary detection\n";
	std::cout << "This program is an open source software realesed under MIT License\n";
	std::cout << "See the LICENSE (or the header) file for further details about License";
	std::cout << "\n\n\t Live long and prosper \t\n";
	std::cout << "\n********************************************************************************************* \n";
	exit(EXIT_SUCCESS);
	
}

void usage() {
		std::cerr<<"Usage: image.ext"<<std::endl;
		std::cerr<<"help for more informations"<<std::endl;
		exit(EXIT_FAILURE);
}

void img_error() {

		std::cerr<<"Fatal error loading image" << std::endl;
	    	exit(EXIT_FAILURE);
}

