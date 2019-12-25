
#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

//other includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>
#include <math.h>

#define PI 3.14159265

using namespace std;
typedef pair<double, double> Point;

class Shape{
public:
    void setnumSides(int n){
        numSides = n;
        return;
    }
    int getnumSides(){
        return numSides;
    }
    void setxCoor(double x){
        xCoor.push_back(x);

    }
    double getxCoor(int index){
        return xCoor[index];
    }
    vector<double> getWholeXCoor(){
        return xCoor;
    }
    vector<double> getWholeYCoor(){
        return yCoor;
    }
    void setyCoor(double y){
        yCoor.push_back(y);
    }
    double getyCoor(int index){
        return yCoor[index];
    }
    void setPoint(double x, double y) {
        point.push_back(make_pair(x, y));
        xCoor.push_back(x);
        yCoor.push_back(y);
    }
    void replacex(int index, double tx) {
        xCoor[index] = tx;
    }
    void replacey(int index, double ty) {
        yCoor[index] = ty;
    }
    void movex(int index, double tx) {
        xCoor[index] = xCoor[index] + tx;
    }
    void movey(int index, double ty) {
        yCoor[index] = yCoor[index] + ty;
    }
    Point getPoint(int index){
        return point[index];
    }
private:
    int numSides;
    vector<double> xCoor;
    vector<double> yCoor;
    vector<Point> point;
};


/****set in main()****/
//the number of pixels in the grid
int grid_width;
int grid_height;

//the size of pixels sets the inital window height and width
//don't make the pixels too large or the screen size will be larger than
//your display size
float pixel_size;

/*Window information*/
int win_height;
int win_width;


void init();
void idle();
void display0();
void display1();
void display2();
void display3();
void display4();
void draw_pix(int x, int y);
void reshape(int width, int height);
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void check();
void OpenFile();
void ReadFile(vector<Shape>& shapes, vector<Shape>& shapesrast);
void Bresenham ();
void DDA();

void Translation(Shape& shaperast, int tx, int ty);
void Scaling(Shape& shape, double factor);
void Rotation(Shape& shape, double angle);
void DrawShape();
void Rasterization();

int trans1, trans2;
int angle;
double factor = 0;
int numShapes;
int gloFactor = 1;
vector<Shape> shapes;
vector<Shape> shapesBackup;

vector<Shape> shapesrast;
char userInput, userInput2, userInput3;

double inf = std::numeric_limits<double>::infinity();

int main(int argc, char **argv)
{
    OpenFile();
    ReadFile(shapes, shapesrast);

    //the number of pixels in the grid
    grid_width = 100 ;
    grid_height = 100;

    //the size of pixels sets the inital window height and width
    //don't make the pixels too large or the screen size will be larger than
    //your display size
    pixel_size = 5;

    /*Window information*/
    win_height = grid_height*pixel_size;
    win_width = grid_width*pixel_size;

    cout << "Welcome to 2D-polygons! Choose which shape you want to control: type a number between 0 to 4 " << endl;
    cin >> userInput;
    while (userInput != '1' && userInput != '2' && userInput != '3' && userInput != '4' && userInput != '0') {
        cout << "Wrong input. Please type a number between 0 to 4." << endl;
        cin >> userInput;
    }
    cout << "Now type which algorithm you want to apply: (1) Bresenham (2) DDA" << endl;
    cin >> userInput2;
    while (userInput2 != '1' && userInput2 != '2') {
        cout << "Wrong input. Please type 1 or 2." << endl;
        cin >> userInput2;
    }
    if(userInput2 == '1') {
        Bresenham();
    } else if (userInput2 == '2') {
        DDA();
    }
    cout << "Choose if you want to rasterize the shape. ('y' or 'n')" << endl;
    cin >> userInput3;
    while (userInput3 != 'y' && userInput3 != 'n') {
        cout << "Wrong input. Please type y or n." << endl;
        cin >> userInput3;
    }
    if(userInput3 == 'y') {
        Rasterization();
    } else if (userInput3 == 'n') {

    }

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    /*initialize variables, allocate memory, create buffers, etc. */
    //create window of size (win_width x win_height
    glutInitWindowSize(win_width,win_height);
    //windown title is "glut demo"
    glutCreateWindow("glut demo");

    /*defined glut callback functions*/
    if(userInput == '0') {
        glutDisplayFunc(display0); //rendering calls here
    } else if (userInput == '1') {
        glutDisplayFunc(display1);
    } else if (userInput == '2') {
        glutDisplayFunc(display2);
    } else if (userInput == '3') {
        glutDisplayFunc(display3);
    } else if (userInput == '4') {
        glutDisplayFunc(display4);
    }

    glutReshapeFunc(reshape); //update GL on window size change
    glutMouseFunc(mouse);     //mouse button events
    glutMotionFunc(motion);   //mouse movement events
    glutKeyboardFunc(key);    //Keyboard events
    glutIdleFunc(idle);       //Function called while program is sitting "idle"

    //initialize opengl variables
    init();
    //start glut event loop
    glutMainLoop();
    return 0;
}

