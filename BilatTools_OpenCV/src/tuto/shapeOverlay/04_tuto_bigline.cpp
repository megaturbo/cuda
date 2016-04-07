#include "ShapeOverlay.h"
#include "OpencvTools.h"


using cv::Scalar;
using cv::Point;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void tuto_04_bigline();

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

void tuto_04_bigline()
    {
    ShapeGroup shapeGroup;
    fill(&shapeGroup);

    Mat image = provideImage();
    ShapeDrawer shapeDrawer(image);
    shapeDrawer.draw(&shapeGroup);

    OpencvTools::showBGR(image, "Tuto 04 : draw big lines");
    cv::waitKey();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void fill(ShapeGroup* ptrShapeGroup)
    {
    // Apparence
    int tickness = 150; //Epaisseur du trait, ne fonctionnerais pas avec les shapes Line!
    Scalar colorBGR(0, 0, 255); //Red

    // Geometry
    Point p1(0, 0);
    Point p2(650, 700);

    LineDrawer bigLineDrawer;
    bigLineDrawer.drawLine(ptrShapeGroup, p1, p2, colorBGR, tickness);
    }

Mat provideImage()
    {
    string fileName = "resources/image_1600_1200.jpg";
    return OpencvTools::loadBGR(fileName);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

