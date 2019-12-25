

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
#include <ctype.h>

#define PI 3.14159265

using namespace std;
typedef pair<double, double> Point;

class Shape {
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
    void setyCoor(double y){
        yCoor.push_back(y);
    }
    double getyCoor(int index){
        return yCoor[index];
    }
    void setzCoor(double z){
        zCoor.push_back(z);
    }
    double getzCoor(int index){
        return zCoor[index];
    }
    vector<double> getWholeXCoor(){
        return xCoor;
    }
    vector<double> getWholeYCoor(){
        return yCoor;
    }
    vector<double> getWholeZCoor(){
        return zCoor;
    }
    void setPointXYZ(double x, double y, double z) {
        xCoor.push_back(x);
        yCoor.push_back(y);
        zCoor.push_back(z);
    }

    void replacex(int index, double tx) {
        xCoor[index] = tx;
    }
    void replacey(int index, double ty) {
        yCoor[index] = ty;
    }
    void replacez(int index, double tz) {
        zCoor[index] = tz;
    }
    void movex(int index, double tx) {
        xCoor[index] = xCoor[index] + tx;
    }
    void movey(int index, double ty) {
        yCoor[index] = yCoor[index] + ty;
    }
    void movez(int index, double tz) {
        zCoor[index] = zCoor[index] + tz;
    }

private:
    int numSides;
    vector<double> xCoor;
    vector<double> yCoor;
    vector<double> zCoor;
    vector<Point> pointxy;
    vector<Point> pointyz;
    vector<Point> pointxz;
};

