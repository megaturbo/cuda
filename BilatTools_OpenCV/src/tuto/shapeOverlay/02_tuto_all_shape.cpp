#include <math.h>
#include <iostream>

#include "ShapeOverlay.h"
#include "OpencvTools.h"


#ifndef M_PI
#define M_PI 3.14
#endif

using cv::Scalar;
using cv::Point;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void tuto_02_allShape();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static Mat provideImage();

static void fill(ShapeGroup* ptrShapeGroup);

static void drawCircle(ShapeGroup* ptrShapeGroup);
static void drawRectangle(ShapeGroup* ptrShapeGroup);
static void drawLines(ShapeGroup* ptrShapeGroup);
static void drawTriangles(ShapeGroup* ptrShapeGroup);
static void drawPolygon(ShapeGroup* ptrShapeGroup);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void tuto_02_allShape()
    {
    ShapeGroup shapeGroup;
    fill(&shapeGroup);

    Mat image = provideImage();
    ShapeDrawer shapeDrawer(image);
    shapeDrawer.draw(&shapeGroup);

    OpencvTools::showBGR(image, "Tuto 02 : All shapes samples");
    cv::waitKey();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void fill(ShapeGroup* ptrShapeGroup)
    {
    drawLines(ptrShapeGroup);
    drawCircle(ptrShapeGroup);
    drawRectangle(ptrShapeGroup);
    drawTriangles(ptrShapeGroup);
    drawPolygon(ptrShapeGroup);
    }

void drawLines(ShapeGroup* ptrShapeGroup)
    {
    // Apparence
    int tickness = 4; //Epaisseur du trait, sauf CV_FILLED!
    int lineType = 8; //par defaut
    Scalar colorBGR(0, 255, 255);
    AppearanceShape apparance(colorBGR, tickness, lineType);

    // Geometry
    int x1 = 100;
    int y1 = 10;
    int x2 = 100;
    int y2 = 400;
    Point p1(x1, y1);
    Point p2(x2, y2);

    // Aggregation
    Line* ptrLine = new Line(&apparance, p1, p2);
    ptrShapeGroup->add(ptrLine);
    }

void drawCircle(ShapeGroup* ptrShapeGroup)
    {
    // Draw red plein circle
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

	// Agregation
	Circle* ptrCircle = new Circle(&apparance, center, radius);
	ptrShapeGroup->add(ptrCircle);
	}

    // Draw green wired Circle
	{
	// Apparence
	int tickness = 5; //Epaisseur du trait, si CV_FILLED forme remplie
	Scalar colorCircleBGR(0, 255, 0); // Green
	AppearanceShape apparance(colorCircleBGR, tickness);

	// Geometry
	int x0 = 300;
	int y0 = 100;
	Point center(x0, y0);
	int radius = 50;

	// Aggregation
	Circle* ptrCircle = new Circle(&apparance, center, radius);
	ptrShapeGroup->add(ptrCircle);
	}
    }

void drawRectangle(ShapeGroup* ptrShapeGroup)
    {
    // Apparence
    int tickness = CV_FILLED; //Epaisseur du trait, si CV_FILLED forme remplie
    Scalar colorBGR(255, 0, 0); // Blue
    AppearanceShape apparance(colorBGR, tickness);

    // Geometry
    int x0 = 600;
    int y0 = 100;
    Point center(x0, y0);
    int w = 200;
    int h = 100;

    // Aggregation
    Rectangle* ptrRectangle = new Rectangle(&apparance, center, w, h);
    ptrShapeGroup->add(ptrRectangle);
    }

void drawTriangles(ShapeGroup* ptrShapeGroup)
    {
    // Apparence
    int tickness = CV_FILLED; //Epaisseur du trait, si CV_FILLED forme remplie
    Scalar colorBGR(128, 128, 128); // Gray05
    AppearanceShape apparance(colorBGR, tickness);

    // Geometry
    int x1 = 800;
    int y1 = 400;
    int x2 = 800;
    int y2 = 700;
    int x3 = 900;
    int y3 = 750;
    Point p1(x1, y1);
    Point p2(x2, y2);
    Point p3(x3, y3);

    // Aggregation
    Triangle* ptrTriangle = new Triangle(&apparance, p1, p2, p3);
    ptrShapeGroup->add(ptrTriangle);
    }

void drawPolygon(ShapeGroup* ptrShapeGroup)
    {
    // Apparence
    int tickness = CV_FILLED; //Epaisseur du trait, si CV_FILLED forme remplie
    Scalar colorBGR(128, 255, 128); // Gray05
    AppearanceShape apparance(colorBGR, tickness);

    // Geometry
    int nbPoint = 10;
    Point* tabPoint = new cv::Point[nbPoint];

    int x0 = 500;
    int y0 = 500;
    double dAlpha = 2 * M_PI / nbPoint;
    double alpha = 0;
    int rayon = 200;
    for (int i = 0; i < nbPoint; i++)
	{
	int x = x0 + rayon * cos(alpha);
	int y = y0 + rayon * sin(alpha);
	Point p(x, y);
	tabPoint[i] = p;
	alpha += dAlpha;
	}

    //Aggregation
    Polygon* ptrPolygon = new Polygon(&apparance, tabPoint, nbPoint);
    ptrShapeGroup->add(ptrPolygon);
    }

Mat provideImage()
    {
    string fileName = "resources/image_1600_1200.jpg";
    return OpencvTools::loadBGR(fileName);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

