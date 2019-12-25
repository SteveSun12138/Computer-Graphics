
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
#include <algorithm>
#include <ctype.h>


#define PI 3.14159265

using namespace std;

class Polyhedra {
public:
    int getNumSides() {
        return numSides;
    }
    void setNumSides(int numSides) {
        Polyhedra::numSides = numSides;
    }
    int getNumFaces() {
        return numFaces;
    }
    void setNumFaces(int numFaces) {
        Polyhedra::numFaces = numFaces;
    }

    void setx(double a, double b){
        x.push_back(make_pair(a, b));
    }
    double getxCoor(int index){
        return x[index].first;
    }

    void sety(double a, double b){
        y.push_back(make_pair(a, b));
    }
    double getyCoor(int index){
        return y[index].first;
    }
    void setz(double a, double b){
        z.push_back(make_pair(a, b));
    }
    double getzCoor(int index){
        return z[index].first;
    }

    void replacexColor(int index, double a){
        x[index].second = a;
    }
    void replaceyColor(int index, double a){
        y[index].second = a;
    }
    void replacezColor(int index, double a){
        z[index].second = a;
    }

    double getxColor(int index){
        return x[index].second;
    }

    double getyColor(int index){
        return y[index].second;
    }

    double getzColor(int index){
        return z[index].second;
    }

//    void setzColor(double col){
//        z.push_back(null, 0);
//    }
    vector<pair<double, double>> getWholeX(){
        return x;
    }
    vector<pair<double, double>> getWholeY(){
        return y;
    }
//    vector<double> getWholeYCoor(){
//        return yCoor;
//    }
//    vector<double> getWholeZCoor(){
//        return zCoor;
//    }


    void movex(int index, double tx) {
        x[index].first = x[index].first + tx;
    }
    void movey(int index, double ty) {
        y[index].first = y[index].first + ty;
    }
    void movez(int index, double tz) {
        z[index].first = z[index].first + tz;
    }

    void setWholeXYZ(double xa, double xb, double ya, double yb, double za, double zb) {
        x.push_back(make_pair(xa, xb));
        y.push_back(make_pair(ya, yb));
        z.push_back(make_pair(za, zb));
    }
    void setAFace(int x){
        aface.push_back(x);
    }
    double getAFace(int index){
        return aface[index];
    }
    void setBFace(int y) {
        bface.push_back(y);
    }
    double getBFace(int index){
        return bface[index];
    }
    void setCFace(int z){
        cface.push_back(z);
    }
    double getCFace(int index){
        return cface[index];
    }
    void replaceAFace(int index, int value){
        aface[index] = value;
    }
    void replaceBFace(int index, int value){
        bface[index] = value;
    }
    void replaceCFace(int index, int value){
        cface[index] = value;
    }

    void setWholeFace(int x, int y, int z) {
        aface.push_back(x);
        bface.push_back(y);
        cface.push_back(z);
    }
    void setSpecularity(int a){
        specularity.push_back(a);
    }
    double getSpecularity(int index){
        return specularity[index];
    }
private:
    int numSides;
    int numFaces;
    //pair 1 is coor, 2 is color
    vector<pair<double, double>> x;
    vector<pair<double, double>> y;
    vector<pair<double, double>> z;

    vector<int> aface;
    vector<int> bface;
    vector<int> cface;
    vector<int> specularity;
};

/****set in main()****/
//the number of pixels in the grid
int grid_width;
int grid_height;

//the size of pxels sets the inital window height and width
//don't make the pixels too large or the screen size will be larger than
//your display size
float pixel_size;

/*Window information*/
int win_height;
int win_width;


void init();
void idle();
void displayMain();

void draw_pix(int x, int y, double red, double green, double blue);
void reshape(int width, int height);
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void check();
void OpenFile();
void ReadFile();
void BasicAdjust();
void BunnyAdjust();
void DDA(vector<Polyhedra>& polyhedras);
void DDAXY();
void DDAXZ();
void DDAYZ();
void LineFillingXY();
void LineFillingXZ();
void LineFillingYZ();
void RasterizationXY();
void RasterizationXZ();
void RasterizationYZ();
void PhongModel();
void CalculateNVector();
bool Compare(const pair<int, double>&a, const pair<int, double>&b);
void PainterXY();
void PainterXZ();
void PainterYZ();

void Painter();
void HalfTone();

void OutputFile();

string file;
double testAdjustment;
double factorBegining;
int pixSize;
double shapeFactor;
int transX, transXBasic;
int transY, transYBasic;
int transZ, transZBasic;
int numShapes;
int numSidesTemp;
int numFacesTemp;
vector<Polyhedra> polyhedraGlobal;
vector<Polyhedra> polyhedraGlobalXY;
vector<Polyhedra> polyhedraGlobalXZ;
vector<Polyhedra> polyhedraGlobalYZ;
vector<Polyhedra> polyhedraGlobalXYTemp;
vector<Polyhedra> polyhedraGlobalXZTemp;
vector<Polyhedra> polyhedraGlobalYZTemp;
vector<double> niFinal, njFinal, nkFinal;

int indexChanged;
int userInputNum1;
int matrixXYCoorABFace[10][10000] = {0};
int matrixXYCoorBCFace[10][10000] = {0};
int matrixXYCoorACFace[10][10000] = {0};
int matrixXZCoorABFace[10][10000] = {0};
int matrixXZCoorBCFace[10][10000] = {0};
int matrixXZCoorACFace[10][10000] = {0};
int matrixYZCoorABFace[10][10000] = {0};
int matrixYZCoorBCFace[10][10000] = {0};
int matrixYZCoorACFace[10][10000] = {0};
double DDAImplePointsXCoorABFace[10000][1000] = {0};
double DDAImplePointsXCoorACFace[10000][1000] = {0};
double DDAImplePointsXCoorBCFace[10000][1000] = {0};
double DDAImplePointsYCoorABFace[10000][1000] = {0};
double DDAImplePointsYCoorACFace[10000][1000] = {0};
double DDAImplePointsYCoorBCFace[10000][1000] = {0};
double DDAImplePointsZCoorABFace[10000][1000] = {0};
double DDAImplePointsZCoorACFace[10000][1000] = {0};
double DDAImplePointsZCoorBCFace[10000][1000] = {0};
double DDAImplePointsXColorABFace[10000][1000] = {0};
double DDAImplePointsXColorACFace[10000][1000] = {0};
double DDAImplePointsXColorBCFace[10000][1000] = {0};
double DDAImplePointsYColorABFace[10000][1000] = {0};
double DDAImplePointsYColorACFace[10000][1000] = {0};
double DDAImplePointsYColorBCFace[10000][1000] = {0};
double DDAImplePointsZColorABFace[10000][1000] = {0};
double DDAImplePointsZColorACFace[10000][1000] = {0};
double DDAImplePointsZColorBCFace[10000][1000] = {0};
//double matrixXZ[1000][100000] = {0};
//double matrixYZ[1000][100000] = {0};


double inf = std::numeric_limits<double>::infinity();

int main(int argc, char **argv)
{
    cout << "Welcome to polyhedra! Choose which file to open (Type 1 or 2)."
            "\n (1) cube_and_icosahedron.txt  (2) bunny.txt" << endl;
    cin >> userInputNum1;
    while(userInputNum1 != 1 && userInputNum1 != 2) {
        cout << "You typed wrong number. Please try again." << endl;
        cin >> userInputNum1;
    }
    if(userInputNum1 == 1){
        file = "cube_and_icosahedron.txt";
//        file = "test3.txt";
    } else if (userInputNum1 == 2) {
        file = "bunny.txt";
//        file = "test4.txt";
    }

    OpenFile();
    ReadFile();
    OutputFile();

    PhongModel();

    polyhedraGlobalXY = polyhedraGlobal;
    polyhedraGlobalXZ = polyhedraGlobal;
    polyhedraGlobalYZ = polyhedraGlobal;

    PainterXY();
    DDAXY();
    RasterizationXY();

    PainterXZ();
    DDAXZ();
    RasterizationXZ();

    PainterYZ();
    DDAYZ();
    RasterizationYZ();


    //User menu
//    cout << "There are " << numShapes << " polyhedra(s) in the file." << endl;

    //the number of pixels in the grid
    grid_width = factorBegining;
    grid_height = factorBegining;

    //the size of pixels sets the inital window height and width
    //don't make the pixels too large or the screen size will be larger than
    //your display size
    pixel_size = pixSize;

    /*Window information*/
    win_height = grid_height*pixel_size;
    win_width = grid_width*pixel_size;


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

void init()
{
    //set clear color (Default background to white)
    glClearColor(0,0,0,1.0);
    //checks for OpenGL errors
    check();
}
void idle()
{
    //redraw the scene over and over again
    glutPostRedisplay();
}

void displayMain()
{
    //clears the screen
    glClearColor(0, 0, 0,1.0);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
//    //clears the opengl Modelview transformation matrix
    glLoadIdentity();

    //draw the grid line

    //glViewport(0, grid_width/2, grid_width/2, grid_width/2);
//    cout << "*************************" << endl;
//    cout << "numsides: " << polyhedras[i].getNumSides() << endl;


    //draw xy, yz, and xz
    LineFillingXY();
    LineFillingXZ();
    LineFillingYZ();

    //blits the current opengl framebuffer on the screen
    glutSwapBuffers();
    //checks for opengl errors
    check();
}

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
void key(unsigned char ch, int x, int y)
{
    //rotate
    if (ch == 'e') {
        //OutputFile();
        exit(1);
    } else if (ch == 't') {
        cout << "Now translating." << endl;

    } else if (ch == 's') {
        cout << "Now scaling." << endl;

    } else if (ch == 'r') {
        cout << "Now rotating." << endl;
    }

    //redraw the scene after keyboard input
    glutPostRedisplay();
}
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
void motion(int x, int y)
{
    //redraw the scene after mouse movement
    glutPostRedisplay();
}
void check()
{
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        printf("GLERROR: There was an error %s\n",gluErrorString(err) );
        exit(1);
    }
}

void draw_pix(int x, int y, double red, double green, double blue){
    glBegin(GL_POINTS);
    glColor3f(red,green,blue);
    glVertex3f(x+.5,y+.5,0);
    glEnd();
}

void OpenFile() {
//    cout << "Type the file you want to open: \n";
//    cin >> file;
    ifstream myReadFile;
    myReadFile.open(file);

//    while (!myReadFile.is_open()) {
//        cout << "trouble opening the file" << endl;
//
//    }

    if (!myReadFile.is_open()) {
        cout << "trouble opening the file" << endl;
    }
    myReadFile >> numShapes;

}
void BasicAdjust() {
    factorBegining = 600;
    pixSize = 1;
    testAdjustment = 1.3;
    transXBasic = 80;
    transYBasic = 80;
    transZBasic = 80;
    testAdjustment = 1;
    transXBasic = 0;
    transYBasic = 0;
    transZBasic = 0;
}
void BunnyAdjust() {
    shapeFactor = 5;
    transX = 1200;
    transY = 1500;
    transZ = 1200;
    return;
}
void ReadFile() {

    int numShapesTemp;
    int numShapesEdgeTemp;
    int numColorTemp;
    double tempx[10000] = {0};
    double tempy[10000] = {0};
    double tempz[10000] = {0};
    ifstream myReadFile;
    myReadFile.open(file);

    myReadFile >> numShapesTemp;
    //cout << "numshapes: " << numShapesTemp << endl;

    BasicAdjust();
    BunnyAdjust();
    for(int i = 0; i < numShapesTemp; i++){//per shape itself
        Polyhedra polyhedra;
        polyhedraGlobal.push_back(polyhedra);
//        polyhedraGlobalXY.push_back(polyhedra);
//        polyhedraGlobalXZ.push_back(polyhedra);
//        polyhedraGlobalYZ.push_back(polyhedra);

        //vertice: points and color
        myReadFile >> numSidesTemp;
        polyhedraGlobal[i].setNumSides(numSidesTemp);
//        polyhedraGlobalXY[i].setNumSides(numSidesTemp);
//        polyhedraGlobalXZ[i].setNumSides(numSidesTemp);
//        polyhedraGlobalYZ[i].setNumSides(numSidesTemp);
//        cout << "numsides: " << polyhedraGlobal[i].getNumSides() << endl;
        int w = 0;

        while (w < numSidesTemp){
            myReadFile >> tempx[w] >> tempy[w] >> tempz[w];
            if(file == "bunny.txt"){
                tempx[w] = tempx[w] * factorBegining * shapeFactor - transX;
                tempy[w] = tempy[w] * factorBegining * shapeFactor - transY;
                tempz[w] = tempz[w] * factorBegining * shapeFactor - transZ;
            } else{
                tempx[w] = tempx[w] * factorBegining * testAdjustment - transXBasic;
                tempy[w] = tempy[w] * factorBegining * testAdjustment - transYBasic;
                tempz[w] = tempz[w] * factorBegining * testAdjustment - transZBasic;
            }
//                polyhedraGlobal[i].setPointXYZ(round((tempx * factorBegining) + 0.5),
//                        round((tempy * factorBegining) + 0.5), round((tempz * factorBegining) +0.5));
            w++;
        }


        //set coor and color
        double temx = 0;
        double temy = 0;
        double temz = 0;
        w = 0;

        while (w < numSidesTemp){
            myReadFile >> temx >> temy >> temz;
            polyhedraGlobal[i].setWholeXYZ(round(tempx[w] + .5), temx / 255,
                                      round(tempy[w] + .5), temy / 255,round(tempz[w] + .5), temz/255);
//            polyhedraGlobalXY[i].setWholeXYZ(round(tempx[w] + .5), temx/ 255,
//                                           round(tempy[w] + .5), temy/ 255,round(tempz[w] + .5), temz/ 255);
//            polyhedraGlobalXZ[i].setWholeXYZ(round(tempx[w] + .5), temx/ 255,
//                                             round(tempy[w] + .5), temy/ 255,round(tempz[w] + .5), temz/ 255);
//            polyhedraGlobalYZ[i].setWholeXYZ(round(tempx[w] + .5), temx/ 255,
//                                             round(tempy[w] + .5), temy/ 255,round(tempz[w] + .5), temz/ 255);
            w++;
        }
//        for(int ii = 0; ii < numSidesTemp; ii++){
//
//            cout << "x: " <<polyhedraGlobal[i].getxCoor(ii) <<
//            ", y: " <<polyhedraGlobal[i].getyCoor(ii) << ", z: " <<polyhedraGlobal[i].getzCoor(ii) << endl;
//            cout << "xcolor: " <<polyhedraGlobal[i].getxColor(ii) <<
//                 ", ycolor: " <<polyhedraGlobal[i].getyColor(ii) << ", zcolor: " <<polyhedraGlobal[i].getzColor(ii) << endl;
//        }

        //face: face and specularity
        myReadFile >> numFacesTemp;
        polyhedraGlobal[i].setNumFaces(numFacesTemp);
//        polyhedraGlobalXY[i].setNumFaces(numFacesTemp);
//        polyhedraGlobalXZ[i].setNumFaces(numFacesTemp);
//        polyhedraGlobalYZ[i].setNumFaces(numFacesTemp);
        int tempxx = 0;
        int tempyy = 0;
        int tempzz = 0;
        w = 0;
        while (w < numFacesTemp) {
            myReadFile >> tempxx >> tempyy >> tempzz;
            polyhedraGlobal[i].setWholeFace(tempxx, tempyy, tempzz);
//            polyhedraGlobalXY[i].setWholeFace(tempxx, tempyy, tempzz);
//            polyhedraGlobalXZ[i].setWholeFace(tempxx, tempyy, tempzz);
//            polyhedraGlobalYZ[i].setWholeFace(tempxx, tempyy, tempzz);
            w++;
        }
//        for(int ii = 0; ii < numFacesTemp; ii++){
//            cout << "x: " <<polyhedraGlobal[i].getaFace(ii) <<
//            ", y: " <<polyhedraGlobal[i].getBFace(ii) << ", z: " <<polyhedraGlobal[i].getCFace(ii) << endl;
//        }
        //specularity
        tempxx = 0;

        w = 0;
        while (w < numFacesTemp) {
            myReadFile >> tempxx;
            polyhedraGlobal[i].setSpecularity(tempxx);
//            polyhedraGlobalXY[i].setSpecularity(tempxx);
//            polyhedraGlobalXZ[i].setSpecularity(tempxx);
//            polyhedraGlobalYZ[i].setSpecularity(tempxx);
            w++;
        }

    }

    return;
}
void OutputFile(){
    ofstream outfile;
    outfile.open("file2.txt");
//    outfile << numShapes << "\n\n";
    for(int i = 0; i < polyhedraGlobal.size(); ++i) {
//        outfile << polyhedraGlobal[i].getNumSides() << "\n";
        for(int j = 0; j < polyhedraGlobal[i].getNumSides(); ++j) {
            outfile << polyhedraGlobal[i].getxCoor(j)  << " "
                    << polyhedraGlobal[i].getyCoor(j)  << " "
                    << polyhedraGlobal[i].getzCoor(j) << endl;
        }


        outfile << "\n" << endl;
    }

    outfile.close();
}

