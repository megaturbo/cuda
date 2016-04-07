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

void tuto_01_simple();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static Mat provideImage();

static void fill(ShapeGroup* ptrShapeGroup);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void tuto_01_simple()
    {
    ShapeGroup shapeGroup;
    fill(&shapeGroup);

    Mat image = provideImage();
    ShapeDrawer shapeDrawer(image);
    shapeDrawer.draw(&shapeGroup);

    OpencvTools::showBGR(image, "Tuto 01 : simple circle");
    cv::waitKey();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void fill(ShapeGroup* ptrShapeGroup)
    {
    // Apparence
    int tickness = CV_FILLED; //Epaisseur du trait, si CV_FILLED forme remplie
    int lineType = 8; //par defaut
    Scalar colorBGR(0, 0, 255); //Red
    AppearanceShape apparance(colorBGR, tickness, lineType);

    // Geometry
    int x0 = 300;
    int y0 = 100;
    Point center(x0, y0);
    int radius = 50;

    // Aggregation
    Circle* ptrCircle = new Circle(&apparance, center, radius);
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