/*initialize gl stufff*/
void init()
{
    //set clear color (Default background to white)
    glClearColor(1.0,1.0,1.0,1.0);
    //checks for OpenGL errors
    check();
}

//called repeatedly when glut isn't doing anything else
void idle()
{
    //redraw the scene over and over again
    glutPostRedisplay();
}

//this is where we render the screen
int i = 1;
void display0()
{
    //clears the screen
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    //clears the opengl Modelview transformation matrix
    glLoadIdentity();

    //Scaling(shapesrast[4], 2);
    if (i % 10 == 0) {
        Translation(shapes[0], trans1, trans2);

        if(factor == 1.03) {
            Scaling(shapes[0], 1.03);
        }
        Rotation(shapes[0], angle);

    }

    i++;

    //Bresenham();
    //DrawShapeBre();
    DrawShape();

    //blits the current opengl framebuffer on the screen
    glutSwapBuffers();
    //checks for opengl errors
    check();
}
void display1()
{
    //clears the screen
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    //clears the opengl Modelview transformation matrix
    glLoadIdentity();

    //Scaling(shapesrast[4], 2);
    if (i % 10 == 0) {
        Translation(shapes[1], trans1, trans2);

        if(factor == 1.03) {
            Scaling(shapes[1], 1.03);
        }
        Rotation(shapes[1], angle);
        //DDA();
    }

    i++;

    //Bresenham();
    //DrawShapeBre();
    DrawShape();

    //blits the current opengl framebuffer on the screen
    glutSwapBuffers();
    //checks for opengl errors
    check();
}
void display2()
{
    //clears the screen
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    //clears the opengl Modelview transformation matrix
    glLoadIdentity();

    //Scaling(shapesrast[4], 2);
    if (i % 10 == 0) {
        Translation(shapes[2], trans1, trans2);

        if(factor == 1.03) {
            Scaling(shapes[2], 1.03);
        }
        Rotation(shapes[2], angle);
        //DDA();
    }

    i++;

    //Bresenham();
    //DrawShapeBre();
    DrawShape();

    //blits the current opengl framebuffer on the screen
    glutSwapBuffers();
    //checks for opengl errors
    check();
}
void display3()
{
    //clears the screen
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    //clears the opengl Modelview transformation matrix
    glLoadIdentity();

    //Scaling(shapesrast[4], 2);
    if (i % 10 == 0) {
        Translation(shapes[3], trans1, trans2);

        if(factor == 1.03) {
            Scaling(shapes[3], 1.03);
        }

        Rotation(shapes[3], angle);
        //DDA();
    }

    i++;

    //Bresenham();
    //DrawShapeBre();
    DrawShape();

    //blits the current opengl framebuffer on the screen
    glutSwapBuffers();
    //checks for opengl errors
    check();
}
void display4()
{
    //clears the screen
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    //clears the opengl Modelview transformation matrix
    glLoadIdentity();

    //Scaling(shapesrast[4], 2);
    if (i % 10 == 0) {
        Translation(shapes[4], trans1, trans2);

        if(factor == 1.03) {
            Scaling(shapes[4], 1.03);

        }

        Rotation(shapes[4], angle);
//        cout << "factor: " << factor << endl;
//        cout << "angle: " << angle << endl;
        //DDA();
    }

    i++;

    //Bresenham();
    //DrawShapeBre();
    DrawShape();

    //blits the current opengl framebuffer on the screen
    glutSwapBuffers();
    //checks for opengl errors
    check();
}


//Draws a single "pixel" given the current grid size
void draw_pix(int x, int y){
    glBegin(GL_POINTS);
    glColor3f(.2,.2,1.0);
    glVertex3f(x+.5,y+.5,0);
    glEnd();
}