void DDAXY(){
    //DDA should be consist of faces. Each face x, y, z. Calculate 3 times xy, xz, yz
    //int, double
    //xy
    int a = polyhedraGlobalXY.size();
    int aa[a];
    double x0, y0, z0, xi, yi, zi, delx, dely, delz, tempx, tempy, tempz, mxy, mxz;
    double x0col, y0col, z0col, xicol, yicol, zicol, delxCol, delyCol, delzCol,
    tempxcol, tempycol, tempzcol;
    double x, y, z;
    double tempxColor = 0;
    double tempyColor = 0;
    double tempzColor = 0;
//    cout << "polyhedra size: " << polyhedraGlobalXY.size() << endl;
    //AB Face
    for(int i = 0; i < polyhedraGlobalXY.size(); ++i){

        for(int j = 0; j < polyhedraGlobalXY[i].getNumFaces(); ++j){
            matrixXYCoorABFace[i][j] = 0;
//            DDAImplePointsXYCoorABFace[i][j] = 0;
            //first aFace, bface
            x0 = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getAFace(j) - 1);
            xi = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getBFace(j) - 1);
            y0 = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getAFace(j) - 1);
            yi = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getBFace(j) - 1);
            z0 = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getAFace(j) - 1);
            zi = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getBFace(j) - 1);


            x0col = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getAFace(j) - 1);
            xicol = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getBFace(j) - 1);
            y0col = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getAFace(j) - 1);
            yicol = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getBFace(j) - 1);
            z0col = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getAFace(j) - 1);
            zicol = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getBFace(j) - 1);

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//            cout << endl;
            if(x0 > xi) {
                tempx = x0;
                tempxcol = x0col;
                x0 = xi;
                x0col = xicol;
                xi = tempx;
                xicol = tempxcol;

                tempy = y0;
                tempycol = y0col;
                y0 = yi;
                y0col = yicol;
                yi = tempy;
                yicol = tempycol;

                tempz = z0;
                tempzcol = z0col;
                z0 = zi;
                z0col = zicol;
                zi = tempz;
                zicol = tempzcol;
            }
            delx = xi - x0;
            dely = yi - y0;
            delz = zi - z0;

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;



//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
            if (!(delx == 0 && dely == 0)) {
                mxy = dely / delx;
                tempx = x0;
                tempy = y0;
                //add points itself
//                cout << "x0color: " << x0col
//                     << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                cout << "xicolor: " << xicol
//                     << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
                if((mxy > 0 && mxy <=1) || (mxy < 0 && mxy >= -1)) {
                    for (int k = 0; k < abs(delx); k++) {
                        y = tempy + mxy;
                        x = tempx + 1;
                        //FIXME: check if this formula correct, mostly k or k + 1 or other
                        tempxColor = x0col + (xicol - x0col ) * k / delx;
                        tempyColor = y0col + (yicol - y0col ) * k / delx;
                        tempzColor = z0col + (zicol - z0col ) * k / delx;
//                       cout << "x0color: " << x0col
//                        << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "xcolor: " << tempxColor
//                        << ", ycolor: " << tempyColor << ", zcolor: " << tempzColor << endl;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(mxy == 0) {
                    for (int k = 0; k < abs(delx); k++) {
                        tempxColor = x0col + (xicol - x0col ) * k / delx;
                        tempyColor = y0col + (yicol - y0col ) * k / delx;
                        tempzColor = z0col + (zicol - z0col ) * k / delx;
//                        cout << "x0color: " << x0col
//                             << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "tempx: " << tempxColor << ", tempy: "
//                        << tempyColor << ", tempz: " << tempzColor << endl;
//                        cout << endl;
                        y = tempy;
                        x = tempx + 1;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(mxy > 1) {
                    for (int k = 0; k < abs(dely); k++) {
                        y = tempy + 1;
                        x = tempx + 1/mxy;
                        tempxColor = x0col + (xicol - x0col ) * k / dely;
                        tempyColor = y0col + (yicol - y0col ) * k / dely;
                        tempzColor = z0col + (zicol - z0col ) * k / dely;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }
//
                if(mxy < -1) {
                    for (int k = 0; k < abs(dely); k++) {
                        y = tempy - 1;
                        x = tempx - 1/mxy;
                        tempxColor = x0col + (xicol - x0col ) * k / dely;
                        tempyColor = y0col + (yicol - y0col ) * k / dely;
                        tempzColor = z0col + (zicol - z0col ) * k / dely;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }

            } else{
//                cout << "mxy = nananan" << endl;
            }

        }

    }

    //AC Face
    for(int i = 0; i < polyhedraGlobalXY.size(); ++i){
//        cout << "*************************" << endl;
//        cout << "numsides: " << polyhedraGlobalXY[i].getNumSides() << endl;

        for(int j = 0; j < polyhedraGlobalXY[i].getNumFaces(); ++j){
            matrixXYCoorACFace[i][j] = 0;
            //first aFace, yface
            x0 = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getAFace(j) - 1);
            xi = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getCFace(j) - 1);
            //x3 = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getCFace(j));

            y0 = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getAFace(j) - 1);
            yi = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getCFace(j) - 1);

            z0 = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getAFace(j) - 1);
            zi = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getCFace(j) - 1);

            x0col = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getAFace(j) - 1);
            xicol = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getCFace(j) - 1);
            y0col = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getAFace(j) - 1);
            yicol = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getCFace(j) - 1);
            z0col = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getAFace(j) - 1);
            zicol = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getCFace(j) - 1);

