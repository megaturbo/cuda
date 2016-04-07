#include <iostream>

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Importation 					*|
 \*---------------------------------------------------------------------*/

extern void useWebcam(int w, int h, int deviceID);
extern void useVideo(string nameFile);

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useCapture();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static string nameVideo();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useCapture()
    {
    int n=1;
    for (int i = 1; i <= n; i++)
	{
	// video
	    {
	    useVideo(nameVideo());
	    }

	// webcam
	    {
	    int w = 1280;
	    int h = 1024;
	    int deviceID = 0;

	    useWebcam(w, h, deviceID);
	    }
	}

    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

string nameVideo()
    {
    // Important de tester en haute definition (autoroute.mp4) pour vallider la dll ffmpeg
    // petite video ne l'utilise pas!

#ifdef _WIN32
    // Work
    // string nameVideo ="Q:\\neilPryde.avi";
   //string nameVideo = "C:\\Users\\cedric.bilat\\Desktop\\neilPryde.avi";// ok
     string nameVideo="C:\\Users\\cedric.bilat\\Desktop\\autoroute.mp4";//ok

    // Home
     //  string nameVideo = "C:\\Users\\bilat\\Desktop\\neilPryde.avi"; // ok
   // string nameVideo="C:\\Users\\bilat\\Desktop\\autoroute.mp4";// ok
#elif  __arm__
    // string nameVideo="/opt/data/neilPryde.avi"; //ok
    string nameVideo = "/opt/data/autoroute.mp4";// ok
#else
    //string nameVideo = "/media/Data/Video/neilPryde.avi"; // ok
    string nameVideo = "/media/Data/Video/autoroute.mp4"; // ok
#endif

   // cout<<"[use video] : "<<nameVideo<<endl;

    return nameVideo;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