/*Gets called when display size changes, including initial craetion of the display*/
void reshape(int width, int height)
{
    /*set up projection matrix to define the view port*/
    //update the ne window width and height
    win_width = width;
    win_height = height;

    //creates a rendering area across the window
    glViewport(0,0,width,height);
    // up an orthogonal projection matrix so that
    // the pixel space is mapped to the grid space
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,grid_width,0,grid_height,-10,10);

    //clear the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //set pixel size based on width, if the aspect ratio
    //changes this hack won't work as well
    pixel_size = width/(float)grid_width;

    //set pixel size relative to the grid cell size
    glPointSize(pixel_size);
    //check for opengl errors
    check();
}

//gets called when a key is pressed on the keyboard
void key(unsigned char ch, int x, int y)
{
    //rotate
    factor = 1;
    if (ch == 'r') {
        angle = 10;
        trans2 = 0;
        trans1 = 0;
        factor = 1;
    } else if (ch == 't') {

    } else if (ch == 'c') {
        factor = 1.03;
        angle = 0;
        trans2 = 0;
        trans1 = 0;
    } else if (ch == 'h') {
        angle = 0;
        trans2 = 0;
        trans1 = 0;
        factor = 1;
    } else if (ch == 'w') {
        trans2 = 1;
        trans1 = 0;
        angle = 0;
        factor = 1;
    } else if (ch == 's') {
        trans2 = -1;
        trans1 = 0;
        angle = 0;
        factor = 1;
    } else if (ch == 'a') {
        trans2 = 0;
        trans1 = -1;
        angle = 0;
        factor = 1;
    } else if (ch == 'd') {
        trans2 = 0;
        trans1 = 1;
        angle = 0;
        factor = 1;
    } else if (ch == 'n'){

    }else if (ch == 'e') {
        exit(1);
    }
    //redraw the scene after keyboard input
    glutPostRedisplay();
}

//gets called when a mouse button is pressed
void mouse(int button, int state, int x, int y)
{
    //print the pixel location, and the grid location
//    printf ("MOUSE AT PIXEL: %d %d, GRID: %d %d\n",x,y,(int)(x/pixel_size),(int)((win_height-y)/pixel_size));
//    switch(button)
//    {
//        case GLUT_LEFT_BUTTON: //left button
//            printf("LEFT ");
//            break;
//        case GLUT_RIGHT_BUTTON: //right button
//            printf("RIGHT ");
//        default:
//            printf("UNKNOWN "); //any other mouse button
//            break;
//    }
//    if(state !=GLUT_DOWN)  //button released
//        printf("BUTTON UP\n");
//    else
//        printf("BUTTON DOWN\n");  //button clicked

    //redraw the scene after mouse click
    glutPostRedisplay();
}

//gets called when the curser moves accross the scene
void motion(int x, int y)
{
    //redraw the scene after mouse movement
    glutPostRedisplay();
}

//checks for any opengl errors in the previous calls and
//outputs if they are present
void check()
{
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        printf("GLERROR: There was an error %s\n",gluErrorString(err) );
        exit(1);
    }
}

void OpenFile() {
    ifstream myReadFile;
    myReadFile.open("test_scene.txt");

    if (!myReadFile.is_open()) {
        cout << "trouble opeining the file" << endl;
    }
    myReadFile >> numShapes;

}
void ReadFile(vector<Shape>& shapes, vector<Shape>& shapesrast)
{
    int numShapesTemp;
    ifstream myReadFile;
    myReadFile.open("test_scene.txt");

    myReadFile >> numShapesTemp;
    int numSides[numShapesTemp];

    for(int i = 0; i < numShapesTemp; i++){//per shape itself
        Shape shape;
        Shape shaperast;
        shapes.push_back(shape);

        myReadFile >> numSides[i];
        shapes[i].setnumSides(numSides[i]);

        int w = 0;
        double tempx = 0;
        double tempy = 0;
        while (w < numSides[i]){
            myReadFile >>tempx >> tempy;
            shapes[i].setPoint(round(tempx + 0.5) * gloFactor, round(tempy + 0.5) * gloFactor);
            w++;
        }
    }

    return;
}