//            z1 = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getAFace(j));
//            z2 = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getBFace(j));
            if(x0 > xi) {
                tempx = x0;
                tempxcol = x0col;
                x0 = xi;
                x0col = xicol;
                xi = tempx;
                xicol = tempxcol;

                tempy = y0;
                tempycol = y0col;
                y0 = yi;
                y0col = yicol;
                yi = tempy;
                yicol = tempycol;

                tempz = z0;
                tempzcol = z0col;
                z0 = zi;
                z0col = zicol;
                zi = tempz;
                zicol = tempzcol;
            }
            delx = xi - x0;
            dely = yi - y0;
            delz = zi - z0;

            if (!(delx == 0 && dely == 0)) {
                mxy = dely / delx;
                tempx = x0;
                tempy = y0;
                if((mxy > 0 && mxy <=1) || (mxy < 0 && mxy >= -1)) {
                    for (int k = 0; k < abs(delx); k++) {
                        y = tempy + mxy;
                        x = tempx + 1;
                        tempxColor = x0col + (xicol - x0col ) * k / delx;
                        tempyColor = y0col + (yicol - y0col ) * k / delx;
                        tempzColor = z0col + (zicol - z0col ) * k / delx;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorACFace[i][j][k] = x;
//                        DDAImplePointsYCoorACFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }

                if(mxy == 0) {
                    for (int k = 0; k < abs(delx); k++) {
                        y = tempy;
                        x = tempx + 1;
                        tempxColor = x0col + (xicol - x0col ) * k / delx;
                        tempyColor = y0col + (yicol - y0col ) * k / delx;
                        tempzColor = z0col + (zicol - z0col ) * k / delx;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorACFace[i][j][k] = x;
//                        DDAImplePointsYCoorACFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }

                if(mxy > 1) {
                    for (int k = 0; k < abs(dely); k++) {
                        y = tempy + 1;
                        x = tempx + 1/mxy;
                        tempxColor = x0col + (xicol - x0col ) * k / dely;
                        tempyColor = y0col + (yicol - y0col ) * k / dely;
                        tempzColor = z0col + (zicol - z0col ) * k / dely;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorACFace[i][j][k] = x;
//                        DDAImplePointsYCoorACFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }

                if(mxy < -1) {
                    for (int k = 0; k < abs(dely); k++) {
                        y = tempy - 1;
                        x = tempx - 1/mxy;
                        tempxColor = x0col + (xicol - x0col ) * k / dely;
                        tempyColor = y0col + (yicol - y0col ) * k / dely;
                        tempzColor = z0col + (zicol - z0col ) * k / dely;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorACFace[i][j][k] = x;
//                        DDAImplePointsYCoorACFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }

            } else{
//                cout << "mxy = nananan" << endl;
            }

        }

    }

//    //BC Face
    for(int i = 0; i < polyhedraGlobalXY.size(); ++i) {
//        cout << "*************************" << endl;
//        cout << "numsides: " << polyhedraGlobalXY[i].getNumSides() << endl;

        for (int j = 0; j < polyhedraGlobalXY[i].getNumFaces(); ++j) {
            matrixXYCoorBCFace[i][j] = 0;
            //first aFace, yface
            x0 = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getBFace(j) - 1);
            xi = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getCFace(j) - 1);
            //x3 = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getCFace(j));

            y0 = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getBFace(j) - 1);
            yi = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getCFace(j) - 1);

            z0 = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getBFace(j) - 1);
            zi = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getCFace(j) - 1);

            x0col = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getBFace(j) - 1);
            xicol = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getCFace(j) - 1);
            y0col = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getBFace(j) - 1);
            yicol = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getCFace(j) - 1);
            z0col = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getBFace(j) - 1);
            zicol = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getCFace(j) - 1);

            if (x0 > xi) {
                tempx = x0;
                tempxcol = x0col;
                x0 = xi;
                x0col = xicol;
                xi = tempx;
                xicol = tempxcol;

                tempy = y0;
                tempycol = y0col;
                y0 = yi;
                y0col = yicol;
                yi = tempy;
                yicol = tempycol;

                tempz = z0;
                tempzcol = z0col;
                z0 = zi;
                z0col = zicol;
                zi = tempz;
                zicol = tempzcol;
            }
            delx = xi - x0;
            dely = yi - y0;
            delz = zi - z0;

            if (!(delx == 0 && dely == 0)) {
                mxy = dely / delx;
                tempx = x0;
                tempy = y0;
                if ((mxy > 0 && mxy <= 1) || (mxy < 0 && mxy >= -1)) {
                    for (int k = 0; k < abs(delx); k++) {
                        y = tempy + mxy;
                        x = tempx + 1;
                        tempxColor = x0col + (xicol - x0col) * k / delx;
                        tempyColor = y0col + (yicol - y0col) * k / delx;
                        tempzColor = z0col + (zicol - z0col) * k / delx;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorACFace[i][j][k] = x;
//                        DDAImplePointsYCoorACFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }

                if (mxy == 0) {
                    for (int k = 0; k < abs(delx); k++) {
                        y = tempy;
                        x = tempx + 1;
                        tempxColor = x0col + (xicol - x0col) * k / delx;
                        tempyColor = y0col + (yicol - y0col) * k / delx;
                        tempzColor = z0col + (zicol - z0col) * k / delx;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorACFace[i][j][k] = x;
//                        DDAImplePointsYCoorACFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }

                if (mxy > 1) {
                    for (int k = 0; k < abs(dely); k++) {
                        y = tempy + 1;
                        x = tempx + 1 / mxy;
                        tempxColor = x0col + (xicol - x0col) * k / dely;
                        tempyColor = y0col + (yicol - y0col) * k / dely;
                        tempzColor = z0col + (zicol - z0col) * k / dely;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorACFace[i][j][k] = x;
//                        DDAImplePointsYCoorACFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }

                if (mxy < -1) {
                    for (int k = 0; k < abs(dely); k++) {
                        y = tempy - 1;
                        x = tempx - 1 / mxy;
                        tempxColor = x0col + (xicol - x0col) * k / dely;
                        tempyColor = y0col + (yicol - y0col) * k / dely;
                        tempzColor = z0col + (zicol - z0col) * k / dely;
                        polyhedraGlobalXY[i].setx(round(x), tempxColor);
                        polyhedraGlobalXY[i].sety(round(y), tempyColor);
                        polyhedraGlobalXY[i].setz(-1, tempzColor);
                        matrixXYCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorACFace[i][j][k] = x;
//                        DDAImplePointsYCoorACFace[i][j][k] = y;
                        tempx = x;
                        tempy = y;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }

            } else {

            }

        }

    }

    return;
}
void DDAXZ(){
    int a = polyhedraGlobalXZ.size();
    int aa[a];
    double x0, y0, z0, xi, yi, zi, delx, dely, delz, tempx, tempy, tempz, mxy, mxz;
    double x0col, y0col, z0col, xicol, yicol, zicol, delxCol, delyCol, delzCol,
            tempxcol, tempycol, tempzcol;
    double x, y, z;
    double tempxColor = 0;
    double tempyColor = 0;
    double tempzColor = 0;
//    cout << "polyhedra size: " << polyhedraGlobalXY.size() << endl;
    //AB Face
    for(int i = 0; i < polyhedraGlobalXZ.size(); ++i){

        for(int j = 0; j < polyhedraGlobalXZ[i].getNumFaces(); ++j){
            matrixXZCoorABFace[i][j] = 0;
//            DDAImplePointsXYCoorABFace[i][j] = 0;
            //first aFace, bface

            x0 = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            xi = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            y0 = polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            yi = polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            z0 = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            zi = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getBFace(j) - 1);


            x0col = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            xicol = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            y0col = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            yicol = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            z0col = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            zicol = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getBFace(j) - 1);

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//            cout << endl;
            if(x0 > xi) {
                tempx = x0;
                tempxcol = x0col;
                x0 = xi;
                x0col = xicol;
                xi = tempx;
                xicol = tempxcol;

                tempy = y0;
                tempycol = y0col;
                y0 = yi;
                y0col = yicol;
                yi = tempy;
                yicol = tempycol;

                tempz = z0;
                tempzcol = z0col;
                z0 = zi;
                z0col = zicol;
                zi = tempz;
                zicol = tempzcol;
            }
            delx = xi - x0;
            dely = yi - y0;
            delz = zi - z0;

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;



//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
            if (!(delx == 0 && delz == 0)) {
                mxz = delz / delx;
                tempx = x0;
                tempz = z0;
                //add points itself
//                cout << "x0color: " << x0col
//                     << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                cout << "xicolor: " << xicol
//                     << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
                if((mxz > 0 && mxz <=1) || (mxz < 0 && mxz >= -1)) {
                    for (int k = 0; k < abs(delx); k++) {
                        z = tempz + mxz;
                        x = tempx + 1;
                        //FIXME: check if this formula correct, mostly k or k + 1 or other
                        tempxColor = x0col + (xicol - x0col ) * k / delx;
                        tempyColor = y0col + (yicol - y0col ) * k / delx;
                        tempzColor = z0col + (zicol - z0col ) * k / delx;
//                       cout << "x0color: " << x0col
//                        << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "xcolor: " << tempxColor
//                        << ", ycolor: " << tempyColor << ", zcolor: " << tempzColor << endl;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(mxz == 0) {
                    for (int k = 0; k < abs(delx); k++) {
                        tempxColor = x0col + (xicol - x0col ) * k / delx;
                        tempyColor = y0col + (yicol - y0col ) * k / delx;
                        tempzColor = z0col + (zicol - z0col ) * k / delx;
//                        cout << "x0color: " << x0col
//                             << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "tempx: " << tempxColor << ", tempy: "
//                        << tempyColor << ", tempz: " << tempzColor << endl;
//                        cout << endl;
                        z = tempz;
                        x = tempx + 1;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(mxz > 1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz + 1;
                        x = tempx + 1/mxz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }

                if(mxz < -1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz - 1;
                        x = tempx - 1/mxz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }
            } else{
//                cout << "mxy = nananan" << endl;
            }

        }

    }



    //AC Face
    for(int i = 0; i < polyhedraGlobalXZ.size(); ++i){

        for(int j = 0; j < polyhedraGlobalXZ[i].getNumFaces(); ++j){
            matrixXZCoorACFace[i][j] = 0;
//            DDAImplePointsXYCoorABFace[i][j] = 0;
            //first aFace, bface

            x0 = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            xi = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getCFace(j) - 1);
            y0 = polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            yi = polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getCFace(j) - 1);
            z0 = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            zi = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getCFace(j) - 1);


            x0col = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            xicol = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
            y0col = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            yicol = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
            z0col = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            zicol = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getCFace(j) - 1);

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//            cout << endl;
            if(x0 > xi) {
                tempx = x0;
                tempxcol = x0col;
                x0 = xi;
                x0col = xicol;
                xi = tempx;
                xicol = tempxcol;

                tempy = y0;
                tempycol = y0col;
                y0 = yi;
                y0col = yicol;
                yi = tempy;
                yicol = tempycol;

                tempz = z0;
                tempzcol = z0col;
                z0 = zi;
                z0col = zicol;
                zi = tempz;
                zicol = tempzcol;
            }
            delx = xi - x0;
            dely = yi - y0;
            delz = zi - z0;

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;



//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
            if (!(delx == 0 && delz == 0)) {
                mxz = delz / delx;
                tempx = x0;
                tempz = z0;
                //add points itself
//                cout << "x0color: " << x0col
//                     << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                cout << "xicolor: " << xicol
//                     << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
                if((mxz > 0 && mxz <=1) || (mxz < 0 && mxz >= -1)) {
                    for (int k = 0; k < abs(delx); k++) {
                        z = tempz + mxz;
                        x = tempx + 1;
                        //FIXME: check if this formula correct, mostly k or k + 1 or other
                        tempxColor = x0col + (xicol - x0col ) * k / delx;
                        tempyColor = y0col + (yicol - y0col ) * k / delx;
                        tempzColor = z0col + (zicol - z0col ) * k / delx;
//                       cout << "x0color: " << x0col
//                        << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "xcolor: " << tempxColor
//                        << ", ycolor: " << tempyColor << ", zcolor: " << tempzColor << endl;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(mxz == 0) {
                    for (int k = 0; k < abs(delx); k++) {
                        tempxColor = x0col + (xicol - x0col ) * k / delx;
                        tempyColor = y0col + (yicol - y0col ) * k / delx;
                        tempzColor = z0col + (zicol - z0col ) * k / delx;

                        z = tempz;
                        x = tempx + 1;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(mxz > 1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz + 1;
                        x = tempx + 1/mxz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }

                if(mxz < -1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz - 1;
                        x = tempx - 1/mxz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }
            } else{
//                cout << "mxy = nananan" << endl;
            }

        }

    }




    //BC Face
    for(int i = 0; i < polyhedraGlobalXZ.size(); ++i){

        for(int j = 0; j < polyhedraGlobalXZ[i].getNumFaces(); ++j){
            matrixXZCoorBCFace[i][j] = 0;
//            DDAImplePointsXYCoorABFace[i][j] = 0;
            //first aFace, bface

            x0 = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            xi = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getCFace(j) - 1);
            y0 = polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            yi = polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getCFace(j) - 1);
            z0 = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            zi = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getCFace(j) - 1);


            x0col = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            xicol = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
            y0col = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            yicol = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
            z0col = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            zicol = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getCFace(j) - 1);

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//            cout << endl;
            if(x0 > xi) {
                tempx = x0;
                tempxcol = x0col;
                x0 = xi;
                x0col = xicol;
                xi = tempx;
                xicol = tempxcol;

                tempy = y0;
                tempycol = y0col;
                y0 = yi;
                y0col = yicol;
                yi = tempy;
                yicol = tempycol;

                tempz = z0;
                tempzcol = z0col;
                z0 = zi;
                z0col = zicol;
                zi = tempz;
                zicol = tempzcol;
            }
            delx = xi - x0;
            dely = yi - y0;
            delz = zi - z0;

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;



//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
            if (!(delx == 0 && delz == 0)) {
                mxz = delz / delx;
                tempx = x0;
                tempz = z0;
                //add points itself
//                cout << "x0color: " << x0col
//                     << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                cout << "xicolor: " << xicol
//                     << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
                if((mxz > 0 && mxz <=1) || (mxz < 0 && mxz >= -1)) {
                    for (int k = 0; k < abs(delx); k++) {
                        z = tempz + mxz;
                        x = tempx + 1;
                        //FIXME: check if this formula correct, mostly k or k + 1 or other
                        tempxColor = x0col + (xicol - x0col ) * k / delx;
                        tempyColor = y0col + (yicol - y0col ) * k / delx;
                        tempzColor = z0col + (zicol - z0col ) * k / delx;
//                       cout << "x0color: " << x0col
//                        << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "xcolor: " << tempxColor
//                        << ", ycolor: " << tempyColor << ", zcolor: " << tempzColor << endl;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(mxz == 0) {
                    for (int k = 0; k < abs(delx); k++) {
                        tempxColor = x0col + (xicol - x0col ) * k / delx;
                        tempyColor = y0col + (yicol - y0col ) * k / delx;
                        tempzColor = z0col + (zicol - z0col ) * k / delx;

                        z = tempz;
                        x = tempx + 1;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(mxz > 1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz + 1;
                        x = tempx + 1/mxz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }

                if(mxz < -1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz - 1;
                        x = tempx - 1/mxz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalXZ[i].setx(round(x), tempxColor);
                        polyhedraGlobalXZ[i].sety(-1, tempyColor);
                        polyhedraGlobalXZ[i].setz(round(z), tempzColor);
                        matrixXZCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempx = x;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }
            } else{
//                cout << "mxy = nananan" << endl;
            }

        }

    }



    return;
}
void DDAYZ(){
    int a = polyhedraGlobalYZ.size();
    int aa[a];
    double x0, y0, z0, xi, yi, zi, delx, dely, delz, tempx, tempy, tempz, mxy, mxz, myz;
    double x0col, y0col, z0col, xicol, yicol, zicol, delxCol, delyCol, delzCol,
            tempxcol, tempycol, tempzcol;
    double x, y, z;
    double tempxColor = 0;
    double tempyColor = 0;
    double tempzColor = 0;
//    cout << "polyhedra size: " << polyhedraGlobalXY.size() << endl;
    //AB Face
    for(int i = 0; i < polyhedraGlobalYZ.size(); ++i){

        for(int j = 0; j < polyhedraGlobalYZ[i].getNumFaces(); ++j){
            matrixYZCoorABFace[i][j] = 0;
//            DDAImplePointsXYCoorABFace[i][j] = 0;
            //first aFace, bface

            x0 = polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            xi = polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            y0 = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            yi = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            z0 = polyhedraGlobalYZ[i].getzCoor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            zi = polyhedraGlobalYZ[i].getzCoor(polyhedraGlobalYZ[i].getBFace(j) - 1);


            x0col = polyhedraGlobalYZ[i].getxColor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            xicol = polyhedraGlobalYZ[i].getxColor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            y0col = polyhedraGlobalYZ[i].getyColor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            yicol = polyhedraGlobalYZ[i].getyColor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            z0col = polyhedraGlobalYZ[i].getzColor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            zicol = polyhedraGlobalYZ[i].getzColor(polyhedraGlobalYZ[i].getBFace(j) - 1);

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//            cout << endl;
            if(y0 > yi) {
                tempx = x0;
                tempxcol = x0col;
                x0 = xi;
                x0col = xicol;
                xi = tempx;
                xicol = tempxcol;

                tempy = y0;
                tempycol = y0col;
                y0 = yi;
                y0col = yicol;
                yi = tempy;
                yicol = tempycol;

                tempz = z0;
                tempzcol = z0col;
                z0 = zi;
                z0col = zicol;
                zi = tempz;
                zicol = tempzcol;
            }
            delx = xi - x0;
            dely = yi - y0;
            delz = zi - z0;

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;



//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
            if (!(dely == 0 && delz == 0)) {
                myz = delz / dely;
                tempy = y0;
                tempz = z0;
                //add points itself
//                cout << "x0color: " << x0col
//                     << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                cout << "xicolor: " << xicol
//                     << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
                if((myz > 0 && myz <=1) || (myz < 0 && myz >= -1)) {
                    for (int k = 0; k < abs(dely); k++) {
                        z = tempz + myz;
                        y = tempy + 1;
                        //FIXME: check if this formula correct, mostly k or k + 1 or other
                        tempxColor = x0col + (xicol - x0col ) * k / dely;
                        tempyColor = y0col + (yicol - y0col ) * k / dely;
                        tempzColor = z0col + (zicol - z0col ) * k / dely;
//                       cout << "x0color: " << x0col
//                        << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "xcolor: " << tempxColor
//                        << ", ycolor: " << tempyColor << ", zcolor: " << tempzColor << endl;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(myz == 0) {
                    for (int k = 0; k < abs(dely); k++) {
                        tempxColor = x0col + (xicol - x0col ) * k / dely;
                        tempyColor = y0col + (yicol - y0col ) * k / dely;
                        tempzColor = z0col + (zicol - z0col ) * k / dely;
//                        cout << "x0color: " << x0col
//                             << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "tempx: " << tempxColor << ", tempy: "
//                        << tempyColor << ", tempz: " << tempzColor << endl;
//                        cout << endl;
                        z = tempz;
                        y = tempy + 1;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(myz > 1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz + 1;
                        y = tempy + 1/myz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }
                if(myz < -1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz - 1;
                        y = tempy - 1/myz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorABFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }
            } else{
//                cout << "mxy = nananan" << endl;
            }

        }

    }

    //AC Face
    for(int i = 0; i < polyhedraGlobalYZ.size(); ++i){

        for(int j = 0; j < polyhedraGlobalYZ[i].getNumFaces(); ++j){
            matrixYZCoorACFace[i][j] = 0;
//            DDAImplePointsXYCoorABFace[i][j] = 0;
            //first aFace, bface

            x0 = polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            xi = polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getCFace(j) - 1);
            y0 = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            yi = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getCFace(j) - 1);
            z0 = polyhedraGlobalYZ[i].getzCoor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            zi = polyhedraGlobalYZ[i].getzCoor(polyhedraGlobalYZ[i].getCFace(j) - 1);


            x0col = polyhedraGlobalYZ[i].getxColor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            xicol = polyhedraGlobalYZ[i].getxColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
            y0col = polyhedraGlobalYZ[i].getyColor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            yicol = polyhedraGlobalYZ[i].getyColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
            z0col = polyhedraGlobalYZ[i].getzColor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            zicol = polyhedraGlobalYZ[i].getzColor(polyhedraGlobalYZ[i].getCFace(j) - 1);

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//            cout << endl;
            if(y0 > yi) {
                tempx = x0;
                tempxcol = x0col;
                x0 = xi;
                x0col = xicol;
                xi = tempx;
                xicol = tempxcol;

                tempy = y0;
                tempycol = y0col;
                y0 = yi;
                y0col = yicol;
                yi = tempy;
                yicol = tempycol;

                tempz = z0;
                tempzcol = z0col;
                z0 = zi;
                z0col = zicol;
                zi = tempz;
                zicol = tempzcol;
            }
            delx = xi - x0;
            dely = yi - y0;
            delz = zi - z0;

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;



//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
            if (!(dely == 0 && delz == 0)) {
                myz = delz / dely;
                tempy = y0;
                tempz = z0;
                //add points itself
//                cout << "x0color: " << x0col
//                     << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                cout << "xicolor: " << xicol
//                     << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
                if((myz > 0 && myz <=1) || (myz < 0 && myz >= -1)) {
                    for (int k = 0; k < abs(dely); k++) {
                        z = tempz + myz;
                        y = tempy + 1;
                        //FIXME: check if this formula correct, mostly k or k + 1 or other
                        tempxColor = x0col + (xicol - x0col ) * k / dely;
                        tempyColor = y0col + (yicol - y0col ) * k / dely;
                        tempzColor = z0col + (zicol - z0col ) * k / dely;
//                       cout << "x0color: " << x0col
//                        << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "xcolor: " << tempxColor
//                        << ", ycolor: " << tempyColor << ", zcolor: " << tempzColor << endl;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(myz == 0) {
                    for (int k = 0; k < abs(dely); k++) {
                        tempxColor = x0col + (xicol - x0col ) * k / dely;
                        tempyColor = y0col + (yicol - y0col ) * k / dely;
                        tempzColor = z0col + (zicol - z0col ) * k / dely;
//                        cout << "x0color: " << x0col
//                             << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "tempx: " << tempxColor << ", tempy: "
//                        << tempyColor << ", tempz: " << tempzColor << endl;
//                        cout << endl;
                        z = tempz;
                        y = tempy + 1;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(myz > 1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz + 1;
                        y = tempy + 1/myz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }
                if(myz < -1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz - 1;
                        y = tempy - 1/myz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorACFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }
            } else{
//                cout << "mxy = nananan" << endl;
            }

        }

    }

    //BC Face
    for(int i = 0; i < polyhedraGlobalYZ.size(); ++i){

        for(int j = 0; j < polyhedraGlobalYZ[i].getNumFaces(); ++j){
            matrixYZCoorBCFace[i][j] = 0;
//            DDAImplePointsXYCoorABFace[i][j] = 0;
            //first aFace, bface

            x0 = polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            xi = polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getCFace(j) - 1);
            y0 = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            yi = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getCFace(j) - 1);
            z0 = polyhedraGlobalYZ[i].getzCoor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            zi = polyhedraGlobalYZ[i].getzCoor(polyhedraGlobalYZ[i].getCFace(j) - 1);


            x0col = polyhedraGlobalYZ[i].getxColor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            xicol = polyhedraGlobalYZ[i].getxColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
            y0col = polyhedraGlobalYZ[i].getyColor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            yicol = polyhedraGlobalYZ[i].getyColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
            z0col = polyhedraGlobalYZ[i].getzColor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            zicol = polyhedraGlobalYZ[i].getzColor(polyhedraGlobalYZ[i].getCFace(j) - 1);

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//            cout << endl;
            if(y0 > yi) {
                tempx = x0;
                tempxcol = x0col;
                x0 = xi;
                x0col = xicol;
                xi = tempx;
                xicol = tempxcol;

                tempy = y0;
                tempycol = y0col;
                y0 = yi;
                y0col = yicol;
                yi = tempy;
                yicol = tempycol;

                tempz = z0;
                tempzcol = z0col;
                z0 = zi;
                z0col = zicol;
                zi = tempz;
                zicol = tempzcol;
            }
            delx = xi - x0;
            dely = yi - y0;
            delz = zi - z0;

//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;



//            cout << "x0color: " << x0col
//                 << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//            cout << "xicolor: " << xicol
//                 << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
            if (!(dely == 0 && delz == 0)) {
                myz = delz / dely;
                tempy = y0;
                tempz = z0;
                //add points itself
//                cout << "x0color: " << x0col
//                     << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                cout << "xicolor: " << xicol
//                     << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
                if((myz > 0 && myz <=1) || (myz < 0 && myz >= -1)) {
                    for (int k = 0; k < abs(dely); k++) {
                        z = tempz + myz;
                        y = tempy + 1;
                        //FIXME: check if this formula correct, mostly k or k + 1 or other
                        tempxColor = x0col + (xicol - x0col ) * k / dely;
                        tempyColor = y0col + (yicol - y0col ) * k / dely;
                        tempzColor = z0col + (zicol - z0col ) * k / dely;
//                       cout << "x0color: " << x0col
//                        << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "xcolor: " << tempxColor
//                        << ", ycolor: " << tempyColor << ", zcolor: " << tempzColor << endl;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(myz == 0) {
                    for (int k = 0; k < abs(dely); k++) {
                        tempxColor = x0col + (xicol - x0col ) * k / dely;
                        tempyColor = y0col + (yicol - y0col ) * k / dely;
                        tempzColor = z0col + (zicol - z0col ) * k / dely;
//                        cout << "x0color: " << x0col
//                             << ", y0color: " << y0col << ", z0color: " << z0col << endl;
//                        cout << "xicolor: " << xicol
//                             << ", yicolor: " << yicol << ", zicolor: " << zicol << endl;
//                        cout << "tempx: " << tempxColor << ", tempy: "
//                        << tempyColor << ", tempz: " << tempzColor << endl;
//                        cout << endl;
                        z = tempz;
                        y = tempy + 1;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << x << ", yiplus: " << (y) << endl;
                    }
                }
                if(myz > 1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz + 1;
                        y = tempy + 1/myz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }
                if(myz < -1) {
                    for (int k = 0; k < abs(delz); k++) {
                        z = tempz - 1;
                        y = tempy - 1/myz;
                        tempxColor = x0col + (xicol - x0col ) * k / delz;
                        tempyColor = y0col + (yicol - y0col ) * k / delz;
                        tempzColor = z0col + (zicol - z0col ) * k / delz;
                        polyhedraGlobalYZ[i].setx(-1, tempxColor);
                        polyhedraGlobalYZ[i].sety(round(y), tempyColor);
                        polyhedraGlobalYZ[i].setz(round(z), tempzColor);
                        matrixYZCoorBCFace[i][j] += 1;
//                        DDAImplePointsXCoorABFace[i][j][k] = x;
//                        DDAImplePointsYCoorABFace[i][j][k] = y;
                        tempy = y;
                        tempz = z;
                        //cout << "xiplus: " << xiPlus << ", yiplus: " << (yiPlus) << endl;
                    }
                }
            } else{
//                cout << "mxy = nananan" << endl;
            }

        }

    }



    return;
}

void LineFillingXY(){
    glViewport(0, win_height/2, win_width/2, win_height/2);
    glBegin(GL_LINES);
    glColor3f(.5,.5, .5);
    glVertex2f(0, 0);
    glVertex2f(0, grid_height);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(.5,.5, .5);
    glVertex2f(grid_height, 0);
    glVertex2f(grid_width, grid_height);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(.5,.5, .5);
    glVertex2f(0, 0);
    glVertex2f(grid_height, 0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(.5,.5, .5);
    glVertex2f(0, grid_height);
    glVertex2f(grid_width, grid_height);
    glEnd();
//    DDAXY(polyhedraGlobalXY);

    double x1, x2, y1, y2, z1, z2;
    for(int i = 0; i < numShapes; ++i) {
        int xSize = polyhedraGlobalXY[i].getWholeX().size();
        for(int j = 0; j < xSize; j++){
            draw_pix(round(polyhedraGlobalXY[i].getxCoor(j)), round(polyhedraGlobalXY[i].getyCoor(j)),
                     polyhedraGlobalXY[i].getxColor(j) , polyhedraGlobalXY[i].getyColor(j) ,
                     polyhedraGlobalXY[i].getzColor(j));
        }
    }

    return;
}
void LineFillingXZ(){
    glViewport(win_height/2, win_height/2, win_width/2, win_height/2);
    glBegin(GL_LINES);
    glColor3f(0.5,0.5, 0.5);
    glVertex2f(0, 0);
    glVertex2f(0, grid_height);
    glEnd();
//    glBegin(GL_LINES);
//    glColor3f(1,1, 1);
//    glVertex2f(grid_height, 0);
//    glVertex2f(grid_width, grid_height);
//    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.5,0.5, 0.5);
    glVertex2f(0, 0);
    glVertex2f(grid_height, 0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.5,0.5, 0.5);
    glVertex2f(0, grid_height);
    glVertex2f(grid_width, grid_height);
    glEnd();
    double x1, x2, y1, y2, z1, z2;

    for(int i = 0; i < numShapes; ++i) {
        int xSize = polyhedraGlobalXZ[i].getWholeX().size();

        for(int j = 0; j < xSize; j++){
            draw_pix(round(polyhedraGlobalXZ[i].getxCoor(j)), round(polyhedraGlobalXZ[i].getzCoor(j)),
                     polyhedraGlobalXZ[i].getxColor(j), polyhedraGlobalXZ[i].getyColor(j) ,
                     polyhedraGlobalXZ[i].getzColor(j));
        }
    }

    return;
}
void LineFillingYZ(){
    glViewport(0, 0, win_width/2, win_height/2);
//    glBegin(GL_LINES);
//    glColor3f(1,1, 1);
//    glVertex2f(0, 0);
//    glVertex2f(0, grid_height);
//    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.5,0.5, 0.5);
    glVertex2f(grid_height, 0);
    glVertex2f(grid_width, grid_height);
    glEnd();
//    glBegin(GL_LINES);
//    glColor3f(1,1, 1);
//    glVertex2f(0, 0);
//    glVertex2f(grid_height, 0);
//    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.5,.5, .5);
    glVertex2f(0, grid_height);
    glVertex2f(grid_width, grid_height);
    glEnd();
    double x1, x2, y1, y2, z1, z2;

    for(int i = 0; i < numShapes; ++i) {
        int ySize = polyhedraGlobalYZ[i].getWholeY().size();
        for(int j = 0; j < ySize; j++){
            draw_pix(round(polyhedraGlobalYZ[i].getyCoor(j)), round(polyhedraGlobalYZ[i].getzCoor(j)),
                     polyhedraGlobalYZ[i].getxColor(j) , polyhedraGlobalYZ[i].getyColor(j) ,
                     polyhedraGlobalYZ[i].getzColor(j));
        }
    }
    return;
}

bool Compare(const pair<int, double>&a, const pair<int, double>&b){
    return a.second > b.second;
}
void PainterXY(){
    double xa, xb, xc, ya, yb, yc, za, zb, zc, temp1, temp2;
//    double tempaa[5][5000][5000];
    for(int i = 0; i < polyhedraGlobalXY.size(); ++i){
        vector<pair<int, double>> tempFace;
        vector<double> tempA, tempB, tempC;
        for(int j = 0; j < polyhedraGlobalXY[i].getNumFaces(); ++j) {
//            cout << "A: " << polyhedraGlobalXY[i].getAFace(j) << ", B: " << polyhedraGlobalXY[i].getBFace(j) <<
//            ", C: " << polyhedraGlobalXY[i].getCFace(j) << endl;

            temp1 = min(polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getAFace(j) - 1),
                        polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getBFace(j) - 1));
            temp2 = min(polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getCFace(j) - 1),
                        polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getBFace(j) - 1));
            za = min(temp1, temp2);
//            cout << "temp1: " << temp1 << ", temp2: " << temp2 << endl;
//            cout << "index[" << j << "]: related z value: " << za << endl;
            tempFace.push_back(make_pair(j, za));
        }

//        for(int j = 0; j < tempFace.size(); ++j) {
//            cout << "index " << j << ": " << tempFace[j].first << " " << tempFace[j].second << endl;
//        }
        sort(tempFace.begin(), tempFace.end(), Compare);
//        cout << "1: " << tempFace.size() << ", 2: " << polyhedraGlobalXY[i].getNumFaces() << endl;
//        for(int j = 0; j < tempFace.size(); ++j) {
//            cout << "new index " << j << ": " << tempFace[j].first + 1 << " " << tempFace[j].second << endl;
//            cout << polyhedraGlobalXY[i].getAFace(tempFace[j].first) << endl;
//            cout << polyhedraGlobalXY[i].getBFace(tempFace[j].first) << endl;
//            cout << polyhedraGlobalXY[i].getCFace(tempFace[j].first) << endl;
//        }
        for(int j = 0; j < polyhedraGlobalXY[i].getNumFaces(); ++j){
            tempA.push_back(polyhedraGlobalXY[i].getAFace(tempFace[j].first));
            tempB.push_back(polyhedraGlobalXY[i].getBFace(tempFace[j].first));
            tempC.push_back(polyhedraGlobalXY[i].getCFace(tempFace[j].first));
        }
        for(int j = 0; j < polyhedraGlobalXY[i].getNumFaces(); ++j){
            polyhedraGlobalXY[i].replaceAFace(j, tempA[j]);
            polyhedraGlobalXY[i].replaceBFace(j, tempB[j]);
            polyhedraGlobalXY[i].replaceCFace(j, tempC[j]);
        }
//        for(int j = 0; j < polyhedraGlobalXY[i].getNumFaces(); ++j){
//            cout << polyhedraGlobalXY[i].getAFace(j) << " " <<
//            polyhedraGlobalXY[i].getBFace(j) << " " << polyhedraGlobalXY[i].getCFace(j) << endl;
//        }


    }
}
void PainterXZ(){
    double xa, xb, xc, ya, yb, yc, za, zb, zc, temp1, temp2;
//    double tempaa[5][5000][5000];
    for(int i = 0; i < polyhedraGlobalXZ.size(); ++i){
        vector<pair<int, double>> tempFace;
        vector<double> tempA, tempB, tempC;
        for(int j = 0; j < polyhedraGlobalXZ[i].getNumFaces(); ++j) {
//            cout << "A: " << polyhedraGlobalXZ[i].getAFace(j) << ", B: " << polyhedraGlobalXZ[i].getBFace(j) <<
//            ", C: " << polyhedraGlobalXZ[i].getCFace(j) << endl;

            temp1 = min(polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getAFace(j) - 1),
                        polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getBFace(j) - 1));
            temp2 = min(polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getCFace(j) - 1),
                        polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getBFace(j) - 1));
            ya = min(temp1, temp2);
            tempFace.push_back(make_pair(j, ya));
        }

        sort(tempFace.begin(), tempFace.end(), Compare);

        for(int j = 0; j < polyhedraGlobalXZ[i].getNumFaces(); ++j){
            tempA.push_back(polyhedraGlobalXZ[i].getAFace(tempFace[j].first));
            tempB.push_back(polyhedraGlobalXZ[i].getBFace(tempFace[j].first));
            tempC.push_back(polyhedraGlobalXZ[i].getCFace(tempFace[j].first));
        }
        for(int j = 0; j < polyhedraGlobalXZ[i].getNumFaces(); ++j){
            polyhedraGlobalXZ[i].replaceAFace(j, tempA[j]);
            polyhedraGlobalXZ[i].replaceBFace(j, tempB[j]);
            polyhedraGlobalXZ[i].replaceCFace(j, tempC[j]);
        }



    }
}
void PainterYZ(){
    double xa, xb, xc, ya, yb, yc, za, zb, zc, temp1, temp2;
//    double tempaa[5][5000][5000];
    for(int i = 0; i < polyhedraGlobalYZ.size(); ++i){
        vector<pair<int, double>> tempFace;
        vector<double> tempA, tempB, tempC;
        for(int j = 0; j < polyhedraGlobalYZ[i].getNumFaces(); ++j) {
//            cout << "A: " << polyhedraGlobalYZ[i].getAFace(j) << ", B: " << polyhedraGlobalYZ[i].getBFace(j) <<
//            ", C: " << polyhedraGlobalYZ[i].getCFace(j) << endl;

            temp1 = min(polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getAFace(j) - 1),
                        polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getBFace(j) - 1));
            temp2 = min(polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getCFace(j) - 1),
                        polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getBFace(j) - 1));
            xa = min(temp1, temp2);
