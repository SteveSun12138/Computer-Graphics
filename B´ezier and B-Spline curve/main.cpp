
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
#include <vector>
#include <math.h>

using namespace std;

class Point{
public:
    double getX() const {
        return x;
    }

    void setX(double x) {
        Point::x = x;
    }

    double getY() const {
        return y;
    }

    void setY(double y) {
        Point::y = y;

    }

    void setXY(double a, double b){
        x = a;
        y = b;
    }

private:
    double x, y;
};

typedef struct{
    double x;
    double y;
}PointStr;

/****set in main()****/

int grid_width;
int grid_height;
double xtemp, ytemp;
int userChoice;
bool choice;
int indexchange;
bool clickOrNot = false;
bool change = false;
vector<Point> points;
vector<Point> curve;
vector<PointStr> pointStr;
vector<PointStr> bezierStr;
vector<PointStr> splineStr;
vector<PointStr> empty;
vector< vector<PointStr> > PPPoint;
vector< vector<PointStr> > BBBezier;
vector< vector<PointStr> > SSSpline;
double t, size;
double xNew, yNew;

//the size of pixels sets the inital window height and width
//don't make the pixels too large or the screen size will be larger than
//your display size
float pixel_size;

/*Window information*/
int win_height;
int win_width;


void init();
void idle();
void display();
void draw_pix(int x, int y);
void draw_pix_point(int x, int y);
void reshape(int width, int height);
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void check();
void setSize();
void Bezier();
void LineFilling();
void InitialSetting();
void draw_pix(int x, int y);
void SetMousePoint(double a, double b);
void Spline(double aaa);
void SetDeBoorVariables();
void ChangePoint();
double GetXNew();
double GetYNew();
void NewPoint();



int main(int argc, char **argv)
{
    setSize();
    InitialSetting();
    cout << "Choose which algorithm you want to use: (1)Bezier  (2)B-Spline." << endl;
    cin >> userChoice;
    while(userChoice != 1 && userChoice != 2){
        cout << "Wrong input. Please type 1 or 2." << endl;
        cin >> userChoice;
    }
    if(userChoice == 1){

    }else if(userChoice == 2){
        SetDeBoorVariables();
    }
    cout << "To modify any point, type 't' on screen. Then follow the command line instruction." << endl;
    cout << "To add a new line, type 'n' on screen." << endl;
    cout << endl;

    win_height = grid_height*pixel_size;
    win_width = grid_width*pixel_size;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(win_width,win_height);
    //windown title is "glut demo"
    glutCreateWindow("glut demo");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape); //update GL on window size change
    glutMouseFunc(mouse);     //mouse button events


    glutMotionFunc(motion);   //mouse movement events
    glutKeyboardFunc(key);    //Keyboard events
    glutIdleFunc(idle);       //Function called while program is sitting "idle"

    init();
    glutMainLoop();

    return 0;
}

void setSize(){
    grid_width = 600;
    grid_height = 600;
    pixel_size = 1;
}

void InitialSetting(){
    cout << "Set up the display resolution. (Recommend 1000)" << endl;
    cin >> size;

}