void Bresenham () {

    for(int i = 0; i < shapes.size(); ++i) {
        for (int j = 0; j < shapes[i].getnumSides(); ++j){
            /////////////first and last
            if(j == 0) {
                int xi, yi, xj, yj, xiPlus, yiPlus, pixI, pixIPlus, delx, dely, tempx, tempy;
                double m;
                xi = shapes[i].getxCoor(0);
                yi = shapes[i].getyCoor(j);
                xj = shapes[i].getxCoor(shapes[i].getnumSides() -1);
                yj = shapes[i].getyCoor(shapes[i].getnumSides() -1);
                delx = xj - xi;
                dely = yj - yi;
                m = double(dely) / double(delx);
                //0 < m < 1
                if(m >= 0 && m <= 1) {
                    if(xi > xj){
                        tempx = xi;
                        xi = xj;
                        xj = tempx;
                        tempy = yi;
                        yi = yj;
                        yj = tempy;
                        delx = delx * (-1);
                        dely = dely * (-1);
                    }

                    pixI = 2 * dely - delx;
                    if(pixI > 0) {
                        yiPlus = yi + 1;
                        xiPlus = xi + 1;
                    } else {
                        yiPlus = yi;
                        xiPlus = xi + 1;
                    }

                    shapes[i].setPoint(double(xiPlus), double(yiPlus));
                    for(int k = 1; k < abs(delx) - 1; ++k){
                        pixIPlus = pixI + 2 * dely - 2 * delx * (yiPlus - yi);
                        yi = yiPlus;
                        xi = xiPlus;
                        if (pixIPlus > 0) {
                            yiPlus = yiPlus + 1;
                            xiPlus = xiPlus + 1;
                        } else {
                            yiPlus = yiPlus;
                            xiPlus = xiPlus + 1;
                        }
                        shapes[i].setPoint(double(xiPlus), double(yiPlus));
                        pixI = pixIPlus;
                    }
                }

                // -1 < m < 0
                if(m < 0 && m >= -1) {
                    if(xi > xj){
                        tempx = xi;
                        xi = xj;
                        xj = tempx;
                        tempy = yi;
                        yi = yj;
                        yj = tempy;
                        delx = delx * (-1);
                        dely = dely * (-1);
                    }

                    pixI = 1 * (-2 * dely - delx);
                    if(pixI > 0) {
                        yiPlus = yi - 1;
                        xiPlus = xi + 1;
                    } else {
                        yiPlus = yi;
                        xiPlus = xi + 1;
                    }

                    shapes[i].setPoint(double(xiPlus), double(yiPlus));

                    for(int k = 1; k < abs(delx) - 1; ++k){
                        pixIPlus = 1 * (pixI - 2 * dely + 2 * delx * (yiPlus - yi));
                        yi = yiPlus;
                        xi = xiPlus;
                        if (pixIPlus > 0) {
                            yiPlus = yiPlus - 1;
                            xiPlus = xiPlus + 1;
                        } else {
                            yiPlus = yiPlus;
                            xiPlus = xiPlus + 1;
                        }

                        shapes[i].setPoint(double(xiPlus), double(yiPlus));

                        pixI = pixIPlus;
                    }
                }

                //m > 1
                if(m > 1) {
                    if(xi > xj){
                        tempx = xi;
                        xi = xj;
                        xj = tempx;
                        tempy = yi;
                        yi = yj;
                        yj = tempy;
                        delx = delx * (-1);
                        dely = dely * (-1);
                    }

                    pixI = 2 * delx - dely;
                    if(pixI > 0) {
                        xiPlus = xi + 1;
                        yiPlus = yi + 1;
                    } else {
                        xiPlus = xi;
                        yiPlus = yi + 1;
                    }

                    shapes[i].setPoint(double(xiPlus), double(yiPlus));

                    for(int k = 1; k < abs(dely) - 1; ++k){

                        pixIPlus = pixI + 2 * delx - 2 * dely * (xiPlus - xi);
                        yi = yiPlus;
                        xi = xiPlus;
                        if (pixIPlus > 0) {
                            yiPlus = yiPlus + 1;
                            xiPlus = xiPlus + 1;
                        } else {
                            yiPlus = yiPlus + 1;
                            xiPlus = xiPlus;
                        }

                        shapes[i].setPoint(double(xiPlus), double(yiPlus));

                        pixI = pixIPlus;
                    }
                }

                // m < -1
                if(m < -1) {
                    if(xi > xj){
                        tempx = xi;
                        xi = xj;
                        xj = tempx;
                        tempy = yi;
                        yi = yj;
                        yj = tempy;
                        delx = delx * (-1);
                        dely = dely * (-1);
                    }

                    pixI = 2 * delx + dely;
                    if(pixI > 0) {
                        xiPlus = xi + 1;
                        yiPlus = yi - 1;
                    } else {
                        xiPlus = xi;
                        yiPlus = yi - 1;
                    }

                    shapes[i].setPoint(double(xiPlus), double(yiPlus));

                    for(int k = 1; k < abs(dely) - 1; ++k){

                        pixIPlus = pixI + 2 * delx + 2 * dely * (xiPlus - xi);
                        yi = yiPlus;
                        xi = xiPlus;
                        if (pixIPlus > 0) {
                            yiPlus = yiPlus - 1;
                            xiPlus = xiPlus + 1;
                        } else {
                            yiPlus = yiPlus - 1;
                            xiPlus = xiPlus;
                        }
                        shapes[i].setPoint(double(xiPlus), double(yiPlus));
                        pixI = pixIPlus;
                    }
                }

            }
            ////////////////
            if(j != shapes[i].getnumSides() - 1) {
                int xi, yi, xj, yj, xiPlus, yiPlus, pixI, pixIPlus, delx, dely, tempx, tempy;
                double m;
                xi = shapes[i].getxCoor(j);
                yi = shapes[i].getyCoor(j);
                xj = shapes[i].getxCoor(j + 1);
                yj = shapes[i].getyCoor(j + 1);
                delx = xj - xi;
                dely = yj - yi;
                m = double(dely) / double(delx);

                //0 < m < 1
                if(m >= 0 && m <= 1) {
                    if(xi > xj){
                        tempx = xi;
                        xi = xj;
                        xj = tempx;
                        tempy = yi;
                        yi = yj;
                        yj = tempy;
                        delx = delx * (-1);
                        dely = dely * (-1);
                    }

                    pixI = 2 * dely - delx;
                    if(pixI > 0) {
                        yiPlus = yi + 1;
                        xiPlus = xi + 1;
                    } else {
                        yiPlus = yi;
                        xiPlus = xi + 1;
                    }
                    shapes[i].setPoint(double(xiPlus), double(yiPlus));

                    for(int k = 1; k < abs(delx) - 1; ++k){
                        pixIPlus = pixI + 2 * dely - 2 * delx * (yiPlus - yi);
                        yi = yiPlus;
                        xi = xiPlus;
                        if (pixIPlus > 0) {
                            yiPlus = yiPlus + 1;
                            xiPlus = xiPlus + 1;
                        } else {
                            yiPlus = yiPlus;
                            xiPlus = xiPlus + 1;
                        }
                        shapes[i].setPoint(double(xiPlus), double(yiPlus));
                        pixI = pixIPlus;
                    }
                }

                // -1 < m < 0
                if(m < 0 && m >= -1) {
                    if(xi > xj){
                        tempx = xi;
                        xi = xj;
                        xj = tempx;
                        tempy = yi;
                        yi = yj;
                        yj = tempy;
                        delx = delx * (-1);
                        dely = dely * (-1);
                    }

                    pixI = 1 * (-2 * dely - delx);
                    if(pixI > 0) {
                        yiPlus = yi - 1;
                        xiPlus = xi + 1;
                    } else {
                        yiPlus = yi;
                        xiPlus = xi + 1;
                    }
                    shapes[i].setPoint(double(xiPlus), double(yiPlus));
                    for(int k = 1; k < abs(delx) - 1; ++k){
                        pixIPlus = 1 * (pixI - 2 * dely + 2 * delx * (yiPlus - yi));
                        yi = yiPlus;
                        xi = xiPlus;
                        if (pixIPlus > 0) {
                            yiPlus = yiPlus - 1;
                            xiPlus = xiPlus + 1;
                        } else {
                            yiPlus = yiPlus;
                            xiPlus = xiPlus + 1;
                        }
                        shapes[i].setPoint(double(xiPlus), double(yiPlus));
                        pixI = pixIPlus;
                    }
                }

                //m > 1
                if(m > 1) {
                    if(xi > xj){
                        tempx = xi;
                        xi = xj;
                        xj = tempx;
                        tempy = yi;
                        yi = yj;
                        yj = tempy;
                        delx = delx * (-1);
                        dely = dely * (-1);
                    }

                    pixI = 2 * delx - dely;
                    if(pixI > 0) {
                        xiPlus = xi + 1;
                        yiPlus = yi + 1;
                    } else {
                        xiPlus = xi;
                        yiPlus = yi + 1;
                    }
                    shapes[i].setPoint(double(xiPlus), double(yiPlus));
                    for(int k = 1; k < abs(dely) - 1; ++k){
                        pixIPlus = pixI + 2 * delx - 2 * dely * (xiPlus - xi);
                        yi = yiPlus;
                        xi = xiPlus;
                        if (pixIPlus > 0) {
                            yiPlus = yiPlus + 1;
                            xiPlus = xiPlus + 1;
                        } else {
                            yiPlus = yiPlus + 1;
                            xiPlus = xiPlus;
                        }
                        shapes[i].setPoint(double(xiPlus), double(yiPlus));
                        pixI = pixIPlus;
                    }
                }

                // m < -1
                if(m < -1) {
                    if(xi > xj){
                        tempx = xi;
                        xi = xj;
                        xj = tempx;
                        tempy = yi;
                        yi = yj;
                        yj = tempy;
                        delx = delx * (-1);
                        dely = dely * (-1);
                    }
                    pixI = 2 * delx + dely;
                    if(pixI > 0) {
                        xiPlus = xi + 1;
                        yiPlus = yi - 1;
                    } else {
                        xiPlus = xi;
                        yiPlus = yi - 1;
                    }
                    shapes[i].setPoint(double(xiPlus), double(yiPlus));
                    for(int k = 1; k < abs(dely) - 1; ++k){
                        pixIPlus = pixI + 2 * delx + 2 * dely * (xiPlus - xi);
                        yi = yiPlus;
                        xi = xiPlus;
                        if (pixIPlus > 0) {
                            yiPlus = yiPlus - 1;
                            xiPlus = xiPlus + 1;
                        } else {
                            yiPlus = yiPlus - 1;
                            xiPlus = xiPlus;
                        }
                        shapes[i].setPoint(double(xiPlus), double(yiPlus));
                        pixI = pixIPlus;
                    }
                }

            }
        }
    }

}
void DDA(){
    double x0, y0, xi, yi, delx, dely;
    double xiPlus, yiPlus, m;
    for(int i = 0; i < shapes.size(); ++i) {

        for(int j = 0; j < shapes[i].getnumSides(); ++j) {
            //shapes[i].setPoint(<#double x#>, <#double y#>)

            if( j != shapes[i].getnumSides() - 1) {
                if(shapes[i].getxCoor(j) <= shapes[i].getxCoor(j + 1)){
                    xi = shapes[i].getxCoor(j);
                    yi = shapes[i].getyCoor(j);
                } else {
                    xi = shapes[i].getxCoor(j + 1);
                    yi = shapes[i].getyCoor(j + 1);
                }
                x0 = xi;
                y0 = yi;
                delx = shapes[i].getxCoor(j + 1) - shapes[i].getxCoor(j);
                dely = shapes[i].getyCoor(j + 1) - shapes[i].getyCoor(j);
                m = double(dely) / double(delx);

                if((m > 0 && m <=1) || (m < 0 && m >= -1)) {
                    for (int k = 1; k < abs(delx); k++) {
                        yiPlus = yi + m;
                        xiPlus = xi + 1;
                        shapes[i].setPoint(round(xiPlus), round(yiPlus));
                        xi = xiPlus;
                        yi = yiPlus;
                    }
                }
                if(m > 1) {
                    for (int k = 1; k < abs(dely); k++) {
                        yiPlus =yi + 1;
                        xiPlus = xi + 1/m;
                        shapes[i].setPoint(round(xiPlus), round(yiPlus));
                        xi = xiPlus;
                        yi = yiPlus;
                    }
                }
                if(m < -1) {
                    for (int k = 1; k < abs(dely); k++) {
                        yiPlus =yi - 1;
                        xiPlus = xi - 1/m;
                        shapes[i].setPoint(round(xiPlus), round(yiPlus));
                        xi = xiPlus;
                        yi = yiPlus;
                    }
                }
                if(m == 0) {
                    for (int k = 1; k < abs(delx); k++) {
                        yiPlus =yi;
                        xiPlus = xi + 1;
                        shapes[i].setPoint(round(xiPlus), round(yiPlus));
                        xi = xiPlus;
                        yi = yiPlus;
                    }
                }

            } else {
                if(shapes[i].getxCoor(0) <= shapes[i].getxCoor(shapes[i].getnumSides() - 1)){
                    xi = shapes[i].getxCoor(0);
                    yi = shapes[i].getyCoor(0);
                } else {
                    xi = shapes[i].getxCoor(shapes[i].getnumSides() - 1);
                    yi = shapes[i].getyCoor(shapes[i].getnumSides() - 1);
                }
                x0 = xi;
                y0 = yi;
                delx = shapes[i].getxCoor(shapes[i].getnumSides() - 1) - shapes[i].getxCoor(0);
                dely = shapes[i].getyCoor(shapes[i].getnumSides() - 1) - shapes[i].getyCoor(0);
                m = double(dely) / double(delx);

                if((m > 0 && m <=1) || (m < 0 && m >= -1)) {
                    for (int k = 1; k < abs(delx); k++) {
                        yiPlus =yi + m;
                        xiPlus = xi + 1;
                        shapes[i].setPoint(round(xiPlus), round(yiPlus));
                        xi = xiPlus;
                        yi = yiPlus;
                    }
                }
                if(m > 1) {
                    for (int k = 1; k < abs(dely); k++) {
                        yiPlus =yi + 1;
                        xiPlus = xi + 1/m;
                        shapes[i].setPoint(round(xiPlus), round(yiPlus));
                        xi = xiPlus;
                        yi = yiPlus;
                    }
                }
                if(m < -1) {
                    for (int k = 1; k < abs(dely); k++) {
                        yiPlus =yi - 1;
                        xiPlus = xi - 1/m;
                        shapes[i].setPoint(round(xiPlus), round(yiPlus));
                        xi = xiPlus;
                        yi = yiPlus;
                    }
                }
                if(m == 0) {
                    for (int k = 1; k < abs(delx); k++) {
                        yiPlus =yi;
                        xiPlus = xi + 1;
                        shapes[i].setPoint(round(xiPlus), round(yiPlus));
                        xi = xiPlus;
                        yi = yiPlus;
                    }
                }
            }

        }
    }
    return;
}