//            cout << "temp1: " << temp1 << ", temp2: " << temp2 << endl;
//            cout << "index[" << j << "]: related z value: " << za << endl;
            tempFace.push_back(make_pair(j, xa));
        }

//        for(int j = 0; j < tempFace.size(); ++j) {
//            cout << "index " << j << ": " << tempFace[j].first << " " << tempFace[j].second << endl;
//        }
        sort(tempFace.begin(), tempFace.end(), Compare);
//        cout << "1: " << tempFace.size() << ", 2: " << polyhedraGlobalYZ[i].getNumFaces() << endl;
//        for(int j = 0; j < tempFace.size(); ++j) {
//            cout << "new index " << j << ": " << tempFace[j].first + 1 << " " << tempFace[j].second << endl;
//            cout << polyhedraGlobalYZ[i].getAFace(tempFace[j].first) << endl;
//            cout << polyhedraGlobalYZ[i].getBFace(tempFace[j].first) << endl;
//            cout << polyhedraGlobalYZ[i].getCFace(tempFace[j].first) << endl;
//        }
        for(int j = 0; j < polyhedraGlobalYZ[i].getNumFaces(); ++j){
            tempA.push_back(polyhedraGlobalYZ[i].getAFace(tempFace[j].first));
            tempB.push_back(polyhedraGlobalYZ[i].getBFace(tempFace[j].first));
            tempC.push_back(polyhedraGlobalYZ[i].getCFace(tempFace[j].first));
        }
        for(int j = 0; j < polyhedraGlobalYZ[i].getNumFaces(); ++j){
            polyhedraGlobalYZ[i].replaceAFace(j, tempA[j]);
            polyhedraGlobalYZ[i].replaceBFace(j, tempB[j]);
            polyhedraGlobalYZ[i].replaceCFace(j, tempC[j]);
        }
//        for(int j = 0; j < polyhedraGlobalYZ[i].getNumFaces(); ++j){
//            cout << polyhedraGlobalYZ[i].getAFace(j) << " " <<
//            polyhedraGlobalYZ[i].getBFace(j) << " " << polyhedraGlobalYZ[i].getCFace(j) << endl;
//        }


    }
}

void RasterizationXY(){
    int sumIndex = 0;
    //FIXME:: consider lines but not triangle, 2 points in the same height
    double xa, ya, xb, yb, xc, yc, delx, dely, delz,
            xAvg, yAvg, zAvg, xMax, yMax, zMax, xMid, yMid, zMid, xMin, yMin, zMin,
            xToMax, yToMax, zToMax, xToMid, yToMid, zToMid, xToMin, yToMin, zToMin,
            xLeft, xRight, yAll, xIn, xTemp1, yTemp1, zTemp1, xTemp2, yTemp2, xTemp3, yTemp3,
            xTempColor1, yTempColor1, zTempColor1, xTempColor2, yTempColor2, zTempColor2,
            xTempColor3, yTempColor3, zTempColor3, xColor, yColor, zColor;

    for(int i = 0; i < polyhedraGlobalXY.size(); ++i){
        sumIndex = 0;

        // get out AB Face points
        for(int m = 0; m < polyhedraGlobalXY[i].getNumFaces(); ++m) {
            for(int k = 0; k < matrixXYCoorABFace[i][m]; ++k) {
                DDAImplePointsXCoorABFace[m][k] = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsYCoorABFace[m][k] = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsXColorABFace[m][k] = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsYColorABFace[m][k] = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsZColorABFace[m][k] = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsZCoorABFace[m][k] = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
            }
//            DDAImplePointsXCoorABFace[m][matrixXYCoorABFace[i][m] + 1] = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getBFace(m));
//            DDAImplePointsYCoorABFace[m][matrixXYCoorABFace[i][m] + 1] = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getBFace(m));
            sumIndex += matrixXYCoorABFace[i][m];
        }

        // get out AC Face points
        for(int m = 0; m < polyhedraGlobalXY[i].getNumFaces(); ++m){
            for(int k = 0; k < matrixXYCoorACFace[i][m]; ++k) {
//                cout << "related x[" << k << "]: " << polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k) << endl;
                DDAImplePointsXCoorACFace[m][k ] = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsYCoorACFace[m][k ] = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsXColorACFace[m][k] = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsYColorACFace[m][k] = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsZColorACFace[m][k] = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsZCoorACFace[m][k ] = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
            }
            sumIndex += matrixXYCoorACFace[i][m];
        }
//
        //get out BC Face
        for(int m = 0; m < polyhedraGlobalXY[i].getNumFaces(); ++m){
            for(int k = 0; k < matrixXYCoorBCFace[i][m]; ++k) {
//                cout << "related x[" << k << "]: " << polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k) << endl;
//                cout << "related y[" << k << "]: " << polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k) << endl;
                DDAImplePointsXCoorBCFace[m][k] = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsYCoorBCFace[m][k] = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsXColorBCFace[m][k] = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsYColorBCFace[m][k] = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsZColorBCFace[m][k] = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
                DDAImplePointsZCoorBCFace[m][k] = polyhedraGlobalXY[i].getzCoor(polyhedraGlobalXY[i].getNumSides() + sumIndex + k);
            }
//            DDAImplePointsXCoorBCFace[m][matrixXYCoorBCFace[i][m] + 1] = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getCFace(m));
//            DDAImplePointsYCoorBCFace[m][matrixXYCoorBCFace[i][m] + 1] = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getCFace(m));
            sumIndex += matrixXYCoorBCFace[i][m];
        }

        for(int j = 0; j < polyhedraGlobalXY[i].getNumFaces(); ++j) {

            xa = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getAFace(j) - 1);
            ya = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getAFace(j) - 1);
            xb = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getBFace(j) - 1);
            yb = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getBFace(j) - 1);
            xc = polyhedraGlobalXY[i].getxCoor(polyhedraGlobalXY[i].getCFace(j) - 1);
            yc = polyhedraGlobalXY[i].getyCoor(polyhedraGlobalXY[i].getCFace(j) - 1);

//            if((xa == xb && ya == yb) || (ya == yc && xa == xc) || (xb == xc && yb == yc)) {
//                continue;
//            }
//            if((xa == xb && ya == yb)) {
//                continue;
//            }
//            cout << "j2: " << j << endl;

            if((ya >= yb) && (ya >= yc)) {
                yMax = ya;
                xToMax = xa;
                if(yb > yc){
                    yMid = yb;
                    xToMid = xb;
                    yMin = yc;
                    xToMin = xc;
                } else{
                    yMid = yc;
                    xToMid = xc;
                    yMin = yb;
                    xToMin = xb;
                }
            } else if ((yb >= ya) && (yb >= yc)){
                yMax = yb;
                xToMax = xb;
                if(ya > yc){
                    yMid = ya;
                    xToMid = xa;
                    yMin = yc;
                    xToMin = xc;
                } else{
                    yMid = yc;
                    xToMid = xc;
                    yMin = ya;
                    xToMin = xa;
                }
            } else if ((yc >= ya) && (yc >= yb)) {
                yMax = yc;
                xToMax = xc;
                if(yb > ya){
                    yMid = yb;
                    xToMid = xb;
                    yMin = ya;
                    xToMin = xa;
                } else{
                    yMid = ya;
                    xToMid = xa;
                    yMin = yb;
                    xToMin = xb;
                }
            }
            // scanline from ymax to ymin

//            vector<double>::iterator it;
//            vector<double>::iterator itBegin;
//            vector<double>::iterator itEnd;
//            int indexABFace[matrixXYCoorABFace[i][j]];
//            int indexACFace[matrixXYCoorACFace[i][j]];
//            int indexBCFace[matrixXYCoorBCFace[i][j]];



            //AB Face
            double aaa = 0;
            yAll = yMin;
