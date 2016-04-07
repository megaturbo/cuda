#include "OpencvTools.h"
#include "ShapeOverlay.h"

using cv::Scalar;
using cv::Point;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void tuto_03_transparance();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static Mat provideImage();

static void fill(ShapeGroup* ptrShapeGroup, int w, int h);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void tuto_03_transparance()
    {
    Mat image = provideImage();

    ShapeGroup shapeGroup;
    fill(&shapeGroup, image.cols, image.rows);

    // sans transparence
   // ShapeDrawer shapeDrawer(image);
    //shapeDrawer.draw(&shapeGroup);

    // avec transparence
    // shapeOpacity01 = 0 	-->  shape invisible
    // shapeOpacity01 = 0.5 	-->  shape semi transparant
    // shapeOpacity01 = 1 	-->  shape 100% opaque
    float shapeOpacity01 = 0.25f;
    ShapeDrawerTransparant shapeDrawer(image, shapeOpacity01);
    shapeDrawer.draw(&shapeGroup);

    // Analyse Difference
    //   -  ShapeDrawer<-->ShapeDrawerTransparant
    //   -  shapeOpacity01
    //
    // Note : touts les shapes peuvent etre rendu sous forme transparente

    OpencvTools::showBGR(image, "Tuto 03 : Transparance");
    cv::waitKey();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void fill(ShapeGroup* ptrShapeGroup, int w, int h)
    {
    // Apparence
    int tickness = CV_FILLED; //Epaisseur du trait, si CV_FILLED forme remplie
    int lineType = 8; //par defaut
    Scalar colorBGR(0, 0, 255); //Red
    AppearanceShape apparence(colorBGR, tickness, lineType);

    // Geometry
    int x0 = w / 2;
    int y0 = h / 2;
    Point center(x0, y0);
    int radius = 400;

    // Aggregation
    Circle* ptrCircle = new Circle(&apparence, center, radius);
    ptrShapeGroup->add(ptrCircle);
    }

Mat provideImage()
    {
    string fileName = "resources/image_1600_1200.jpg";
    return OpencvTools::loadBGR(fileName);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