void Translation(Shape& shape, int tx, int ty) {
    for (int j = 0; j < shape.getWholeXCoor().size(); ++j) {
        shape.movex(j, tx);
        shape.movey(j, ty);
    }
    return;
}
void Scaling(Shape& shape, double factor) {
    //find centroid
    //FIXME:: int or double?
    double centx = 0;
    double centy = 0;
    double tempx = 0;
    double tempy = 0;
    for(int i = 0; i < shape.getWholeXCoor().size(); ++i) {
        centx = centx + shape.getxCoor(i);
        centy = centy + shape.getyCoor(i);
    }
    centx = centx / shape.getWholeXCoor().size();
    centy = centy / shape.getWholeYCoor().size();
    //cout << "centx: " << centx << ", centy: " << centy << endl;
    //move to origin
    //FIXME::move shape or shaperast
    for(int i = 0; i < shape.getWholeXCoor().size(); ++i) {
        shape.movex(i, -centx);
        shape.movey(i, -centy);
    }
//    shape.getxCoor(i)
    //rotate
    for(int i = 0; i < shape.getWholeXCoor().size(); ++i) {
        tempx = shape.getxCoor(i) * factor;
        tempy = shape.getyCoor(i) * factor;
        shape.replacex(i, tempx);
        shape.replacey(i, tempy);
    }
    //move back
    for(int i = 0; i < shape.getWholeXCoor().size(); ++i) {
        shape.movex(i, centx);
        shape.movey(i, centy);
    }
    //getchar();
}
void Rotation(Shape& shape, double angle) {
    //find centroid
    //FIXME:: int or double?
    double centx = 0;
    double centy = 0;
    double tempx, tempy;
    for(int i = 0; i < shape.getWholeXCoor().size(); ++i) {
        centx = centx + shape.getxCoor(i);
        centy = centy + shape.getyCoor(i);
    }
    centx = centx / shape.getWholeXCoor().size();
    centy = centy / shape.getWholeYCoor().size();
    //cout << "centx: " << centx << ", centy: " << centy << endl;
    //move to origin
    //FIXME::move shape or shaperast
    for(int i = 0; i < shape.getWholeXCoor().size(); ++i) {
        shape.movex(i, -centx);
        shape.movey(i, -centy);
    }

    //rotate
    for(int i = 0; i < shape.getWholeXCoor().size(); ++i) {
        tempx = shape.getxCoor(i) * cos(angle*PI/180) - shape.getyCoor(i) * sin (angle*PI/180);
        tempy = shape.getxCoor(i) * sin (angle*PI/180) + shape.getyCoor(i) * cos(angle*PI/180);
        shape.replacex(i, tempx);
        shape.replacey(i, tempy);
    }
    //move back
    for(int i = 0; i < shape.getWholeXCoor().size(); ++i) {
        shape.movex(i, centx);
        shape.movey(i, centy);
    }
    //DDA();
}
void DrawShape() {
    for(int i = 0; i < shapes.size(); ++i) {
        for (int j = 0; j < shapes[i].getWholeXCoor().size(); ++j) {
            draw_pix(shapes[i].getxCoor(j), shapes[i].getyCoor(j));
        }
    }

}
void Rasterization(){
    double ymin, ymax, xmin, xmax, yin, xin, delx, dely;
    int crossNum;
    vector<double> crossPointsXCoor;
    for (int i = 0 ; i < shapes.size(); ++i) {
        crossNum = 0;
        //get ymin and ymax
        ymin = shapes[i].getWholeYCoor()[0];
        ymax = shapes[i].getWholeYCoor()[0];
        for (int j = 0; j < shapes[i].getnumSides(); ++j){
            if(shapes[i].getWholeYCoor()[j] < ymin){
                ymin = shapes[i].getWholeYCoor()[j];
            }
            if(shapes[i].getWholeYCoor()[j] > ymax){
                ymax = shapes[i].getWholeYCoor()[j];
            }
        }

        //begin from bottom to top
        for (int k = ymin; k < ymax; ++k) {
            crossPointsXCoor.clear();
            for (int l = 0; l < shapes[i].getWholeYCoor().size(); ++l) {
                //if y = y, add relative x to vector
                if (shapes[i].getWholeYCoor()[l] == k) {
                    crossPointsXCoor.push_back(shapes[i].getWholeXCoor()[l]);
                }
            }
            //then if num = 2, from left implement to right
            if(crossPointsXCoor.size() == 2){
                if(crossPointsXCoor[0] > crossPointsXCoor[1]){
                    xmin = crossPointsXCoor[1];
                    xmax = crossPointsXCoor[0];
                } else if (crossPointsXCoor[0] < crossPointsXCoor[1]){
                    xmin = crossPointsXCoor[0];
                    xmax = crossPointsXCoor[1];
                } else{
                    xmin = -1;
                    xmax = -1;
                }
                delx = abs(xmax - xmin);

                if(xmin != -1 && xmax != -1){
                    for (int m = xmin; m <= xmax; ++m) {
                        shapes[i].setPoint(m, k);
                    }
                }

            } else {
                //if 3, judge them, if more,
                sort(crossPointsXCoor.begin(), crossPointsXCoor.end());
                int countCross = 0;
                int del = 0;
                vector<int> indexCross;
                indexCross.clear();
                for (int l = 0; l < crossPointsXCoor.size() - 1; ++l) {
                    del = crossPointsXCoor[l + 1] - crossPointsXCoor[l];
                    if(del > 1){
                        countCross++;
                        indexCross.push_back(l);
                    }
                }
                if(countCross == 1){
                    //one blank, imple from l to l + 1
                    for (int l = crossPointsXCoor[indexCross[0]]; l < crossPointsXCoor[indexCross[0] + 1]; ++l) {
                        shapes[i].setPoint(l, k);
                    }
                } else if (countCross == 2) {
                    int countSameLine = 0;
                    //judge if itself input point the same line
                    for (int l = 0; l < shapes[i].getnumSides(); ++l) {
                        if(k == shapes[i].getWholeYCoor()[l]){
                            countSameLine++;
                        }
                    }
                    if(countSameLine == 2){
                        for (int l = crossPointsXCoor[indexCross[0]]; l < crossPointsXCoor[indexCross[0] + 1]; ++l) {
                            shapes[i].setPoint(l, k);
                        }
                    } else {
                        for (int l = crossPointsXCoor[indexCross[0]]; l < crossPointsXCoor[indexCross[0] + 1]; ++l) {
                            shapes[i].setPoint(l, k);
                        }
                        for (int l = crossPointsXCoor[indexCross[1]]; l < crossPointsXCoor[indexCross[1] + 1]; ++l) {
                            shapes[i].setPoint(l, k);
                        }
                    }
                    //two blank, both. [0] to [0]+1 and [1] to [1] + 1

                } else if (countCross == 3) {
                    for (int l = crossPointsXCoor[indexCross[0]]; l < crossPointsXCoor[indexCross[0] + 1]; ++l) {
                        shapes[i].setPoint(l, k);
                    }
                    for (int l = crossPointsXCoor[indexCross[2]]; l < crossPointsXCoor[indexCross[2] + 1]; ++l) {
                        shapes[i].setPoint(l, k);
                    }
                }
            }


        }


    }

}