//            cout << "************************" << endl;
            for(int k = 0; k < (yMax - yMin - 1); ++k) {

                yAll = yMin + k + 1;

                double xLeft, xRight, delx, dely;
//                cout << "x imple: " << tempxAB << endl;
//                cout << "y imple: " << tempyAB << endl;
                if((ya - yb) == 0 && (xa - xb) == 0){
//                    cout << "AB Same point" << endl;
                    continue;
                } else if((ya - yc) == 0 && (xa - xc) == 0){
//                    cout << "AC Same point" << endl;
                    continue;
                } else if((yb - yc) == 0 && (xb - xc) == 0){

                    continue;
                }
                //find xleft and xright
                xLeft = -1;
                xRight = -1;
                xTemp1 = -1;
                xTemp2 = -1;
                xTemp3 = -1;
//                cout << "j: " << j + 1 << endl;
//                cout << "yAll: " << yAll << endl;
                for(int l = 0; l < matrixXYCoorABFace[i][j] ; ++l){
                    if(yAll == DDAImplePointsYCoorABFace[j][l]){

//                        cout << "DDAImplePointsYCoorABFace[j][l]: " << DDAImplePointsYCoorABFace[j][l] << endl;
                        xTemp1 = DDAImplePointsXCoorABFace[j][l];
                        xTempColor1 = DDAImplePointsXColorABFace[j][l];
                        yTempColor1 = DDAImplePointsYColorABFace[j][l];
                        zTempColor1 = DDAImplePointsZColorABFace[j][l];

//                        cout<< "xtemp1: " << xTemp1<< endl;
//                        break;
                    } else {

                    }
                }
//                cout << "xtemp1: " << xTemp1 << endl;
//                cout << "matrixXYCoorACFace[i][j]: " << matrixXYCoorACFace[i][j] << endl;
                for(int l = 0; l < matrixXYCoorACFace[i][j] ; ++l){
                    if(yAll == DDAImplePointsYCoorACFace[j][l]){
//                        cout << "yAll: " << yAll << endl;
//                        cout << "DDAImplePointsYCoorACFace[j][l]: " << DDAImplePointsYCoorACFace[j][l] << endl;
                        xTemp2 = DDAImplePointsXCoorACFace[j][l];
                        xTempColor2 = DDAImplePointsXColorACFace[j][l];
                        yTempColor2 = DDAImplePointsYColorACFace[j][l];
                        zTempColor2 = DDAImplePointsZColorACFace[j][l];
//                        cout<< "xtemp2AC: " << xTemp2<< endl;
//                        break;
//                    } else {

                    }
                }
                for(int l = 0; l < matrixXYCoorBCFace[i][j]; ++l){
                    if(yAll == DDAImplePointsYCoorBCFace[j][l]){
//                        cout << "yAll: " << yAll << endl;
//                        cout << "DDAImplePointsYCoorACFace[j][l]: " << DDAImplePointsYCoorACFace[j][l] << endl;
                        xTemp3 = DDAImplePointsXCoorBCFace[j][l];
                        xTempColor3 = DDAImplePointsXColorBCFace[j][l];
                        yTempColor3 = DDAImplePointsYColorBCFace[j][l];
                        zTempColor3 = DDAImplePointsZColorBCFace[j][l];
//                        cout<< "xtemp3: " << xTemp3 << endl;
                        break;
                    } else {

                    }
                }

//                cout << "xtemp1: " << xTemp1 << endl;
//                cout << "xtemp2: " << xTemp2 << endl;
//                cout << "xtemp3: " << xTemp3 << endl;

                //set points
                if(xTemp1 == -1 && xTemp2 != -1 && xTemp3 != -1){

                    for(int l = 1; l < int(abs(xTemp2 - xTemp3)); ++l){
//                        cout << "delx: " <<abs(xTemp2 - xTemp3) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xTemp2, xTemp3);
                        xRight = max(xTemp2, xTemp3);
                        if(xTemp2 < xTemp3){
                            xLeft = xTemp2;
                            xRight = xTemp3;
                            xColor = xTempColor2 + (xTempColor3 - xTempColor2) * l / abs(xTemp2 - xTemp3);
                            yColor = yTempColor2 + (yTempColor3 - yTempColor2) * l / abs(xTemp2 - xTemp3);
                            zColor = zTempColor2 + (zTempColor3 - zTempColor2) * l / abs(xTemp2 - xTemp3);
                        } else if (xTemp2 > xTemp3){
                            xLeft = xTemp3;
                            xRight = xTemp2;
                            xColor = xTempColor3 + (xTempColor2 - xTempColor3) * l / abs(xTemp2 - xTemp3);
                            yColor = yTempColor3 + (yTempColor2 - yTempColor3) * l / abs(xTemp2 - xTemp3);
                            zColor = zTempColor3 + (zTempColor2 - zTempColor3) * l / abs(xTemp2 - xTemp3);
                        }
                        polyhedraGlobalXY[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXY[i].sety(yAll, yColor);
                        polyhedraGlobalXY[i].setz(-1, zColor);
//                        cout << "xcolor: " << xColor << ", ycolor: " << yColor << ", zcolor: " << zColor << endl;
                    }
                }
                if(xTemp2 == -1 && xTemp1 != -1 && xTemp3 != -1){
//                    cout<< "here" << endl;
                    for(int l = 1; l < int(abs(xTemp1 - xTemp3)); ++l){
//                        cout << "xtemp1: " << xTemp1 << ", xtemp2: " << xTemp2 << ", xtemp3: " << xTemp3 << endl;
//                        cout << "delx: " <<abs(xTemp1 - xTemp3) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xTemp1, xTemp3);
                        xRight = max(xTemp1, xTemp3);
                        if(xTemp1 <= xTemp3){
                            xLeft = xTemp1;
                            xRight = xTemp3;
                            xColor = xTempColor1 + (xTempColor3 - xTempColor1) * l / abs(xTemp1 - xTemp3);
                            yColor = yTempColor1 + (yTempColor3 - yTempColor1) * l / abs(xTemp1 - xTemp3);
                            zColor = zTempColor1 + (zTempColor3 - zTempColor1) * l / abs(xTemp1 - xTemp3);
                        } else {
                            xLeft = xTemp3;
                            xRight = xTemp1;
                            xColor = xTempColor3 + (xTempColor1 - xTempColor3) * l / abs(xTemp1 - xTemp3);
                            yColor = yTempColor3 + (yTempColor1 - yTempColor3) * l / abs(xTemp1 - xTemp3);
                            zColor = zTempColor3 + (zTempColor1 - zTempColor3) * l / abs(xTemp1 - xTemp3);
                        }
                        polyhedraGlobalXY[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXY[i].sety(yAll, yColor);
                        polyhedraGlobalXY[i].setz(-1, zColor);
                    }
                }

                if(xTemp3 == -1 && xTemp1 != -1 && xTemp2 != -1){
//                    cout<< "here" << endl;
                    for(int l = 1; l < int(abs(xTemp2 - xTemp1)); ++l){
//                        cout << "xtemp1: " << xTemp2 << ", xtemp3: " << xTemp3 << endl;
//                        cout << "delx: " <<abs(xTemp2 - xTemp3) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xTemp2, xTemp1);
                        xRight = max(xTemp2, xTemp1);

                        if(xTemp1 <= xTemp2){
                            xLeft = xTemp1;
                            xRight = xTemp2;
                            xColor = xTempColor1 + (xTempColor2 - xTempColor1) * l / abs(xTemp1 - xTemp2);
                            yColor = yTempColor1 + (yTempColor2 - yTempColor1) * l / abs(xTemp1 - xTemp2);
                            zColor = zTempColor1 + (zTempColor2 - zTempColor1) * l / abs(xTemp1 - xTemp2);
                        } else {
                            xLeft = xTemp2;
                            xRight = xTemp1;
                            xColor = xTempColor2 + (xTempColor1 - xTempColor2) * l / abs(xTemp1 - xTemp2);
                            yColor = yTempColor2 + (yTempColor1 - yTempColor2) * l / abs(xTemp1 - xTemp2);
                            zColor = zTempColor2 + (zTempColor1 - zTempColor2) * l / abs(xTemp1 - xTemp2);
                        }
                        polyhedraGlobalXY[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXY[i].sety(yAll, yColor);
                        polyhedraGlobalXY[i].setz(-1, zColor);
                    }

                }


                // temp2 and temp3 share point c
                if(xTemp2 == xTemp3 && xTemp1 != -1 ){
//                    if(j == 10){
//                        cout << "j: " << j + 1 << endl;
//                        cout << "yAll: " << yAll << endl;
//                        cout << "xtemp1: " << xTemp1 << ", xtemp2: " << xTemp2 <<", xtemp3: " << xTemp3 << endl;
                    xTempColor3 = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getCFace(j) - 1);
                    yTempColor3 = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getCFace(j) - 1);
                    zTempColor3 = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getCFace(j) - 1);
                    for(int l = 0; l < int(abs(xc - xTemp1)); ++l){
//                            cout << "xtemp1: " << xTemp1 << ", xc: " << xc << endl;
//                        cout << "delx: " <<abs(xTemp2 - xTemp1) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xc, xTemp1);
                        xRight = max(xc, xTemp1);

                        if(xTemp1 <= xc){
                            xLeft = xTemp1;
                            xRight = xc;
                            xColor = xTempColor1 + (xTempColor3 - xTempColor1) * l / abs(xTemp1 - xc);
                            yColor = yTempColor1 + (yTempColor3 - yTempColor1) * l / abs(xTemp1 - xc);
                            zColor = zTempColor1 + (zTempColor3 - zTempColor1) * l / abs(xTemp1 - xc);
                        } else {
                            xLeft = xc;
                            xRight = xTemp1;
                            xColor = xTempColor3 + (xTempColor1 - xTempColor3) * l / abs(xTemp1 - xc);
                            yColor = yTempColor3 + (yTempColor1 - yTempColor3) * l / abs(xTemp1 - xc);
                            zColor = zTempColor3 + (zTempColor1 - zTempColor3) * l / abs(xTemp1 - xc);
                        }
                        polyhedraGlobalXY[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXY[i].sety(yAll, yColor);
                        polyhedraGlobalXY[i].setz(-1, zColor);
                    }
////                    }
//
                }
                // temp1 and temp3 share point b
                if(xTemp1 == xTemp3 && xTemp2 != -1 ){
//                    if(j == 10){
//                        cout << "j: " << j + 1 << endl;
//                        cout << "yAll: " << yAll << endl;
//                        cout << "xtemp1: " << xTemp1 << ", xtemp2: " << xTemp2 <<", xtemp3: " << xTemp3 << endl;
                    xTempColor3 = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getCFace(j) - 1);
                    yTempColor3 = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getCFace(j) - 1);
                    zTempColor3 = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getCFace(j) - 1);
                    for(int l = 0; l < int(abs(xb - xTemp2)); ++l){
//                            cout << "xtemp1: " << xTemp1 << ", xc: " << xc << endl;
//                        cout << "delx: " <<abs(xTemp2 - xTemp1) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xb, xTemp2);
                        xRight = max(xb, xTemp2);

                        if(xTemp2 <= xb){
                            xLeft = xTemp2;
                            xRight = xb;
                            xColor = xTempColor2 + (xTempColor3 - xTempColor2) * l / abs(xb - xTemp2);
                            yColor = yTempColor2 + (yTempColor3 - yTempColor2) * l / abs(xb - xTemp2);
                            zColor = zTempColor2 + (zTempColor3 - zTempColor2) * l / abs(xb - xTemp2);
                        } else {
                            xLeft = xb;
                            xRight = xTemp2;
                            xColor = xTempColor3 + (xTempColor2 - xTempColor3) * l / abs(xb - xTemp2);
                            yColor = yTempColor3 + (yTempColor2 - yTempColor3) * l / abs(xb - xTemp2);
                            zColor = zTempColor3 + (zTempColor2 - zTempColor3) * l / abs(xb - xTemp2);
                        }
                        polyhedraGlobalXY[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXY[i].sety(yAll, yColor);
                        polyhedraGlobalXY[i].setz(-1, zColor);
                    }

                }
                // temp1 and temp2 share point a
                if(xTemp1 == xTemp2 && xTemp3 != -1 ){
//                    if(j == 10){
//                        cout << "j: " << j + 1 << endl;
//                        cout << "yAll: " << yAll << endl;
//                        cout << "xtemp1: " << xTemp1 << ", xtemp2: " << xTemp2 <<", xtemp3: " << xTemp3 << endl;
                    xTempColor2 = polyhedraGlobalXY[i].getxColor(polyhedraGlobalXY[i].getCFace(j) - 1);
                    yTempColor2 = polyhedraGlobalXY[i].getyColor(polyhedraGlobalXY[i].getCFace(j) - 1);
                    zTempColor2 = polyhedraGlobalXY[i].getzColor(polyhedraGlobalXY[i].getCFace(j) - 1);
                    for(int l = 0; l < int(abs(xa - xTemp3)); ++l){
//                            cout << "xtemp1: " << xTemp1 << ", xc: " << xc << endl;
//                        cout << "delx: " <<abs(xTemp2 - xTemp1) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xa, xTemp3);
                        xRight = max(xa, xTemp3);

                        if(xa <= xTemp3){
                            xLeft = xa;
                            xRight = xTemp3;
                            xColor = xTempColor2 + (xTempColor3 - xTempColor2) * l / abs(xa - xTemp3);
                            yColor = yTempColor2 + (yTempColor3 - yTempColor2) * l / abs(xa - xTemp3);
                            zColor = zTempColor2 + (zTempColor3 - zTempColor2) * l / abs(xa - xTemp3);
                        } else {
                            xLeft = xTemp3;
                            xRight = xa;
                            xColor = xTempColor3 + (xTempColor2 - xTempColor3) * l / abs(xa - xTemp3);
                            yColor = yTempColor3 + (yTempColor2 - yTempColor3) * l / abs(xa - xTemp3);
                            zColor = zTempColor3 + (zTempColor2 - zTempColor3) * l / abs(xa - xTemp3);
                        }
                        polyhedraGlobalXY[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXY[i].sety(yAll, yColor);
                        polyhedraGlobalXY[i].setz(-1, zColor);
                    }

                }


            }

        }



    }

}
void RasterizationXZ(){
    int sumIndex = 0;
    //FIXME:: consider lines but not triangle, 2 points in the same height
    double xa, ya, xb, yb, xc, yc, za, zb, zc, delx, dely, delz,
            xAvg, yAvg, zAvg, xMax, yMax, zMax, xMid, yMid, zMid, xMin, yMin, zMin,
            xToMax, yToMax, zToMax, xToMid, yToMid, zToMid, xToMin, yToMin, zToMin,
            xLeft, xRight, xAll, yAll, zAll, xIn, xTemp1, yTemp1, zTemp1, xTemp2, yTemp2, xTemp3, yTemp3,
            xTempColor1, yTempColor1, zTempColor1, xTempColor2, yTempColor2, zTempColor2,
            xTempColor3, yTempColor3, zTempColor3, xColor, yColor, zColor;

    for(int i = 0; i < polyhedraGlobalXZ.size(); ++i) {
        sumIndex = 0;
        // get out AB Face points

        for (int m = 0; m < polyhedraGlobalXZ[i].getNumFaces(); ++m) {
//            cout << "matrixXZCoorABFace: " << matrixXZCoorABFace[i][m] << endl;
            for (int k = 0; k < matrixXZCoorABFace[i][m]; ++k) {
                DDAImplePointsXCoorABFace[m][k] = polyhedraGlobalXZ[i].getxCoor(
                        polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsXColorABFace[m][k] = polyhedraGlobalXZ[i].getxColor(
                        polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);

                DDAImplePointsYCoorABFace[m][k] = polyhedraGlobalXZ[i].getyCoor(
                        polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsYColorABFace[m][k] = polyhedraGlobalXZ[i].getyColor(
                        polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);

                DDAImplePointsZCoorABFace[m][k] = polyhedraGlobalXZ[i].getzCoor(
                        polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsZColorABFace[m][k] = polyhedraGlobalXZ[i].getzColor(
                        polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
            }
            sumIndex += matrixXZCoorABFace[i][m];
        }

        // get out AC Face points
        for(int m = 0; m < polyhedraGlobalXZ[i].getNumFaces(); ++m){
          for(int k = 0; k < matrixXZCoorACFace[i][m]; ++k) {
//                cout << "related x[" << k << "]: " << polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k) << endl;
                DDAImplePointsXCoorACFace[m][k ] = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsYCoorACFace[m][k ] = polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsXColorACFace[m][k] = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsYColorACFace[m][k] = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsZCoorACFace[m][k] = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);

                DDAImplePointsZColorACFace[m][k] = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
            }
//            DDAImplePointsXCoorACFace[m][matrixXZCoorACFace[i][m] + 1] = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getCFace(m));
//            DDAImplePointsYCoorACFace[m][matrixXZCoorACFace[i][m] + 1] = polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getCFace(m));
            sumIndex += matrixXZCoorACFace[i][m];
        }

        //BC Face
        for(int m = 0; m < polyhedraGlobalXZ[i].getNumFaces(); ++m){
          for(int k = 0; k < matrixXZCoorBCFace[i][m]; ++k) {
//                cout << "related x[" << k << "]: " << polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k) << endl;
//                cout << "related y[" << k << "]: " << polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k) << endl;
                DDAImplePointsXCoorBCFace[m][k] = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsYCoorBCFace[m][k] = polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsXColorBCFace[m][k] = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsYColorBCFace[m][k] = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsZCoorBCFace[m][k] = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsZColorBCFace[m][k] = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getNumSides() + sumIndex + k);
            }
//            DDAImplePointsXCoorBCFace[m][matrixXZCoorBCFace[i][m] + 1] = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getCFace(m));
//            DDAImplePointsYCoorBCFace[m][matrixXZCoorBCFace[i][m] + 1] = polyhedraGlobalXZ[i].getyCoor(polyhedraGlobalXZ[i].getCFace(m));
            sumIndex += matrixXZCoorBCFace[i][m];
        }

        for(int j = 0; j < polyhedraGlobalXZ[i].getNumFaces(); ++j) {

            xa = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            za = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getAFace(j) - 1);
            xb = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            zb = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getBFace(j) - 1);
            xc = polyhedraGlobalXZ[i].getxCoor(polyhedraGlobalXZ[i].getCFace(j) - 1);
            zc = polyhedraGlobalXZ[i].getzCoor(polyhedraGlobalXZ[i].getCFace(j) - 1);

            if((za >= zb) && (za >= zc)) {
                zMax = za;
                xToMax = xa;
                if(zb > zc){
                    zMid = zb;
                    xToMid = xb;
                    zMin = zc;
                    xToMin = xc;
                } else{
                    zMid = zc;
                    xToMid = xc;
                    zMin = zb;
                    xToMin = xb;
                }
            } else if ((zb >= za) && (zb >= zc)){
                zMax = zb;
                xToMax = xb;
                if(za > zc){
                    zMid = za;
                    xToMid = xa;
                    zMin = zc;
                    xToMin = xc;
                } else{
                    zMid = zc;
                    xToMid = xc;
                    zMin = za;
                    xToMin = xa;
                }
            } else if ((zc >= za) && (zc >= zb)) {
                zMax = zc;
                xToMax = xc;
                if(zb > za){
                    zMid = zb;
                    xToMid = xb;
                    zMin = za;
                    xToMin = xa;
                } else{
                    zMid = za;
                    xToMid = xa;
                    zMin = zb;
                    xToMin = xb;
                }
            }

            //AB Face
            double aaa = 0;
            zAll = zMin;
//            cout << "************************" << endl;
            for(int k = 0; k < (zMax - zMin - 1); ++k) {

                zAll = zMin + k + 1;

                double xLeft, xRight, delx, delz;
//                cout << "x imple: " << tempxAB << endl;
//                cout << "z imple: " << tempzAB << endl;
                if ((za - zb) == 0 && (xa - xb) == 0) {
//                    cout << "AB Same point" << endl;
                    continue;
                } else if ((za - zc) == 0 && (xa - xc) == 0) {
//                    cout << "AC Same point" << endl;
                    continue;
                } else if ((zb - zc) == 0 && (xb - xc) == 0) {

                    continue;
                }
                //find xleft and xright
                xLeft = -1;
                xRight = -1;
                xTemp1 = -1;
                xTemp2 = -1;
                xTemp3 = -1;
//                cout << "j: " << j + 1 << endl;
//                cout << "zAll: " << zAll << endl;
                for(int l = 0; l < matrixXZCoorABFace[i][j] ; ++l){
                    if(zAll == DDAImplePointsZCoorABFace[j][l]){
                        xTemp1 = DDAImplePointsXCoorABFace[j][l];
                        xTempColor1 = DDAImplePointsXColorABFace[j][l];
                        yTempColor1 = DDAImplePointsYColorABFace[j][l];
                        zTempColor1 = DDAImplePointsZColorABFace[j][l];

//                        cout<< "xtemp1: " << xTemp1<< endl;
//                        break;
                    } else {

                    }
                }

                for(int l = 0; l < matrixXZCoorACFace[i][j] ; ++l){
                    if(zAll == DDAImplePointsZCoorACFace[j][l]){
//                        cout << "zAll: " << zAll << endl;
//                        cout << "DDAImplePointszCoorACFace[j][l]: " << DDAImplePointszCoorACFace[j][l] << endl;
                        xTemp2 = DDAImplePointsXCoorACFace[j][l];
                        xTempColor2 = DDAImplePointsXColorACFace[j][l];
                        yTempColor2 = DDAImplePointsYColorACFace[j][l];
                        zTempColor2 = DDAImplePointsZColorACFace[j][l];
//                        cout<< "xtemp2AC: " << xTemp2<< endl;
//                        break;
//                    } else {

                    }
                }

                for(int l = 0; l < matrixXZCoorBCFace[i][j]; ++l){
                    if(zAll == DDAImplePointsZCoorBCFace[j][l]){
//                        cout << "yAll: " << yAll << endl;
//                        cout << "DDAImplePointsYCoorACFace[j][l]: " << DDAImplePointsYCoorACFace[j][l] << endl;
                        xTemp3 = DDAImplePointsXCoorBCFace[j][l];
                        xTempColor3 = DDAImplePointsXColorBCFace[j][l];
                        yTempColor3 = DDAImplePointsYColorBCFace[j][l];
                        zTempColor3 = DDAImplePointsZColorBCFace[j][l];
//                        cout<< "xtemp3: " << xTemp3 << endl;
                        break;

                    }
                }

                //set points
                if(xTemp1 == -1 && xTemp2 != -1 && xTemp3 != -1){

                    for(int l = 1; l < int(abs(xTemp2 - xTemp3)); ++l){
//                        cout << "delx: " <<abs(xTemp2 - xTemp3) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xTemp2, xTemp3);
                        xRight = max(xTemp2, xTemp3);
                        if(xTemp2 < xTemp3){
                            xLeft = xTemp2;
                            xRight = xTemp3;
                            xColor = xTempColor2 + (xTempColor3 - xTempColor2) * l / abs(xTemp2 - xTemp3);
                            yColor = yTempColor2 + (yTempColor3 - yTempColor2) * l / abs(xTemp2 - xTemp3);
                            zColor = zTempColor2 + (zTempColor3 - zTempColor2) * l / abs(xTemp2 - xTemp3);
                        } else if (xTemp2 > xTemp3){
                            xLeft = xTemp3;
                            xRight = xTemp2;
                            xColor = xTempColor3 + (xTempColor2 - xTempColor3) * l / abs(xTemp2 - xTemp3);
                            yColor = yTempColor3 + (yTempColor2 - yTempColor3) * l / abs(xTemp2 - xTemp3);
                            zColor = zTempColor3 + (zTempColor2 - zTempColor3) * l / abs(xTemp2 - xTemp3);
                        }
                        polyhedraGlobalXZ[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXZ[i].sety(-1, yColor);
                        polyhedraGlobalXZ[i].setz(zAll, zColor);
//                        cout << "xcolor: " << xColor << ", ycolor: " << yColor << ", zcolor: " << zColor << endl;
                    }
                }

                if(xTemp2 == -1 && xTemp1 != -1 && xTemp3 != -1){
//                    cout<< "here" << endl;
                    for(int l = 1; l < int(abs(xTemp1 - xTemp3)); ++l){
//                        cout << "xtemp1: " << xTemp1 << ", xtemp2: " << xTemp2 << ", xtemp3: " << xTemp3 << endl;
//                        cout << "delx: " <<abs(xTemp1 - xTemp3) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xTemp1, xTemp3);
                        xRight = max(xTemp1, xTemp3);
                        if(xTemp1 <= xTemp3){
                            xLeft = xTemp1;
                            xRight = xTemp3;
                            xColor = xTempColor1 + (xTempColor3 - xTempColor1) * l / abs(xTemp1 - xTemp3);
                            yColor = yTempColor1 + (yTempColor3 - yTempColor1) * l / abs(xTemp1 - xTemp3);
                            zColor = zTempColor1 + (zTempColor3 - zTempColor1) * l / abs(xTemp1 - xTemp3);
                        } else {
                            xLeft = xTemp3;
                            xRight = xTemp1;
                            xColor = xTempColor3 + (xTempColor1 - xTempColor3) * l / abs(xTemp1 - xTemp3);
                            yColor = yTempColor3 + (yTempColor1 - yTempColor3) * l / abs(xTemp1 - xTemp3);
                            zColor = zTempColor3 + (zTempColor1 - zTempColor3) * l / abs(xTemp1 - xTemp3);
                        }
                        polyhedraGlobalXZ[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXZ[i].sety(-1, yColor);
                        polyhedraGlobalXZ[i].setz(zAll, zColor);
                    }
                }

                if(xTemp3 == -1 && xTemp1 != -1 && xTemp2 != -1){
//                    cout<< "here" << endl;
                    for(int l = 1; l < int(abs(xTemp2 - xTemp1)); ++l){
//                        cout << "xtemp1: " << xTemp2 << ", xtemp3: " << xTemp3 << endl;
//                        cout << "delx: " <<abs(xTemp2 - xTemp3) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xTemp2, xTemp1);
                        xRight = max(xTemp2, xTemp1);

                        if(xTemp1 <= xTemp2){
                            xLeft = xTemp1;
                            xRight = xTemp2;
                            xColor = xTempColor1 + (xTempColor2 - xTempColor1) * l / abs(xTemp1 - xTemp2);
                            yColor = yTempColor1 + (yTempColor2 - yTempColor1) * l / abs(xTemp1 - xTemp2);
                            zColor = zTempColor1 + (zTempColor2 - zTempColor1) * l / abs(xTemp1 - xTemp2);
                        } else {
                            xLeft = xTemp2;
                            xRight = xTemp1;
                            xColor = xTempColor2 + (xTempColor1 - xTempColor2) * l / abs(xTemp1 - xTemp2);
                            yColor = yTempColor2 + (yTempColor1 - yTempColor2) * l / abs(xTemp1 - xTemp2);
                            zColor = zTempColor2 + (zTempColor1 - zTempColor2) * l / abs(xTemp1 - xTemp2);
                        }
                        polyhedraGlobalXZ[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXZ[i].sety(-1, yColor);
                        polyhedraGlobalXZ[i].setz(zAll, zColor);
                    }

                }

                // temp2 and temp3 share point c
                if(xTemp2 == xTemp3 && xTemp1 != -1 ){
//                    if(j == 10){
//                        cout << "j: " << j + 1 << endl;
//                        cout << "yAll: " << yAll << endl;
//                        cout << "xtemp1: " << xTemp1 << ", xtemp2: " << xTemp2 <<", xtemp3: " << xTemp3 << endl;
                    xTempColor3 = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
                    yTempColor3 = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
                    zTempColor3 = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
                    for(int l = 0; l < int(abs(xc - xTemp1)); ++l){
//                            cout << "xtemp1: " << xTemp1 << ", xc: " << xc << endl;
//                        cout << "delx: " <<abs(xTemp2 - xTemp1) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xc, xTemp1);
                        xRight = max(xc, xTemp1);

                        if(xTemp1 <= xc){
                            xLeft = xTemp1;
                            xRight = xc;
                            xColor = xTempColor1 + (xTempColor3 - xTempColor1) * l / abs(xTemp1 - xc);
                            yColor = yTempColor1 + (yTempColor3 - yTempColor1) * l / abs(xTemp1 - xc);
                            zColor = zTempColor1 + (zTempColor3 - zTempColor1) * l / abs(xTemp1 - xc);
                        } else {
                            xLeft = xc;
                            xRight = xTemp1;
                            xColor = xTempColor3 + (xTempColor1 - xTempColor3) * l / abs(xTemp1 - xc);
                            yColor = yTempColor3 + (yTempColor1 - yTempColor3) * l / abs(xTemp1 - xc);
                            zColor = zTempColor3 + (zTempColor1 - zTempColor3) * l / abs(xTemp1 - xc);
                        }
                        polyhedraGlobalXZ[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXZ[i].sety(-1, yColor);
                        polyhedraGlobalXZ[i].setz(zAll, zColor);
                    }

                }

                // temp1 and temp3 share point b
                if(xTemp1 == xTemp3 && xTemp2 != -1 ){
//                    if(j == 10){
//                        cout << "j: " << j + 1 << endl;
//                        cout << "yAll: " << yAll << endl;
//                        cout << "xtemp1: " << xTemp1 << ", xtemp2: " << xTemp2 <<", xtemp3: " << xTemp3 << endl;
                    xTempColor3 = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
                    yTempColor3 = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
                    zTempColor3 = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
                    for(int l = 0; l < int(abs(xb - xTemp2)); ++l){
//                            cout << "xtemp1: " << xTemp1 << ", xc: " << xc << endl;
//                        cout << "delx: " <<abs(xTemp2 - xTemp1) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xb, xTemp2);
                        xRight = max(xb, xTemp2);

                        if(xTemp2 <= xb){
                            xLeft = xTemp2;
                            xRight = xb;
                            xColor = xTempColor2 + (xTempColor3 - xTempColor2) * l / abs(xb - xTemp2);
                            yColor = yTempColor2 + (yTempColor3 - yTempColor2) * l / abs(xb - xTemp2);
                            zColor = zTempColor2 + (zTempColor3 - zTempColor2) * l / abs(xb - xTemp2);
                        } else {
                            xLeft = xb;
                            xRight = xTemp2;
                            xColor = xTempColor3 + (xTempColor2 - xTempColor3) * l / abs(xb - xTemp2);
                            yColor = yTempColor3 + (yTempColor2 - yTempColor3) * l / abs(xb - xTemp2);
                            zColor = zTempColor3 + (zTempColor2 - zTempColor3) * l / abs(xb - xTemp2);
                        }
                        polyhedraGlobalXZ[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXZ[i].sety(-1, yColor);
                        polyhedraGlobalXZ[i].setz(zAll, zColor);
                    }

                }

                // temp1 and temp2 share point a
                if(xTemp1 == xTemp2 && xTemp3 != -1 ){
//                    if(j == 10){
//                        cout << "j: " << j + 1 << endl;
//                        cout << "yAll: " << yAll << endl;
//                        cout << "xtemp1: " << xTemp1 << ", xtemp2: " << xTemp2 <<", xtemp3: " << xTemp3 << endl;
                    xTempColor2 = polyhedraGlobalXZ[i].getxColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
                    yTempColor2 = polyhedraGlobalXZ[i].getyColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
                    zTempColor2 = polyhedraGlobalXZ[i].getzColor(polyhedraGlobalXZ[i].getCFace(j) - 1);
                    for(int l = 0; l < int(abs(xa - xTemp3)); ++l){
//                            cout << "xtemp1: " << xTemp1 << ", xc: " << xc << endl;
//                        cout << "delx: " <<abs(xTemp2 - xTemp1) << endl;
                        //FIXME: edges not fillin
                        xLeft = min(xa, xTemp3);
                        xRight = max(xa, xTemp3);

                        if(xa <= xTemp3){
                            xLeft = xa;
                            xRight = xTemp3;
                            xColor = xTempColor2 + (xTempColor3 - xTempColor2) * l / abs(xa - xTemp3);
                            yColor = yTempColor2 + (yTempColor3 - yTempColor2) * l / abs(xa - xTemp3);
                            zColor = zTempColor2 + (zTempColor3 - zTempColor2) * l / abs(xa - xTemp3);
                        } else {
                            xLeft = xTemp3;
                            xRight = xa;
                            xColor = xTempColor3 + (xTempColor2 - xTempColor3) * l / abs(xa - xTemp3);
                            yColor = yTempColor3 + (yTempColor2 - yTempColor3) * l / abs(xa - xTemp3);
                            zColor = zTempColor3 + (zTempColor2 - zTempColor3) * l / abs(xa - xTemp3);
                        }
                        polyhedraGlobalXZ[i].setx(xLeft + l, xColor);
                        polyhedraGlobalXZ[i].sety(-1, yColor);
                        polyhedraGlobalXZ[i].setz(zAll, zColor);
                    }

                }


            }
        }
    }
}
void RasterizationYZ() {
    int sumIndex = 0;
    //FIXME:: consider lines but not triangle, 2 points in the same height
    double xa, ya, xb, yb, xc, yc, za, zb, zc, delx, dely, delz,
            xAvg, yAvg, zAvg, xMax, yMax, zMax, xMid, yMid, zMid, xMin, yMin, zMin,
            xToMax, yToMax, zToMax, xToMid, yToMid, zToMid, xToMin, yToMin, zToMin,
            xLeft, xRight, xAll, yAll, zAll, xIn, xTemp1, yTemp1, zTemp1, xTemp2, yTemp2, xTemp3, yTemp3,
            xTempColor1, yTempColor1, zTempColor1, xTempColor2, yTempColor2, zTempColor2,
            xTempColor3, yTempColor3, zTempColor3, xColor, yColor, zColor;
    for (int i = 0; i < polyhedraGlobalYZ.size(); ++i) {
        sumIndex = 0;
        // get out AB Face points
        for (int m = 0; m < polyhedraGlobalYZ[i].getNumFaces(); ++m) {
            for (int k = 0; k < matrixYZCoorABFace[i][m]; ++k) {
                DDAImplePointsXCoorABFace[m][k] = polyhedraGlobalYZ[i].getxCoor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsXColorABFace[m][k] = polyhedraGlobalYZ[i].getxColor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);

                DDAImplePointsYCoorABFace[m][k] = polyhedraGlobalYZ[i].getyCoor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsYColorABFace[m][k] = polyhedraGlobalYZ[i].getyColor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);

                DDAImplePointsZCoorABFace[m][k] = polyhedraGlobalYZ[i].getzCoor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsZColorABFace[m][k] = polyhedraGlobalYZ[i].getzColor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
            }
            sumIndex += matrixYZCoorABFace[i][m];
        }

        // get out AC Face points
        for (int m = 0; m < polyhedraGlobalYZ[i].getNumFaces(); ++m) {
            for (int k = 0; k < matrixYZCoorACFace[i][m]; ++k) {
//                cout << "related x[" << k << "]: " << polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getNumSides() + sumIndex + k) << endl;
                DDAImplePointsXCoorACFace[m][k] = polyhedraGlobalYZ[i].getxCoor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsYCoorACFace[m][k] = polyhedraGlobalYZ[i].getyCoor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsXColorACFace[m][k] = polyhedraGlobalYZ[i].getxColor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsYColorACFace[m][k] = polyhedraGlobalYZ[i].getyColor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsZCoorACFace[m][k] = polyhedraGlobalYZ[i].getzCoor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);

                DDAImplePointsZColorACFace[m][k] = polyhedraGlobalYZ[i].getzColor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
            }
//            DDAImplePointsXCoorACFace[m][matrixYZCoorACFace[i][m] + 1] = polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getCFace(m));
//            DDAImplePointsYCoorACFace[m][matrixYZCoorACFace[i][m] + 1] = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getCFace(m));
            sumIndex += matrixYZCoorACFace[i][m];
        }

        //BC Face
        for (int m = 0; m < polyhedraGlobalYZ[i].getNumFaces(); ++m) {
            for (int k = 0; k < matrixYZCoorBCFace[i][m]; ++k) {
//                cout << "related x[" << k << "]: " << polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getNumSides() + sumIndex + k) << endl;
//                cout << "related y[" << k << "]: " << polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getNumSides() + sumIndex + k) << endl;
                DDAImplePointsXCoorBCFace[m][k] = polyhedraGlobalYZ[i].getxCoor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsYCoorBCFace[m][k] = polyhedraGlobalYZ[i].getyCoor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsXColorBCFace[m][k] = polyhedraGlobalYZ[i].getxColor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsYColorBCFace[m][k] = polyhedraGlobalYZ[i].getyColor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsZCoorBCFace[m][k] = polyhedraGlobalYZ[i].getzCoor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
                DDAImplePointsZColorBCFace[m][k] = polyhedraGlobalYZ[i].getzColor(
                        polyhedraGlobalYZ[i].getNumSides() + sumIndex + k);
            }
//            DDAImplePointsXCoorBCFace[m][matrixYZCoorBCFace[i][m] + 1] = polyhedraGlobalYZ[i].getxCoor(polyhedraGlobalYZ[i].getCFace(m));
//            DDAImplePointsYCoorBCFace[m][matrixYZCoorBCFace[i][m] + 1] = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getCFace(m));
            sumIndex += matrixYZCoorBCFace[i][m];
        }


        for (int j = 0; j < polyhedraGlobalYZ[i].getNumFaces(); ++j) {

            za = polyhedraGlobalYZ[i].getzCoor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            ya = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getAFace(j) - 1);
            zb = polyhedraGlobalYZ[i].getzCoor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            yb = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getBFace(j) - 1);
            zc = polyhedraGlobalYZ[i].getzCoor(polyhedraGlobalYZ[i].getCFace(j) - 1);
            yc = polyhedraGlobalYZ[i].getyCoor(polyhedraGlobalYZ[i].getCFace(j) - 1);

            if ((za >= zb) && (za >= zc)) {
                zMax = za;
                yToMax = ya;
                if (zb > zc) {
                    zMid = zb;
                    yToMid = yb;
                    zMin = zc;
                    yToMin = yc;
                } else {
                    zMid = zc;
                    yToMid = yc;
                    zMin = zb;
                    yToMin = yb;
                }
            } else if ((zb >= za) && (zb >= zc)) {
                zMax = zb;
                yToMax = yb;
                if (za > zc) {
                    zMid = za;
                    yToMid = ya;
                    zMin = zc;
                    yToMin = yc;
                } else {
                    zMid = zc;
                    yToMid = yc;
                    zMin = za;
                    yToMin = ya;
                }
            } else if ((zc >= za) && (zc >= zb)) {
                zMax = zc;
                yToMax = yc;
                if (zb > za) {
                    zMid = zb;
                    yToMid = yb;
                    zMin = za;
                    yToMin = ya;
                } else {
                    zMid = za;
                    yToMid = ya;
                    zMin = zb;
                    yToMin = yb;
                }
            }


            //AB Face
            double aaa = 0;
            zAll = zMin;
//            cout << "************************" << endl;
            for (int k = 0; k < (zMax - zMin - 1); ++k) {

                zAll = zMin + k + 1;

                double yLeft, yRight, dely, delz;
//                cout << "y imple: " << tempyAB << endl;
//                cout << "z imple: " << tempzAB << endl;
                if ((za - zb) == 0 && (ya - yb) == 0) {
//                    cout << "AB Same point" << endl;
                    continue;
                } else if ((za - zc) == 0 && (ya - yc) == 0) {
//                    cout << "AC Same point" << endl;
                    continue;
                } else if ((zb - zc) == 0 && (yb - yc) == 0) {

                    continue;
                }
                //find yleft and yright
                yLeft = -1;
                yRight = -1;
                yTemp1 = -1;
                yTemp2 = -1;
                yTemp3 = -1;
//                cout << "j: " << j + 1 << endl;
//                cout << "zAll: " << zAll << endl;
                for (int l = 0; l < matrixYZCoorABFace[i][j]; ++l) {
                    if (zAll == DDAImplePointsZCoorABFace[j][l]) {
                        yTemp1 = DDAImplePointsYCoorABFace[j][l];
                        xTempColor1 = DDAImplePointsXColorABFace[j][l];
                        yTempColor1 = DDAImplePointsYColorABFace[j][l];
                        zTempColor1 = DDAImplePointsZColorABFace[j][l];

//                        cout<< "xtemp1: " << xTemp1<< endl;
//                        break;
                    } else {

                    }
                }

                for (int l = 0; l < matrixYZCoorACFace[i][j]; ++l) {
                    if (zAll == DDAImplePointsZCoorACFace[j][l]) {
//                        cout << "zAll: " << zAll << endl;
//                        cout << "DDAImplePointszCoorACFace[j][l]: " << DDAImplePointszCoorACFace[j][l] << endl;
                        yTemp2 = DDAImplePointsYCoorACFace[j][l];
                        xTempColor2 = DDAImplePointsXColorACFace[j][l];
                        yTempColor2 = DDAImplePointsYColorACFace[j][l];
                        zTempColor2 = DDAImplePointsZColorACFace[j][l];
//                        cout<< "xtemp2AC: " << xTemp2<< endl;
//                        break;
//                    } else {

                    }
                }

                for (int l = 0; l < matrixYZCoorBCFace[i][j]; ++l) {
                    if (zAll == DDAImplePointsZCoorBCFace[j][l]) {
//                        cout << "yAll: " << yAll << endl;
//                        cout << "DDAImplePointsYCoorACFace[j][l]: " << DDAImplePointsYCoorACFace[j][l] << endl;
                        yTemp3 = DDAImplePointsYCoorBCFace[j][l];
                        xTempColor3 = DDAImplePointsXColorBCFace[j][l];
                        yTempColor3 = DDAImplePointsYColorBCFace[j][l];
                        zTempColor3 = DDAImplePointsZColorBCFace[j][l];
//                        cout<< "xtemp3: " << xTemp3 << endl;
                        break;

                    }
                }

                //set points
                if(yTemp1 == -1 && yTemp2 != -1 && yTemp3 != -1){

                    for(int l = 1; l < int(abs(yTemp2 - yTemp3)); ++l){
//                        cout << "dely: " <<abs(yTemp2 - yTemp3) << endl;
                        //FIyME: edges not fillin
                        yLeft = min(yTemp2, yTemp3);
                        yRight = max(yTemp2, yTemp3);
                        if(yTemp2 < yTemp3){
                            yLeft = yTemp2;
                            yRight = yTemp3;
                            xColor = xTempColor2 + (xTempColor3 - xTempColor2) * l / abs(yTemp2 - yTemp3);
                            yColor = yTempColor2 + (yTempColor3 - yTempColor2) * l / abs(yTemp2 - yTemp3);
                            zColor = zTempColor2 + (zTempColor3 - zTempColor2) * l / abs(yTemp2 - yTemp3);
                        } else if (yTemp2 > yTemp3){
                            yLeft = yTemp3;
                            yRight = yTemp2;
                            xColor = xTempColor3 + (xTempColor2 - xTempColor3) * l / abs(yTemp2 - yTemp3);
                            yColor = yTempColor3 + (yTempColor2 - yTempColor3) * l / abs(yTemp2 - yTemp3);
                            zColor = zTempColor3 + (zTempColor2 - zTempColor3) * l / abs(yTemp2 - yTemp3);
                        }
                        polyhedraGlobalYZ[i].setx(-1, xColor);
                        polyhedraGlobalYZ[i].sety(yLeft + l, yColor);
                        polyhedraGlobalYZ[i].setz(zAll, zColor);
//                        cout << "xcolor: " << xColor << ", ycolor: " << yColor << ", zcolor: " << zColor << endl;
                    }
                }

                if(yTemp2 == -1 && yTemp1 != -1 && yTemp3 != -1){
//                    cout<< "here" << endl;
                    for(int l = 1; l < int(abs(yTemp1 - yTemp3)); ++l){
//                        cout << "ytemp1: " << yTemp1 << ", ytemp2: " << yTemp2 << ", ytemp3: " << yTemp3 << endl;
//                        cout << "dely: " <<abs(yTemp1 - yTemp3) << endl;
                        //FIyME: edges not fillin
                        yLeft = min(yTemp1, yTemp3);
                        yRight = max(yTemp1, yTemp3);
                        if(yTemp1 <= yTemp3){
                            yLeft = yTemp1;
                            yRight = yTemp3;
                            xColor = xTempColor1 + (xTempColor3 - xTempColor1) * l / abs(yTemp1 - yTemp3);
                            yColor = yTempColor1 + (yTempColor3 - yTempColor1) * l / abs(yTemp1 - yTemp3);
                            zColor = zTempColor1 + (zTempColor3 - zTempColor1) * l / abs(yTemp1 - yTemp3);
                        } else {
                            yLeft = yTemp3;
                            yRight = yTemp1;
                            xColor = xTempColor3 + (xTempColor1 - xTempColor3) * l / abs(yTemp1 - yTemp3);
                            yColor = yTempColor3 + (yTempColor1 - yTempColor3) * l / abs(yTemp1 - yTemp3);
                            zColor = zTempColor3 + (zTempColor1 - zTempColor3) * l / abs(yTemp1 - yTemp3);
                        }
                        polyhedraGlobalYZ[i].setx(-1, xColor);
                        polyhedraGlobalYZ[i].sety(yLeft + l, yColor);
                        polyhedraGlobalYZ[i].setz(zAll, zColor);
                    }
                }

                if(yTemp3 == -1 && yTemp1 != -1 && yTemp2 != -1){
//                    cout<< "here" << endl;
                    for(int l = 1; l < int(abs(yTemp2 - yTemp1)); ++l){
//                        cout << "ytemp1: " << yTemp2 << ", ytemp3: " << yTemp3 << endl;
//                        cout << "dely: " <<abs(yTemp2 - yTemp3) << endl;
                        //FIXME: edges not fillin
                        yLeft = min(yTemp2, yTemp1);
                        yRight = max(yTemp2, yTemp1);

                        if(yTemp1 <= yTemp2){
                            yLeft = yTemp1;
                            yRight = yTemp2;
                            xColor = xTempColor1 + (xTempColor2 - xTempColor1) * l / abs(yTemp1 - yTemp2);
                            yColor = yTempColor1 + (yTempColor2 - yTempColor1) * l / abs(yTemp1 - yTemp2);
                            zColor = zTempColor1 + (zTempColor2 - zTempColor1) * l / abs(yTemp1 - yTemp2);
                        } else {
                            yLeft = yTemp2;
                            yRight = yTemp1;
                            xColor = xTempColor2 + (xTempColor1 - xTempColor2) * l / abs(yTemp1 - yTemp2);
                            yColor = yTempColor2 + (yTempColor1 - yTempColor2) * l / abs(yTemp1 - yTemp2);
                            zColor = zTempColor2 + (zTempColor1 - zTempColor2) * l / abs(yTemp1 - yTemp2);
                        }
                        polyhedraGlobalYZ[i].setx(-1, xColor);
                        polyhedraGlobalYZ[i].sety(yLeft + l, yColor);
                        polyhedraGlobalYZ[i].setz(zAll, zColor);
                    }

                }

                // temp2 and temp3 share point c
                if(yTemp2 == yTemp3 && yTemp1 != -1 ){
//                    if(j == 10){
//                        cout << "j: " << j + 1 << endl;
//                        cout << "yAll: " << yAll << endl;
//                        cout << "xtemp1: " << xTemp1 << ", xtemp2: " << xTemp2 <<", xtemp3: " << xTemp3 << endl;
                    xTempColor3 = polyhedraGlobalYZ[i].getxColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
                    yTempColor3 = polyhedraGlobalYZ[i].getyColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
                    zTempColor3 = polyhedraGlobalYZ[i].getzColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
                    for(int l = 0; l < int(abs(yc - yTemp1)); ++l){
//                            cout << "xtemp1: " << xTemp1 << ", xc: " << xc << endl;
//                        cout << "delx: " <<abs(xTemp2 - xTemp1) << endl;
                        //FIXME: edges not fillin
                        yLeft = min(yc, yTemp1);
                        yRight = max(yc, yTemp1);

                        if(yTemp1 <= yc){
                            yLeft = yTemp1;
                            yRight = yc;
                            xColor = xTempColor1 + (xTempColor3 - xTempColor1) * l / abs(yTemp1 - yc);
                            yColor = yTempColor1 + (yTempColor3 - yTempColor1) * l / abs(yTemp1 - yc);
                            zColor = zTempColor1 + (zTempColor3 - zTempColor1) * l / abs(yTemp1 - yc);
                        } else {
                            yLeft = yc;
                            yRight = yTemp1;
                            xColor = xTempColor3 + (xTempColor1 - xTempColor3) * l / abs(yTemp1 - yc);
                            yColor = yTempColor3 + (yTempColor1 - yTempColor3) * l / abs(yTemp1 - yc);
                            zColor = zTempColor3 + (zTempColor1 - zTempColor3) * l / abs(yTemp1 - yc);
                        }
                        polyhedraGlobalYZ[i].setx(-1, xColor);
                        polyhedraGlobalYZ[i].sety(yLeft + l, yColor);
                        polyhedraGlobalYZ[i].setz(zAll, zColor);
                    }

                }

                // temp1 and temp3 share point b
                if(yTemp1 == yTemp3 && yTemp2 != -1 ){
//                    if(j == 10){
//                        cout << "j: " << j + 1 << endl;
//                        cout << "yAll: " << yAll << endl;
//                        cout << "ytemp1: " << yTemp1 << ", ytemp2: " << yTemp2 <<", ytemp3: " << yTemp3 << endl;
                    xTempColor3 = polyhedraGlobalYZ[i].getxColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
                    yTempColor3 = polyhedraGlobalYZ[i].getyColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
                    zTempColor3 = polyhedraGlobalYZ[i].getzColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
                    for(int l = 0; l < int(abs(yb - yTemp2)); ++l){
//                            cout << "ytemp1: " << yTemp1 << ", yc: " << yc << endl;
//                        cout << "dely: " <<abs(yTemp2 - yTemp1) << endl;
                        //FIXME: edges not fillin
                        yLeft = min(yb, yTemp2);
                        yRight = max(yb, yTemp2);

                        if(yTemp2 <= yb){
                            yLeft = yTemp2;
                            yRight = yb;
                            xColor = xTempColor2 + (xTempColor3 - xTempColor2) * l / abs(yb - yTemp2);
                            yColor = yTempColor2 + (yTempColor3 - yTempColor2) * l / abs(yb - yTemp2);
                            zColor = zTempColor2 + (zTempColor3 - zTempColor2) * l / abs(yb - yTemp2);
                        } else {
                            yLeft = yb;
                            yRight = yTemp2;
                            xColor = xTempColor3 + (xTempColor2 - xTempColor3) * l / abs(yb - yTemp2);
                            yColor = yTempColor3 + (yTempColor2 - yTempColor3) * l / abs(yb - yTemp2);
                            zColor = zTempColor3 + (zTempColor2 - zTempColor3) * l / abs(yb - yTemp2);
                        }
                        polyhedraGlobalYZ[i].setx(-1, xColor);
                        polyhedraGlobalYZ[i].sety(yLeft + l, yColor);
                        polyhedraGlobalYZ[i].setz(zAll, zColor);
                    }

                }

                // temp1 and temp2 share point a
                if(yTemp1 == yTemp2 && yTemp3 != -1 ){
//                    if(j == 10){
//                        cout << "j: " << j + 1 << endl;
//                        cout << "yAll: " << yAll << endl;
//                        cout << "ytemp1: " << yTemp1 << ", ytemp2: " << yTemp2 <<", ytemp3: " << yTemp3 << endl;
                    xTempColor2 = polyhedraGlobalYZ[i].getxColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
                    yTempColor2 = polyhedraGlobalYZ[i].getyColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
                    zTempColor2 = polyhedraGlobalYZ[i].getzColor(polyhedraGlobalYZ[i].getCFace(j) - 1);
                    for(int l = 0; l < int(abs(ya - yTemp3)); ++l){
//                            cout << "ytemp1: " << yTemp1 << ", yc: " << yc << endl;
//                        cout << "dely: " <<abs(yTemp2 - yTemp1) << endl;
                        //FIXME: edges not fillin
                        yLeft = min(ya, yTemp3);
                        yRight = max(ya, yTemp3);

                        if(ya <= yTemp3){
                            yLeft = ya;
                            yRight = yTemp3;
                            xColor = xTempColor2 + (xTempColor3 - xTempColor2) * l / abs(ya - yTemp3);
                            yColor = yTempColor2 + (yTempColor3 - yTempColor2) * l / abs(ya - yTemp3);
                            zColor = zTempColor2 + (zTempColor3 - zTempColor2) * l / abs(ya - yTemp3);
                        } else {
                            yLeft = yTemp3;
                            yRight = ya;
                            xColor = xTempColor3 + (xTempColor2 - xTempColor3) * l / abs(ya - yTemp3);
                            yColor = yTempColor3 + (yTempColor2 - yTempColor3) * l / abs(ya - yTemp3);
                            zColor = zTempColor3 + (zTempColor2 - zTempColor3) * l / abs(ya - yTemp3);
                        }
                        polyhedraGlobalYZ[i].setx(-1, xColor);
                        polyhedraGlobalYZ[i].sety(yLeft + l, yColor);
                        polyhedraGlobalYZ[i].setz(zAll, zColor);
                    }

                }




            }
        }
    }
}

