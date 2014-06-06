// set up for 12 bits 
// ASSUMES 3840x2160 ONLY


#include <tiffio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
double PQ10000_f( double V);
double PQ10000_r( double L);

// TV applies PQ Gamma producing Luminance: L via PQf on Vtv L=PQf(Vtv)
// for each tv Luminance the V that produced it is given by Vtv=PQr(L)
// that "Vtv" is gamma encoded in ODT to cancel out the TV gamma  Vtv=PQr(Vlinear)
// Vlinear comes from ACES workflow (e.g after RRT +ODT w/o gamma)
// PQf(Vtv) = L
// PQf(PQr(Vlinear)) = L
// PQf(Vtv) = PQf(PQr(Vlinear)) = Vlinear
// L = Vlinear


using namespace std;



  // file pointer for tif
  TIFF* tif;
  
  // hard code 3840 x 2160
  unsigned short stripsize = 1920*2*3;
  unsigned short pixelStart = 0;
  unsigned short numStrips = 1080;
  short  stripStart;
  short D55 = 0;
  char tifName[] = "Pattern5.tif"; 
  int one=320; //quarter percent

main(int argc, char* argv[])
{ 

		
	     //Process Args:
	     short arg = 1;
	     while(arg < argc) {
	     	
		     if(strcmp(argv[arg],"-one")==0) {
					arg++;
					if(arg < argc)one=atof(argv[arg]);		 
					printf("one: %d\n",one);   	
		     }  
	
		     		     
	     arg++;
	     }
  
 
 
  // Array to store line of output for writing process
  // will be allocated to line width with 4 unsigned shorts
  unsigned short *Line;
  
  // Allocate memory to read each image
  int arraySizeX = stripsize/6 - pixelStart/6; // eg 3840
  int arraySizeY = numStrips;
  int arraySizeXH = arraySizeX/2; // eg 1920 cols
  int arraySizeYH = arraySizeY/2; // eg 1080 rows
  printf("Frame Size: %d x %d\n",arraySizeX,arraySizeY);

  Line =  (unsigned short *)malloc((4*arraySizeX*sizeof(unsigned short)));


		
		tif = TIFFOpen(tifName, "w");
		TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 3);
		TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 16);
		TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
		TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, arraySizeX);
		TIFFSetField(tif, TIFFTAG_IMAGELENGTH, arraySizeY);
		TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, 1);
		TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);		

		
		for (int line = 0;line < arraySizeY;line++)
		{


			
			for (unsigned int pixel = 0; pixel < (3*arraySizeX);pixel+=3)
			{

				   Line[pixel]   = 32000;     // R = X
					Line[pixel+1] = 32000;  //G = Y 
					Line[pixel+2] = 32000;   // B = Z
					//Line[pixel+3] = 65535;  // A
					
				// Write top block 
				if(line>=25 && line < 205){
					//+block
					if(pixel/3 >= 230 && pixel/3 < 410){
					   Line[pixel]   = 32000;     // R = X
						Line[pixel+1] = 32000+one;  //G = Y 
						Line[pixel+2] = 32000;   // B = Z					
					}
				
				}
				
				if(line>=25 && line < 205){
					//+block
					if((pixel/3 - 640) >= 230 && (pixel/3 - 640) < 410){
					   Line[pixel]   = 32000;     // R = X
						Line[pixel+1] = 32000;  //G = Y 
						Line[pixel+2] = 32000+one;   // B = Z					
					}
				
				}
				
				if(line>=25 && line < 205){
					//+block
					if((pixel/3 - 1280) >= 230 && (pixel/3 - 1280)< 410){
					   Line[pixel]   = 32000+one;     // R = X
						Line[pixel+1] = 32000;  //G = Y 
						Line[pixel+2] = 32000;   // B = Z					
					}
				
				}	
				
				
				// Write bottom block 
				if(line>=435 && line < 615){
					//+block
					if(pixel/3 >= 230 && pixel/3 < 410){
					   Line[pixel]   = 32000;     // R = X
						Line[pixel+1] = 32000-one;  //G = Y 
						Line[pixel+2] = 32000;   // B = Z					
					}
				
				}
				
				if(line>=435 && line < 615){
					//+block
					if((pixel/3 - 640) >= 230 && (pixel/3 - 640) < 410){
					   Line[pixel]   = 32000;     // R = X
						Line[pixel+1] = 32000;  //G = Y 
						Line[pixel+2] = 32000-one;   // B = Z					
					}
				
				}
				
				if(line>=435 && line < 615){
					//+block
					if((pixel/3 - 1280) >= 230 && (pixel/3 - 1280)< 410){
					   Line[pixel]   = 32000-one;     // R = X
						Line[pixel+1] = 32000;  //G = Y 
						Line[pixel+2] = 32000;   // B = Z					
					}
				
				}	
				
				
				
				// Write left block 
				if(line>=230 && line < 410){
					//+block
					if(pixel/3 >= 25 && pixel/3 < 205){
					   Line[pixel]   = 32000+one;     // R = X
						Line[pixel+1] = 32000-one;  //G = Y 
						Line[pixel+2] = 32000;   // B = Z					
					}
				
				}
				
				if(line>=230 && line < 410){
					//+block
					if((pixel/3 - 640) >= 25 && (pixel/3 - 640) < 205){
					   Line[pixel]   = 32000;     // R = X
						Line[pixel+1] = 32000+one;  //G = Y 
						Line[pixel+2] = 32000-one;   // B = Z					
					}
				
				}
				
				if(line>=230 && line < 410){
					//+block
					if((pixel/3 - 1280) >= 25 && (pixel/3 - 1280)< 205){
					   Line[pixel]   = 32000-one;     // R = X
						Line[pixel+1] = 32000;  //G = Y 
						Line[pixel+2] = 32000+one;   // B = Z					
					}
				
				}	
				
				
				// Write right block 
				if(line>=230 && line < 410){
					//+block
					if(pixel/3 >= 435 && pixel/3 < 615){
					   Line[pixel]   = 32000;     // R = X
						Line[pixel+1] = 32000+one;  //G = Y 
						Line[pixel+2] = 32000-one;   // B = Z					
					}
				
				}
				
				if(line>=230 && line < 410){
					//+block
					if((pixel/3 - 640) >= 435 && (pixel/3 - 640) < 615){
					   Line[pixel]   = 32000-one;     // R = X
						Line[pixel+1] = 32000;  //G = Y 
						Line[pixel+2] = 32000+one;   // B = Z					
					}
				
				}
				
				if(line>=230 && line < 410){
					//+block
					if((pixel/3 - 1280) >= 435 && (pixel/3 - 1280)< 615){
					   Line[pixel]   = 32000+one;     // R = X
						Line[pixel+1] = 32000-one;  //G = Y 
						Line[pixel+2] = 32000;   // B = Z					
					}
				
				}																					
					
			// Write sweep +/- 3%
			if(line >= 720){
				   Line[pixel]   = 32000-960+pixel/3;     // R = X
					Line[pixel+1] = 32000-960+pixel/3;  //G = Y 
					Line[pixel+2] = 32000-960+pixel/3;   // B = Z			
			}
			if(line >= 900){
				   Line[pixel]   = 32000-3840+4*pixel/3;     // R = X
					Line[pixel+1] = 32000-3840+4*pixel/3;  //G = Y 
					Line[pixel+2] = 32000-3840+4*pixel/3;   // B = Z			
			}			
			   

			}
			

			TIFFWriteRawStrip(tif, (tstrip_t)line, (tdata_t)Line, 4*arraySizeX*2);

		}		
		
		TIFFClose(tif);
		

}
	

// Functions

// 10000 nits
//  1/gamma-ish, calculate V from Luma
// decode L = (max(,0)/(c2-c3*V**(1/m)))**(1/n)
double PQ10000_f( double V)
{
  double L;
  // Lw, Lb not used since absolute Luma used for PQ
  // formula outputs normalized Luma from 0-1
  L = pow(max(pow(V, 1.0/78.84375) - 0.8359375 ,0.0)/(18.8515625 - 18.6875 * pow(V, 1.0/78.84375)),1.0/0.1593017578);

  return L;
}

// encode (V^gamma ish calculate L from V)
//  encode   V = ((c1+c2*Y**n))/(1+c3*Y**n))**m
double PQ10000_r( double L)
{
  double V;
  // Lw, Lb not used since absolute Luma used for PQ
  // input assumes normalized luma 0-1
  V = pow((0.8359375+ 18.8515625*pow((L),0.1593017578))/(1+18.6875*pow((L),0.1593017578)),78.84375);
  return V;
}