typedef pair<double, double> EdgeToEdge;
class Edge {
public:
    void setNumEdges(int numEdge){
        numEdges = numEdge;
    }
    int getNumEdges(){
        return numEdges;
    }
    void setEdge1(int ed1) {
        edge1.push_back(ed1);
    }
    void setEdge2(int ed2) {
        edge2.push_back(ed2);
    }
    void setAllEdges(int ed1, int ed2){
        edgeToEdge.push_back(make_pair(ed1, ed2));
        edge1.push_back(ed1);
        edge2.push_back(ed2);
    }
    int getEdge1(int index){
        return edge1[index];
    }
    int getEdge2(int index){
        return edge2[index];
    }

private:
    int numEdges;
    vector<int> edge1;
    vector<int> edge2;
    vector<EdgeToEdge> edgeToEdge;
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
void displayMain();

void draw_pix(int x, int y);
void reshape(int width, int height);
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void check();
void OpenFile();
void ReadFile(vector<Shape>& shapes, vector<Edge>& edges);

void LineFillingXY();
void LineFillingXZ();
void LineFillingYZ();

void Translation(Shape& shape);
void Scaling(Shape& shape);
void Rotation(Shape& shape);

void ChangeShape();
void OutputFile();

string file;
double factorBegining = 700;
int numShapes;
vector<Shape> shapes;
vector<Edge> edges;
int indexChanged;


double inf = std::numeric_limits<double>::infinity();

int main(int argc, char **argv)
{
    OpenFile();
    ReadFile(shapes, edges);
    //set index to be changed is 1

    //User menu
    cout << "Welcome to 3D polygons! There are " << numShapes << " shape(s) in the file." << endl;
    cout << "Start the program by using the key on screen. Obey Readme.txt.\n" << endl;
    //the number of pixels in the grid
    grid_width = factorBegining;
    grid_height = factorBegining;

    //the size of pixels sets the inital window height and width
    //don't make the pixels too large or the screen size will be larger than
    //your display size
    pixel_size = 1;

    /*Window information*/
    win_height = grid_height*pixel_size;
    win_width = grid_width*pixel_size;

    /*Set up glut functions*/
    /** See https://www.opengl.org/resources/libraries/glut/spec3/spec3.html ***/


    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    /*initialize variables, allocate memory, create buffers, etc. */
    //create window of size (win_width x win_height
    glutInitWindowSize(win_width,win_height);
    //windown title is "glut demo"
    int mainWindow = glutCreateWindow("glut demo");
    glutSetWindow(mainWindow);
    glutDisplayFunc(displayMain);


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
int controlTime = 0;
void displayMain()
{
    //clears the screen
    glClearColor(1.0, 1.0, 1.0,1.0);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
//    //clears the opengl Modelview transformation matrix
    glLoadIdentity();

    //draw the grid line

    //glViewport(0, grid_width/2, grid_width/2, grid_width/2);

    //draw xy, yz, and xz
    LineFillingXY();
    LineFillingXZ();
    LineFillingYZ();
    //DrawShapeXY();
    //blits the current opengl framebuffer on the screen
    glutSwapBuffers();
    //checks for opengl errors
    check();
}


//Draws a single "pixel" given the current grid size
//don't change anything in this for project 1
void draw_pix(int x, int y){
    glBegin(GL_POINTS);
    glColor3f(0,0,.5);
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
int j = 1;
void key(unsigned char ch, int x, int y)
{
    //rotate

    if (ch == 'e') {
        //OutputFile();
        exit(1);
    } else if (ch == 't') {
        cout << "Now translating." << endl;
        ChangeShape();
        Translation(shapes[indexChanged]);
        OutputFile();
    } else if (ch == 's') {
        cout << "Now scaling." << endl;
        ChangeShape();
        Scaling(shapes[indexChanged]);
        OutputFile();
    } else if (ch == 'r') {
        cout << "Now rotating." << endl;
        ChangeShape();
        Rotation(shapes[indexChanged]);
        OutputFile();
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
    cout << "Type the file you want to open: \n";
    cin >> file;
    ifstream myReadFile;
    myReadFile.open(file);

    while (!myReadFile.is_open()) {
        cout << "trouble opening the file" << endl;
        cin >> file;
        myReadFile.open(file);
    }

//    if (myReadFile.is_open()) {
//        cout << "open file successfully" << endl;
//    } else {
//        cout << "trouble opening the file" << endl;
//    }
    myReadFile >> numShapes;

}

void ReadFile(vector<Shape>& shapes, vector<Edge>& edges) {
    int numShapesTemp;
    int numShapesEdgeTemp;
    int numEdgesTemp;
    ifstream myReadFile;
    myReadFile.open(file);

    myReadFile >> numShapesTemp;

    for(int i = 0; i < numShapesTemp; i++){//per shape itself
        Shape shape;
        Edge edge;
        shapes.push_back(shape);
        edges.push_back(edge);
        //shape
        myReadFile >> numShapesEdgeTemp;
        shapes[i].setnumSides(numShapesEdgeTemp);

        int w = 0;
        double tempx = 0;
        double tempy = 0;
        double tempz = 0;
        while (w < numShapesEdgeTemp){
            myReadFile >> tempx >> tempy >> tempz;
            shapes[i].setPointXYZ((tempx * factorBegining),
                    (tempy * factorBegining), (tempz * factorBegining));
            w++;
        }
        //edge
        myReadFile >> numEdgesTemp;
        edges[i].setNumEdges(numEdgesTemp);
        int h = 0;
        int edge1Temp = 0;
        int edge2Temp = 0;
        while (h < numEdgesTemp) {
            myReadFile >> edge1Temp >> edge2Temp;
            edges[i].setAllEdges(edge1Temp, edge2Temp);
            h++;
        }
    }

    return;
}


void LineFillingXY(){
    glViewport(0, win_height/2, win_width/2, win_height/2);
    double x1, x2, y1, y2, z1, z2;
    for(int i = 0; i < numShapes; ++i) {
        for(int j = 0; j < edges[i].getNumEdges(); j++){
            x1 = shapes[i].getxCoor(edges[i].getEdge1(j) - 1);
            y1 = shapes[i].getyCoor(edges[i].getEdge1(j) - 1);
            z1 = shapes[i].getzCoor(edges[i].getEdge1(j) - 1);

            x2 = shapes[i].getxCoor(edges[i].getEdge2(j) - 1);
            y2 = shapes[i].getyCoor(edges[i].getEdge2(j) - 1);
            z2 = shapes[i].getzCoor(edges[i].getEdge2(j) - 1);

            glBegin(GL_LINES);
            //glViewport(0, grid_width/2, grid_width/2, grid_width/2);
            glColor3f(0.4,0.4, 0);
            glVertex2f(x1, y1 );
            glVertex2f(x2, y2 );
            glEnd();
        }
    }
}

void LineFillingXZ(){
    glViewport(win_width/2 , win_height/2, win_width/2, win_height/2);
    glBegin(GL_LINES);
    glColor3f(0,0, 0);
    glVertex2f(0, 0);
    glVertex2f(0, grid_height);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0,0, 0);
    glVertex2f(0, 0);
    glVertex2f(grid_width, 0);
    glEnd();
    double x1, x2, y1, y2, z1, z2;
    for(int i = 0; i < numShapes; ++i) {
        for(int j = 0; j < edges[i].getNumEdges(); j++){
            x1 = shapes[i].getxCoor(edges[i].getEdge1(j) - 1);
            y1 = shapes[i].getyCoor(edges[i].getEdge1(j) - 1);
            z1 = shapes[i].getzCoor(edges[i].getEdge1(j) - 1);

            x2 = shapes[i].getxCoor(edges[i].getEdge2(j) - 1);
            y2 = shapes[i].getyCoor(edges[i].getEdge2(j) - 1);
            z2 = shapes[i].getzCoor(edges[i].getEdge2(j) - 1);

            glBegin(GL_LINES);
            glColor3f(0.6,0, .4);
            glVertex2f(x1, z1);
            glVertex2f(x2 , z2);
            glEnd();
        }
    }
}

void LineFillingYZ(){
    glViewport(0, 0, win_width/2, win_height/2);
    glBegin(GL_LINES);
    glColor3f(0,0, 0);
    glVertex2f(grid_width, 0);
    glVertex2f(grid_width, grid_height);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0,0, 0);
    glVertex2f(0, grid_height);
    glVertex2f(grid_width, grid_height);
    glEnd();
    double x1, x2, y1, y2, z1, z2;
    for(int i = 0; i < numShapes; ++i) {
        for(int j = 0; j < edges[i].getNumEdges(); j++){
            x1 = shapes[i].getxCoor(edges[i].getEdge1(j) - 1);
            y1 = shapes[i].getyCoor(edges[i].getEdge1(j) - 1);
            z1 = shapes[i].getzCoor(edges[i].getEdge1(j) - 1);

            x2 = shapes[i].getxCoor(edges[i].getEdge2(j) - 1);
            y2 = shapes[i].getyCoor(edges[i].getEdge2(j) - 1);
            z2 = shapes[i].getzCoor(edges[i].getEdge2(j) - 1);

            glBegin(GL_LINES);
            glColor3f(0,0.6, .4);
            glVertex2f(y1, z1);
            glVertex2f(y2, z2);
            glEnd();
        }
    }
}


void Translation(Shape& shape) {
    double tx, ty, tz, ux, uy, uz;
    cout << "Type x and y and z to move: " << endl;
    cin >> tx >> ty >> tz;
    ux = sqrt(tx*tx + ty*ty + tz*tz);

    for (int j = 0; j < shape.getWholeXCoor().size(); ++j) {
        shape.movex(j, tx);
        shape.movey(j, ty);
        shape.movez(j, tz);
        }

    cout << "Done and file has been updated.  ...wait for your next step...\n" << endl;
    return;
}

void Scaling(Shape& shape) {
    //find centroid
    //FIXME:: int or double?
    double scaleFactor;
    cout << "Type the factor: " << endl;
    cin >> scaleFactor;

    double centx = 0;
    double centy = 0;
    double centz = 0;
    double tempx = 0;
    double tempy = 0;
    double tempz = 0;

    for(int i = 0; i < shape.getnumSides(); ++i) {
        centx = centx + shape.getxCoor(i);
        centy = centy + shape.getyCoor(i);
        centz = centz + shape.getzCoor(i);
    }
    centx = centx / shape.getnumSides();
    centy = centy / shape.getnumSides();
    centz = centz / shape.getnumSides();

    //move to origin
    //FIXME::move shape or shaperast
    for(int i = 0; i < shape.getnumSides(); ++i) {
        shape.movex(i, -centx);
        shape.movey(i, -centy);
        shape.movez(i, -centz);
    }

    //scaling
    for(int i = 0; i < shape.getnumSides(); ++i) {
        tempx = shape.getxCoor(i) * scaleFactor;
        tempy = shape.getyCoor(i) * scaleFactor;
        tempz = shape.getzCoor(i) * scaleFactor;
        shape.replacex(i, tempx);
        shape.replacey(i, tempy);
        shape.replacez(i, tempz);
    }
    //move back
    for(int i = 0; i < shape.getnumSides(); ++i) {
        shape.movex(i, centx);
        shape.movey(i, centy);
        shape.movez(i, centz);
    }
    cout << "Done and file has been updated.  ...wait for your next step...\n" << endl;
    return;
}

void Rotation(Shape& shape) {
    double angle, radian, ux, uy, uz, x1, y1, z1, x2, y2, z2, p1p2, xt, yt, zt,
    x3, y3, z3, x4, y4, z4, x5, y5, z5, delx, dely, delz, tempx, tempy, tempz;
    double angleA, angleB;
    cout << "Type in sequence of angle(degree), "
            "xyz coordinates of point 1 and point 2(x1, y1, z1, x2, y2, z2)" << endl;
    cin >> angle >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

    //draw the axis xy, yz, xz
    delx = x2 - x1;
    dely = y2 - y1;
    delz = z2 - z1;
    radian = angle * PI / 180;
    p1p2 = sqrt(delx * delx + dely * dely + delz * delz);
    ux = delx / p1p2;
    uy = dely / p1p2;
    uz = delz / p1p2;

    for (int i = 0; i < shape.getnumSides(); ++i) {
        tempx = shape.getxCoor(i);
        tempy = shape.getyCoor(i);
        tempz = shape.getzCoor(i);

        xt = (cos(radian) + ux * ux * (1 - cos(radian))) * tempx + (ux * uy * (1 - cos(radian)) -
                uz * sin(radian)) * tempy + (ux * uz * (1 - cos(radian)) + uy * sin(radian)) * tempz;
        yt = (uy * ux * (1 - cos(radian)) + uz * sin(radian)) * tempx +
                (cos(radian) + uy * uy * (1 - cos(radian))) * tempy +
                (uy * uz * (1 - cos(radian)) - ux * sin(radian)) * tempz;
        zt = (uz * ux * (1 - cos(radian)) - uy * sin(radian)) * tempx
                + (uz * uy * (1- cos(radian)) + ux * sin(radian)) * tempy
                + (cos(radian) + uz * uz * (1 - cos(radian))) * tempz;

        shape.replacex(i, xt);
        shape.replacey(i, yt);
        shape.replacez(i, zt);
    }

    cout << "Done and file has been updated.  ...wait for your next step...\n" << endl;
    return;
}

void ChangeShape(){
    int indexInput;
    if(numShapes == 1 ) {
        cout << "There is only one shape. You do not need to change index." << endl;
        indexChanged = 0;
    } else {
        cout << "Type the index of the shape you want to move. Choose an index from 0 to " << numShapes - 1 << ": \n";
        cin >> indexInput;
        while ((indexInput < 0) || (indexInput > (numShapes - 1))) {
            cout<< "Invalid input. Type the index of the shape from 0 to " << numShapes - 1 << ": \n";
            cin >> indexInput;

        }
        indexChanged = indexInput;
        cout<< "The shape index is " << indexInput << endl;

    }
    return;
}

void OutputFile(){
    ofstream outfile;
    outfile.open(file);
    outfile << numShapes << "\n\n";
    for(int i = 0; i < shapes.size(); ++i) {
        outfile << shapes[i].getnumSides() << "\n";
        for(int j = 0; j < shapes[i].getnumSides(); ++j) {
            outfile << shapes[i].getxCoor(j) / factorBegining << " "
            << shapes[i].getyCoor(j) / factorBegining << " " << shapes[i].getzCoor(j) / factorBegining << endl;
        }
        outfile << edges[i].getNumEdges() << "\n";
        for(int j = 0; j < edges[i].getNumEdges(); ++j) {
            outfile << edges[i].getEdge1(j) << " " << edges[i].getEdge2(j) << endl;

        }

        outfile << "\n" << endl;
    }

    outfile.close();
}