char userInput;
void PhongModel(){
    cout << "Do you want to apply phong model? (y/n)" << endl;
    cin >> userInput;
    if(userInput == 'N' || userInput == 'n'){
        return;
    } else if (userInput == 'Y' || userInput == 'y'){
        cout << "Now phong model." << endl;
    }

    CalculateNVector();
    double kaIa, Il, K, fa, fb, fc, ksx, ksy, ksz, xCoor, yCoor, zCoor, lx, ly, lz;
//    double ;
    double ks[3], f[3], l[3];
    cout << "Attention: all variables including f, ks, and l are recommended between 0-1 except for K." << endl;
    cout << "Type kaIa(one constant), Il, K " << endl;
    cin >> kaIa >> Il >> K;
    cout << "Type f(fx, fy, and fz), ks(ksRed, ksGreen, and ksBlue), l(lx, ly, lz)" << endl;
    cin >> fa >> fb >> fc >> ksx >> ksy >> ksz >> lx >> ly >> lz;


//    if(file == "bunny.txt"){
//        f[0] = fa * factorBegining * shapeFactor - transX;
//        f[1] = fb * factorBegining * shapeFactor - transY;
//        f[2] = fc * factorBegining * shapeFactor - transZ;
//        l[0] = lx * factorBegining * shapeFactor - transX;
//        l[1] = ly * factorBegining * shapeFactor - transY;
//        l[2] = lz * factorBegining * shapeFactor - transZ;
//    }else{
//        f[0] = fa * factorBegining;
//        f[1] = fb * factorBegining;
//        f[2] = fc * factorBegining;
//        l[0] = lx * factorBegining;
//        l[1] = ly * factorBegining;
//        l[2] = lz * factorBegining;
//    }
    ks[0] = ksx;
    ks[1] = ksy;
    ks[2] = ksz;

//    cout << "f[0]: " << f[0] << ", f[1]: " << f[1] << ", f[2]: " << f[2] << endl;
//    cout << "ks[0]: " << ks[0] << ", ks[1]: " << ks[1] << ", ks[2]: " << ks[2] << endl;
//    cout << "l[0]: " << l[0] << ", l[1]: " << l[1] << ", l[2]: " << l[2] << endl;



    double Ip[3], kd[3], p[3], lVec[3], v[3], r[3], fMinp, lAndn, rAndv, temp1, temp2, temp3;
    int nn;


    //x.  y and z later
    for(int i = 0; i < polyhedraGlobal.size(); ++i){
        for(int j = 0; j < polyhedraGlobal[i].getNumSides(); ++j) {
//            cout << "color: " << polyhedraGlobal[i].getxColor(j) << " "
//            << polyhedraGlobal[i].getyColor(j) << " " << polyhedraGlobal[i].getzColor(j) << endl;

            kd[0] = polyhedraGlobal[i].getxColor(j);
            kd[1] = polyhedraGlobal[i].getyColor(j);
            kd[2] = polyhedraGlobal[i].getzColor(j);
            p[0] = polyhedraGlobal[i].getxCoor(j);
            p[1] = polyhedraGlobal[i].getyCoor(j);
            p[2] = polyhedraGlobal[i].getzCoor(j);
            nn = polyhedraGlobal[i].getSpecularity(j);

            lVec[0] = l[0] - p[0];
            lVec[1] = l[1] - p[1];
            lVec[2] = l[2] - p[2];
            temp1 = max(lVec[0], lVec[1]);
            temp2 = max(lVec[1], lVec[2]);
            temp3 = max(temp1, temp2);

            lVec[0] = lVec[0] / temp3;
            lVec[1] = lVec[1] / temp3;
            lVec[2] = lVec[2] / temp3;

            if(file == "bunny.txt"){
                p[0] = (p[0] + transX) / shapeFactor / factorBegining;
                p[1] = (p[1] + transX) / shapeFactor / factorBegining;
                p[2] = (p[2] + transX) / shapeFactor / factorBegining;
            } else {
                p[0] = p[0] / factorBegining;
                p[1] = p[1] / factorBegining;
                p[2] = p[2] / factorBegining;
            }

//            cout << "kd[0]: " << kd[0] << ", kd[1]: " << kd[1] << ", kd[2]: " << kd[2] << endl;
//            cout << "p[0]: " << p[0] << ", p[1]: " << p[1] << ", p[2]: " << p[2] << endl;
////            cout << "p[0]" << p[0] << "p[1]" << p[1] << "p[2]" << p[2] << endl;
//            cout << "lVec[0]: " << lVec[0] << ", lVec[1]: " << lVec[1] << ", lVec[2]: " << lVec[2] << endl;



            fMinp = sqrt((f[0] - p[0]) * (f[0] - p[0]) +
                    (f[1] - p[1]) * (f[1] - p[1]) + (f[2] - p[2]) * (f[2] - p[2]));

//            cout << "fMinp: " << fMinp << endl;
            //FIXME: i > 0
            if(i == 0){
                lAndn = lVec[0] * niFinal[j] + lVec[1] * njFinal[j] + lVec[2] * nkFinal[j];
            } else {
                lAndn = lVec[0] * niFinal[j + i * polyhedraGlobal[i - 1].getNumFaces()]
                        + lVec[1] * njFinal[j + i * polyhedraGlobal[i - 1].getNumFaces()]
                        + lVec[2] * nkFinal[j + i * polyhedraGlobal[i - 1].getNumFaces()];
            }

//            cout << "lVec: " << lAndn << endl;

            v[0] = f[0] - p[0];
            v[1] = f[1] - p[1];
            v[2] = f[2] - p[2];
            temp1 = max(v[0], v[1]);
            temp2 = max(v[2], v[1]);
            temp3 = max(temp1, temp2);

            v[0] = v[0] / temp3;
            v[1] = v[1] / temp3;
            v[2] = v[2] / temp3;

            if(i == 0){
                r[0] = -lVec[0] + 2*lAndn * sqrt(niFinal[j] * niFinal[j]
                        + njFinal[j] * njFinal[j] + nkFinal[j] * nkFinal[j]);
                r[1] = -lVec[1] + 2*lAndn * sqrt(niFinal[j] * niFinal[j]
                        + njFinal[j] * njFinal[j] + nkFinal[j] * nkFinal[j]);
                r[2] = -lVec[2] + 2*lAndn * sqrt(niFinal[j] * niFinal[j]
                        + njFinal[j] * njFinal[j] + nkFinal[j] * nkFinal[j]);

            } else{
                temp1 = niFinal[j + i * polyhedraGlobal[i - 1].getNumFaces()];
                temp2 = njFinal[j + i * polyhedraGlobal[i - 1].getNumFaces()];
                temp3 = nkFinal[j + i * polyhedraGlobal[i - 1].getNumFaces()];

                r[0] = -lVec[0] + 2 * lAndn * sqrt(temp1 * temp1 + temp2 * temp2 + temp3 * temp3);
                r[1] = -lVec[1] + 2 * lAndn * sqrt(temp1 * temp1 + temp2 * temp2 + temp3 * temp3);
                r[2] = -lVec[2] + 2 * lAndn * sqrt(temp1 * temp1 + temp2 * temp2 + temp3 * temp3);

            }

            temp1 = max(r[0], r[1]);
            temp2 = max(r[2], r[1]);
            temp3 = max(temp1, temp2);

            r[0] = r[0] / temp3;
            r[1] = r[1] / temp3;
            r[2] = r[2] / temp3;

            rAndv = r[0] * v[0] + r[1] * v[1] + r[2] * r[2];

            //****************************************
            Ip[0] = kaIa + Il/(fMinp + K) *(kd[0] * lAndn + ks[0] * pow(rAndv, nn));
            Ip[1] = kaIa + Il/(fMinp + K) *(kd[1] * lAndn + ks[1] * pow(rAndv, nn));
            Ip[2] = kaIa + Il/(fMinp + K) *(kd[2] * lAndn + ks[2] * pow(rAndv, nn));

            temp1 = max(Ip[0], Ip[1]);
            temp2 = max(Ip[1], Ip[2]);
            temp3 = max(temp1, temp2);

//            Ip[0] = Ip[0] / temp3;
//            Ip[1] = Ip[1] / temp3;
//            Ip[2] = Ip[2] / temp3;


//            cout << "ip[0]: " << Ip[0] << ", ip[1]: " << Ip[1] << ", ip[2]: " << Ip[2] << endl;
            polyhedraGlobal[i].replacexColor(j, Ip[0]);
            polyhedraGlobal[i].replaceyColor(j, Ip[1]);
            polyhedraGlobal[i].replaceyColor(j, Ip[2]);


        }
    }




//    for(int i = 0; i < niFinal.size(); ++i) {
//        cout << niFinal[i] << " " << njFinal[i] << " " << nkFinal[i] << endl;
//    }
    //need calculate the Ip 3 times by x, y, z



}

