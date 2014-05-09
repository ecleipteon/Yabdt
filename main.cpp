#include "bound_rec.hpp"

/*
* This code is part of yabdt open source software.
* Please see the README (or the header file) for more license details
*/

int main(int argc, char * argv[]) {
	
	if(argc != 2)
		usage();
	
	if(!(std::strcmp(argv[1], "help")))
		help();

	Img src(argv[1]);
	
	
	src.boundarize();
	
	


	

	
	std::cout<<"Ho campionato "<<src.getPoints()<<" punti\n";
  	//printing output

  	src.print_rev(0);
	

	namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
	imshow( "Display Image", src.getImg() );
	waitKey(0);
	
	std::cout <<" "<< " "<<src.getPoints()<<std::endl;
	std::cout<<src.getImg().size();
	
}