void init()
{
    //set clear color (Default background to white)
    glClearColor(0,0,0,1.0);
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
void display()
{
    //clears the screen
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    //clears the opengl Modelview transformation matrix
    glLoadIdentity();

    LineFilling();

    //blits the current opengl framebuffer on the screen
    glutSwapBuffers();
    //checks for opengl errors
    check();
}
void draw_pix_point(int x, int y){
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex3f(x+.5,y+.5,0);
    glVertex3f(x+.5 - 1,y+.5 + 2,0);
    glVertex3f(x+.5,y+.5 + 2,0);
    glVertex3f(x+.5 + 1,y+.5 + 2,0);
    glVertex3f(x+.5 - 2,y+.5 + 1,0);
    glVertex3f(x+.5 - 2,y+.5,0);
    glVertex3f(x+.5 - 2,y+.5 - 1,0);
    glVertex3f(x+.5 + 2,y+.5 + 1,0);
    glVertex3f(x+.5 + 2,y+.5,0);
    glVertex3f(x+.5 + 2,y+.5 - 1,0);
    glVertex3f(x+.5 - 1,y+.5 - 2,0);
    glVertex3f(x+.5,y+.5 - 2,0);
    glVertex3f(x+.5 + 1,y+.5 - 2,0);
    glVertex3f(x+.5 - 1,y+.5 + 1,0);
    glVertex3f(x+.5,y+.5 + 1,0);
    glVertex3f(x+.5+1,y+.5 + 1,0);
    glVertex3f(x+.5 - 1,y+.5,0);
    glVertex3f(x+.5 + 1,y+.5,0);
    glVertex3f(x+.5 - 1,y+.5 - 1,0);
    glVertex3f(x+.5,y+.5 -1,0);
    glVertex3f(x+.5 +1,y+.5 -1,0);
    glEnd();
}
void draw_pix(int x, int y){
    glBegin(GL_POINTS);
    glColor3f(.2,.2,1.0);
    glVertex3f(x+.5,y+.5,0);
    glEnd();
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
    switch(ch)
    {
        case 'e':
            exit(1);
            break;
        case 't':
            change = true;
            ChangePoint();
            break;
        case 'n':
            NewPoint();
            break;

        default:
            //prints out which key the user hit
//            printf("User hit the \"%c\" key\n",ch);
            break;
    }
    //redraw the scene after keyboard input
    glutPostRedisplay();
}

void NewPoint(){
//    PPPoint.push_back(pointStr);
//    BBBezier.push_back(bezierStr);
//    SSSpline.push_back(splineStr);
    pointStr.clear();
//    bezierStr.clear();
//    splineStr.clear();
}

int indexChanged;
char userInp;
void ChangePoint(){
    cout << "Type the index you want to modify. (begin from 0)" << endl;
    cin >> indexChanged;
    while(indexChanged < 0 || indexChanged > pointStr.size()){
        cout << "wrong index typed. Please type again. " << endl;
        cin >> indexChanged;
    }
    cout << "'d'--delete this point  'm'--move to another point." << endl;
    cin >> userInp;
//    pointStr.clear();
    if(userInp == 'd'){
//        PPPoint[PPPoint.size() - 1].erase(PPPoint[PPPoint.size() - 1].begin() + indexChanged);
        pointStr.erase(pointStr.begin() + indexChanged);
    }
    if(userInp == 'm'){
        cout << "type the coordinates of the new point (x and y) (0 to 600)" << endl;
        cin >> xNew >> yNew;
//        PPPoint[PPPoint.size() - 1][indexChanged].x = xNew;
//        PPPoint[PPPoint.size() - 1][indexChanged].y = yNew;
        pointStr[indexChanged].x = xNew;
        pointStr[indexChanged].y = yNew;
    }
}

double GetXNew(){

}
double GetYNew(){ }

void mouse(int button, int state, int x, int y)
{
    //print the pixel location, and the grid location
    //printf ("MOUSE AT PIXEL: %d %d, GRID: %d %d\n",x,y,(int)(x/pixel_size),(int)((win_height-y)/pixel_size));
     xtemp = (x/pixel_size);
     ytemp = ((win_height-y)/pixel_size);
    //cout << "x: " <<  xtemp << ", y: " << ytemp << endl;
//    cout << "state: " << state << endl;

//    if(button == GLUT_LEFT_BUTTON){
//        cout << "hh" << endl;
//    }

    switch(button)
    {
        case GLUT_LEFT_BUTTON: //left button
            //printf("LEFT ");
            SetMousePoint(xtemp, ytemp);
            break;
        case GLUT_RIGHT_BUTTON: //right button
            printf("RIGHT ");
        default:
            printf("UNKNOWN "); //any other mouse button
            break;
    }
//    if(state !=GLUT_DOWN)  //button released
//        printf("BUTTON UP\n");
//    else
//        printf("BUTTON DOWN\n");  //button clicked

    //redraw the scene after mouse click
    //cout <<"size: " << points.size() << endl;

    glutPostRedisplay();
//    Bezier();
}

void motion(int x, int y)
{
//    cout << "motion x: " << x << ", y: " << y << endl;
//    double delx, dely;
//    if(change == true){
//        cout << "now true" << endl;
//    }
//
//    if(clickOrNot == true){
//        cout << "click true. " << endl;
//    } else {
//        cout << "click false. " << endl;
//    }

//    int indexChange;
//    bool state = false;
//    cout << "index change: " << indexchange << endl;
//    //redraw the scene after mouse movement
//    for(int i = 0; i < points.size(); ++i){
//        delx = points[i].getX() - double(x);
//        dely = points[i].getY() - double(y);
//        if (abs(delx) < 10 && abs(dely) < 10){
//            cout << "true" << endl;
//            state = true;
//            indexChange = i;
//            break;
//        }
//    }
//    if(state == true){
//        points[indexChange].setX(x);
//        points[indexChange].setY(y);
//    }


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

char userInput;
double input1, input2;

int NI(int n, int i){
    int nFac = 1;
    int iFac = 1;
    int nMiniFac = 1;
    int result;
    for(int j = n; j > 0; --j){
        nFac = nFac * j;
    }
    for (int k = i; k > 0; --k) {
        iFac = iFac * k;
    }
    for(int j = n - i; j > 0; --j){
        nMiniFac = nMiniFac * j;
    }
    result = nFac / (iFac * nMiniFac);
    return result;
}


void SetMousePoint(double a, double b){
    Point point;
    PointStr pointstr1;


    int sizeTemp = pointStr.size();
//    pointStr.size();
    if(pointStr.size() == 0){
//        point.setXY(a, b);
//        points.push_back(point);
        pointstr1.x = a;
        pointstr1.y = b;
        pointStr.push_back(pointstr1);
    }
//    if(pointStr.size() == 2){
//        if(points[0].getX() == points[1].getX() && points[0].getY() == points[1].getY()){
//            points.erase(points.begin() + 1);
//        }
//    }
    if(pointStr.size() == 2){
        if(pointStr[0].x == pointStr[1].x && pointStr[0].y == pointStr[1].y){
            pointStr.erase(pointStr.begin() + 1);
        }
    }
    double delx, dely;
    bool inState = false;
    if(pointStr.size() != 0){
        if(a != pointStr[sizeTemp - 1].x){
            for(int i = 0; i < pointStr.size(); ++i){
                delx = a - pointStr[i].x;
                dely = b - pointStr[i].y;
//                cout << "delx: " << abs(delx) << ", dely: " << abs(dely) << endl;
                if (abs(delx) < 10 && abs(dely) < 10){
//
//                    clickOrNot = true;
//                    inState = true;
                    indexchange = i;
                    break;
                } else {
                    //clickOrNot == false;
//                    point.setXY(a, b);
//                    points.push_back(point);
                }
            }
            if(!inState){
//                point.setXY(a, b);
//                points.push_back(point);
                pointstr1.x = a;
                pointstr1.y = b;
                pointStr.push_back(pointstr1);
            }
//            if(!clickOrNot){
//                point.setXY(a, b);
//                points.push_back(point);
//            }
//            if(clickOrNot == false){
//                //cout << "here." << endl;
//                point.setXY(a, b);
//                points.push_back(point);
//            }



        }



    }

//    cout << "point size: " << sizeTemp << endl;
    return;
}



//void Spline(){
////    curve.clear();
////    int k = 3;
////    int n = points.size() - 1;
////    int m = n + k + 1;
////    int I = 0;
////    double t[m];
////    Point d[n + 1];
////    for(int a = 0; a < n + 1; ++a){
////        d[a].setXY(points[a].getX(), points[a].getY());
////    }
////    //FIXME: initialize t. Change 0 to others
////    for (int a = 0; a < m + 1; ++a) {
////        t[a] = a;
////    }
////    NN N[k][n +1];
//
//
//}

void Bezier(){
    PointStr pointstr1;
    double delt = 1 / size;
    double tempt = 0;

//    int n = points.size() - 1;
    int n = pointStr.size() - 1;
    double tempx;
    double tempy;
//    cout << "in here" << endl;
//    cout << "n: " << n << endl;
    if(n > 0) {
//        cout << "hhhhh" <<endl;
        while(tempt < 1){
//
            tempx = 0;
            tempy = 0;

            for(int i = 0; i < n + 1; ++i){
                tempx += double(pointStr[i].x) * double(NI(n, i)) * double(pow(1 - tempt, n - i)) * double(pow(tempt, i));
                tempy += double(pointStr[i].y) * double(NI(n, i)) * double(pow(1 - tempt, n - i)) * double(pow(tempt, i));
//                tempy += points[i].getY() * NI(n, i) * pow(1 - tempt, n - i) * pow(tempt, i);

            }
//            p.setXY(tempx, tempy);
//            curve.push_back(p);
            pointstr1.x = tempx;
            pointstr1.y = tempy;
//            cout << "str x: " << tempx << ", y: " << tempy << endl;
            bezierStr.push_back(pointstr1);
            tempt += delt;
        }
    }


//    cout << "enough points now. " << endl;
    return;
}

int k;
void SetDeBoorVariables(){
    cout << "type k value: " << endl;
    cin >> k;

}

void Spline(double aaa){
    //FIXME: for loop to add all points in it
//    curve.clear();

//    SetDeBoorVariables();
//    cout << "Deboor now" << endl;

//    Point p;
    //cout << "size: " << size << endl;
//    for(int i = 0; i < points.size(); ++i){
//        cout << "point[" << i << "]:  x: " << points[i].getX() << ", y: " << points[i].getY() << endl;
//    }
    double curT = 0.3;
    double tempt = 0;

    double del = 1 / size;
    int I = 0;

//    PointStr d[k + 1][n + 1];
//    PointStr pointstr1;
//    vector<double> T;
    if(pointStr.size() > 0){

        while(curT < 1){
            vector<double> T;
            int n = pointStr.size() - 1;
            PointStr d[k + 1][n + 1];
            PointStr pointstr1;

            for(int i = 0; i < k + pointStr.size(); ++i){
                T.push_back(1.0 / pointStr.size() * i);
            }
            for(int i = 0; i < pointStr.size(); ++i){
                d[0][i] = pointStr[i];
//                d[0][i].y = pointStr[i].y;
            }

            if(!(curT >= T[I] && curT <= T[I + 1])) {
                I++;
            }
//            double interval = 1 / (n + k);
//            double x1, x2;
//            for(int m = 0; m < n + k; ++m){
//                x1 = (m ) * interval;
//                x2 = (m + 1) * interval;
//                if(!(curT >= x1 && curT < x2)){
//                    I++;
//                }
//            }

            for (int j = 1; j <= k - 1; ++j) {
                for (int i = I - k + 1; i <= I - j; ++i) {
                    double alpha = (T[i + k] - curT) / (T[i + k] - T[i + j]);
                    d[j][i].x = alpha * d[j - 1][i].x + (1 - alpha) * d[j - 1][i + 1].x;
                    d[j][i].y = alpha * d[j - 1][i].y + (1 - alpha) * d[j - 1][i + 1].y;
                }
            }
            xtemp = d[k - 1][I - k + 1].x;
            ytemp = d[k - 1][I - k + 1].y;
//            p.setXY(xtemp, ytemp);
//            curve.push_back(p);
            pointstr1.x = xtemp;
            pointstr1.y = ytemp;
            splineStr.push_back(d[k-1][I - k + 1]);

            curT = curT + del;

        }

    }


}

void LineFilling(){
//    Bezier();

    bezierStr.clear();
    splineStr.clear();
    if(userChoice == 1){
        Bezier();
    } else if (userChoice == 2){
        double aaa = 0.2;
//        double del = 1 / size;
//        while(aaa < 1){
//            Spline(aaa);
//            aaa += del;
//        }
        Spline(aaa);
    }
    //int tempa = pointStr.size();
    int tempb, tempc;
//    PPPoint.erase(PPPoint.begin());
    PPPoint.clear();
    BBBezier.clear();
    SSSpline.clear();
    PPPoint.push_back(pointStr);
    BBBezier.push_back(bezierStr);
    SSSpline.push_back(splineStr);
    //cout << "now size: " << tempa << endl;
    //points
    for (int l = 0; l < PPPoint.size(); ++l) {
        int tempa = PPPoint[l].size();
//        cout << tempa;
        for (int i = 0; i < tempa; ++i) {
            draw_pix_point(PPPoint[l][i].x, PPPoint[l][i].y);
//            draw_pix_point(pointStr[i].x, pointStr[i].y);
        }
//        pointStr.clear();
//
    }

    // lines between points
    for (int m = 0; m < PPPoint.size(); ++m) {
        int tempa = PPPoint[m].size();
        for (int k = 0; k < tempa - 1; ++k) {
            glColor3f(.4, 0.2, 0.2);
            glBegin(GL_LINES);
            glVertex2f(PPPoint[m][k].x, PPPoint[m][k].y);
            glVertex2f(PPPoint[m][k + 1].x, PPPoint[m][k + 1].y);
            glEnd();
        }

    }

    //curves
    for (int m = 0; m < PPPoint.size(); ++m) {
        tempb = BBBezier[m].size();
        for (int j = 0; j < tempb; ++j) {
            draw_pix(BBBezier[m][j].x, BBBezier[m][j].y);
        }
        BBBezier[m].clear();
//        BBBezier.push_back(empty);
    }


    for (int m = 0; m < PPPoint.size(); ++m) {
        tempc = SSSpline[m].size();
        for (int j = 0; j < tempc; ++j) {
            draw_pix(SSSpline[m][j].x, SSSpline[m][j].y);
        }
        SSSpline[m].clear();
    }
//    splineStr.clear();

}