void CalculateNVector(){
    //n faces, n points
    double x1, y1, z1, x2, y2, z2, x3, y3, z3, delx2x1, dely2y1, delz2z1,
            delx3x1, dely3y1, delz3z1, xa, xb, xc, ya, yb, yc, za, zb, zc, ni, nj, nk;
    vector<pair<int, double>> nii, njj, nkk;

    //FIXME:: consider size > 1
    for (int i = 0; i < polyhedraGlobal.size(); ++i) {
        for (int j = 0; j < polyhedraGlobal[i].getNumFaces(); ++j) {
            xa = polyhedraGlobal[i].getxCoor(polyhedraGlobal[i].getAFace(j) - 1);
            xb = polyhedraGlobal[i].getxCoor(polyhedraGlobal[i].getBFace(j) - 1);
            xc = polyhedraGlobal[i].getxCoor(polyhedraGlobal[i].getCFace(j) - 1);
            ya = polyhedraGlobal[i].getyCoor(polyhedraGlobal[i].getAFace(j) - 1);
            yb = polyhedraGlobal[i].getyCoor(polyhedraGlobal[i].getBFace(j) - 1);
            yc = polyhedraGlobal[i].getyCoor(polyhedraGlobal[i].getCFace(j) - 1);
            za = polyhedraGlobal[i].getzCoor(polyhedraGlobal[i].getAFace(j) - 1);
            zb = polyhedraGlobal[i].getzCoor(polyhedraGlobal[i].getBFace(j) - 1);
            zc = polyhedraGlobal[i].getzCoor(polyhedraGlobal[i].getCFace(j) - 1);

//            cout << "face " << j + 1 << endl;
//            cout << "xa: " << xa << ", xb: " << xb << ", xc: " << xc <<endl;

            x1 = xb - xa;
            x2 = xc - xa;
            y1 = yb - ya;
            y2 = yc - ya;
            z1 = zb - za;
            z2 = zc - za;
            ni = y1 * z2 - y2 * z1;
            nj = -(x1 * z2 - x2 * z1);
            nk = x1 * y2 - x2 * y1;



            nii.push_back(make_pair(polyhedraGlobal[i].getAFace(j) - 1, ni));
            njj.push_back(make_pair(polyhedraGlobal[i].getBFace(j) - 1, nj));
            nkk.push_back(make_pair(polyhedraGlobal[i].getCFace(j) - 1, nk));

//            cout << "Aface: " << polyhedraGlobal[i].getAFace(j) <<
//            "Bface: " << polyhedraGlobal[i].getBFace(j) << "Cface: "
//            << polyhedraGlobal[i].getCFace(j) << endl;
//            cout << "na: " << na << ", nb: " << nb << ", nc: " << nc << endl;
        }
    }

    for (int i = 0; i < nii.size(); ++i) {
//        cout << "index[" << i << "]: " << "first: " <<
//        nii[i].first + 1 << ", second: " << nii[i].second << endl;
    }

    double count = 0;
    double sumii = 0;
    double sumjj = 0;
    double sumkk = 0;
    int indexx = -1;
    double tempi = 0;
    double tempj = 0;
    double tempk = 0;
    double temp1, temp2, temp3;

    for(int i = 0; i < polyhedraGlobal.size(); ++i) {
        for (int j = 0; j < polyhedraGlobal[i].getNumSides(); ++j) {
            count = 0;
            sumii = 0;
            sumjj = 0;
            sumkk = 0;
            indexx ++;
            for(int k = 0; k < polyhedraGlobal[i].getNumFaces();++k){
                if(i == 0){
                    if((j == nii[k].first)){
//                        cout << "j: " << j + 1 << ", k: " << k + 1 << endl;
                        sumii += nii[k].second;
                        sumjj += njj[k].second;
                        sumkk += nkk[k].second;
                        count++;
//                        cout << "sum: " << sum << ", count: " << count << endl;

                    }
                    if((j == njj[k].first)){
//                        cout << "j: " << j + 1 << ", k: " << k + 1 << endl;
                        sumii += nii[k].second;
                        sumjj += njj[k].second;
                        sumkk += nkk[k].second;
                        count++;
//                        cout << "sum: " << sum << ", count: " << count << endl;

                    }
                    if((j == nkk[k].first)){
//                        cout << "j: " << j + 1 << ", k: " << k + 1 << endl;
                        sumii += nii[k].second;
                        sumjj += njj[k].second;
                        sumkk += nkk[k].second;
                        count++;
//                        cout << "sum: " << sum << ", count: " << count << endl;

                    }

                } else {
                    if(j == nii[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].first){
//                        cout << "j: " << j + 1 << ", k: " << k + 1 << ", second: "
//                             << naa[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second << endl;
                        sumii += nii[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second;
                        sumjj += njj[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second;
                        sumkk += nkk[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second;
                        count++;
//                        cout << "sum: " << sum << ", count: " << count << endl;

                    }
                    if(j == njj[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].first){
//                        cout << "j: " << j + 1 << ", k: " << k + 1 << ", second: "
//                             << naa[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second << endl;
                        sumii += nii[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second;
                        sumjj += njj[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second;
                        sumkk += nkk[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second;
                        count++;
//                        cout << "sum: " << sum << ", count: " << count << endl;

                    }
                    if(j == nkk[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].first){
//                        cout << "j: " << j + 1 << ", k: " << k + 1 << ", second: "
//                             << naa[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second << endl;
                        sumii += nii[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second;
                        sumjj += njj[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second;
                        sumkk += nkk[k + (i) * polyhedraGlobal[i - 1].getNumFaces()].second;
                        count++;
//                        cout << "sum: " << sum << ", count: " << count << endl;

                    }

                }
//                cout << "sum: " << sum << ", count: " << count << endl;

            }
//            cout << "j: " << j + 1 << endl;
//            cout << "sumii: " << sumii << "sumjj: " << sumjj << "sumkk: " << sumkk << ", count: " << count << endl;
            tempi = sumii / count;
            tempj = sumjj / count;
            tempk = sumkk / count;
//            cout << "temp: " << temp << endl;
            //FIXME: temp
//            cout << "temp: " << temp << endl;
//            cout << endl;
            temp1 = max(abs(tempi), abs(tempj));
            temp2 = max(abs(tempj), abs(tempk));
            temp3 = max(temp1, temp2);

            tempi = tempi / temp3;
            tempj = tempj / temp3;
            tempk = tempk / temp3;

            niFinal.push_back(tempi);
            njFinal.push_back(tempj);
            nkFinal.push_back(tempk);
//            cout << "tempi: " << tempi << ", tempj: " << tempj << ", tempk: " << tempk << endl;
        }
    }



}




void HalfTone(){

}