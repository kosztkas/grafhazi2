//=============================================================================================
// Szamitogepes grafika hazi feladat keret. Ervenyes 2014-tol.          
// A //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sorokon beluli reszben celszeru garazdalkodni, mert a tobbit ugyis toroljuk. 
// A beadott program csak ebben a fajlban lehet, a fajl 1 byte-os ASCII karaktereket tartalmazhat. 
// Tilos:
// - mast "beincludolni", illetve mas konyvtarat hasznalni
// - faljmuveleteket vegezni (printf is fajlmuvelet!)
// - new operatort hivni az onInitialization függvényt kivéve, a lefoglalt adat korrekt felszabadítása nélkül 
// - felesleges programsorokat a beadott programban hagyni
// - tovabbi kommenteket a beadott programba irni a forrasmegjelolest kommentjeit kiveve
// ---------------------------------------------------------------------------------------------
// A feladatot ANSI C++ nyelvu forditoprogrammal ellenorizzuk, a Visual Studio-hoz kepesti elteresekrol
// es a leggyakoribb hibakrol (pl. ideiglenes objektumot nem lehet referencia tipusnak ertekul adni)
// a hazibeado portal ad egy osszefoglalot.
// ---------------------------------------------------------------------------------------------
// A feladatmegoldasokban csak olyan gl/glu/glut fuggvenyek hasznalhatok, amelyek
// 1. Az oran a feladatkiadasig elhangzottak ES (logikai AND muvelet)
// 2. Az alabbi listaban szerepelnek:  
// Rendering pass: glBegin, glVertex[2|3]f, glColor3f, glNormal3f, glTexCoord2f, glEnd, glDrawPixels
// Transzformaciok: glViewport, glMatrixMode, glLoadIdentity, glMultMatrixf, gluOrtho2D, 
// glTranslatef, glRotatef, glScalef, gluLookAt, gluPerspective, glPushMatrix, glPopMatrix,
// Illuminacio: glMaterialfv, glMaterialfv, glMaterialf, glLightfv
// Texturazas: glGenTextures, glBindTexture, glTexParameteri, glTexImage2D, glTexEnvi, 
// Pipeline vezerles: glShadeModel, glEnable/Disable a kovetkezokre:
// GL_LIGHTING, GL_NORMALIZE, GL_DEPTH_TEST, GL_CULL_FACE, GL_TEXTURE_2D, GL_BLEND, GL_LIGHT[0..7]
//
// NYILATKOZAT
// ---------------------------------------------------------------------------------------------
// Nev    :
// Neptun : 
// ---------------------------------------------------------------------------------------------
// ezennel kijelentem, hogy a feladatot magam keszitettem, es ha barmilyen segitseget igenybe vettem vagy 
// mas szellemi termeket felhasznaltam, akkor a forrast es az atvett reszt kommentekben egyertelmuen jeloltem. 
// A forrasmegjeloles kotelme vonatkozik az eloadas foliakat es a targy oktatoi, illetve a 
// grafhazi doktor tanacsait kiveve barmilyen csatornan (szoban, irasban, Interneten, stb.) erkezo minden egyeb 
// informaciora (keplet, program, algoritmus, stb.). Kijelentem, hogy a forrasmegjelolessel atvett reszeket is ertem, 
// azok helyessegere matematikai bizonyitast tudok adni. Tisztaban vagyok azzal, hogy az atvett reszek nem szamitanak
// a sajat kontribucioba, igy a feladat elfogadasarol a tobbi resz mennyisege es minosege alapjan szuletik dontes.  
// Tudomasul veszem, hogy a forrasmegjeloles kotelmenek megsertese eseten a hazifeladatra adhato pontokat 
// negativ elojellel szamoljak el es ezzel parhuzamosan eljaras is indul velem szemben.
//=============================================================================================
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
 
#if defined(__APPLE__)                                                                                                                                                                                                            
#include <OpenGL/gl.h>                                                                                                                                                                                                            
#include <OpenGL/glu.h>                                                                                                                                                                                                           
#include <GLUT/glut.h>                                                                                                                                                                                                            
#else                                                                                                                                                                                                                             
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)                                                                                                                                                                       
#include <windows.h>                                                                                                                                                                                                              
#endif                                                                                                                                                                                                                            
#include <GL/gl.h>                                                                                                                                                                                                                
#include <GL/glu.h>                                                                                                                                                                                                               
#include <GL/glut.h>                                                                                                                                                                                                              
#endif          
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Innentol modosithatod...
 
//--------------------------------------------------------
// 3D Vektor
//--------------------------------------------------------
 
struct Vector {
    float x, y, z;
 
    Vector( ) { 
        x = y = z = 0;
    }
    Vector(float x0, float y0, float z0 = 0) { 
        x = x0; y = y0; z = z0;
    }
    Vector operator*(float a) { 
        return Vector(x * a, y * a, z * a); 
    }
    Vector operator+(const Vector& v) {
        return Vector(x + v.x, y + v.y, z + v.z); 
    }
    Vector operator-(const Vector& v) {
        return Vector(x - v.x, y - v.y, z - v.z); 
    }
    float operator*(const Vector& v) {     // dot product
        return (x * v.x + y * v.y + z * v.z); 
    }
    Vector operator%(const Vector& v) {     // cross product
        return Vector(y*v.z-z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }
    float Length() { return sqrt(x * x + y * y + z * z); }
 
    Vector Normal() { return *this * (1 / this->Length()); }
};
 
//--------------------------------------------------------
// Spektrum illetve szin
//--------------------------------------------------------
struct Color {
    float r, g, b;
 
    Color( ) { 
        r = g = b = 0;
    }
    Color(float r0, float g0, float b0) { 
        r = r0; g = g0; b = b0;
    }
    Color operator*(float a) { 
        return Color(r * a, g * a, b * a); 
    }
    Color operator*(const Color& c) { 
        return Color(r * c.r, g * c.g, b * c.b); 
    }
    Color operator+(const Color& c) {
        return Color(r + c.r, g + c.g, b + c.b); 
    }
};
 
const Color WHITE = Color(1.0f, 1.0f, 1.0f);
const Color RED = Color(1.0f, 0.0f, 0.0f);
const Color YELLOW = Color(1.0f, 0.93f, 0.0f);
const Color GREEN = Color(0.0f, 1.0f, 0.0f);
 
void changeColor(Color color) {
    glColor3f(color.r, color.g, color.b);
}
 
const int screenWidth = 600;    // alkalmazas ablak felbontasa
const int screenHeight = 600;
 
enum View { TOP, FRONT, RIGHT };
 
// Inicializacio, a program futasanak kezdeten, az OpenGL kontextus letrehozasa utan hivodik meg (ld. main() fv.)
void onInitialization( ) { 
    glViewport(0, 0, screenWidth, screenHeight);
 
}
 
void drawBorders() {
glBegin(GL_LINES);
    glVertex2f( 0.0f, -1.0f);
    glVertex2f( 0.0f, 1.0f);
    glVertex2f( -1.0f, 0.0f);
    glVertex2f( 1.0f, 0.0f);
glEnd( );
}
 
inline float square(float x) { return x * x; }
inline float cube(float x) { return x * x * x; }
 
int getQuarter(int x, int y) {
    if (x > 300) {
        if (y > 300) {
            return 4;
        }
        return 1;
    }
    if (y > 300){
        return 3;
    }
    else {return 2;}
}
 
Vector convert(Vector v, int Q) { 
    float a = (v.x - 300) / 300;
    float b = (v.y - 300) / -300;
    Vector base;
    Vector shift; 
 
    switch (Q) {
        case 2:
            shift = Vector(0.5, -0.5, 0);
            base = Vector(a, b);
            break;
        case 3:
            shift = Vector(0.5, 0, 0.5);
            base = Vector(a, 0, b);
            break;
        case 4:
            shift = Vector(0, -0.5, 0.5); 
            base = Vector(0, a, b); 
            break;
    }
 
    return (base + shift) * 2;        
}
 
struct Projection{
    Vector P;
    View v;
    Projection(Vector i, View j){ P=i; v=j;}
};
 
struct RennerSpline{
    Vector p[100];
    Vector v[100];
    float t[100];
    Vector herm[4];//A Hermite egyutthatoit megtartjuk, mert kell 2 helyen
    int numCP;
 
    void addControlPoint(const Vector cp){
        if(numCP < 100)
        {
            p[numCP++] = cp;
        }
    }
    
    //Ai-1 terulet
    float Aim1(int i){
        float a = (p[i-1] - p[i-2]).Length();
        float b = (p[i] - p[i-1]).Length();
        return 0.5*a*b;
    }
    //Ai terulet
    float Ai(int i){
        float a = (p[i+1] - p[i+2]).Length();
        float b = (p[i+2] - p[i+1]).Length();
        return 0.5*a*b;
    }
    
//sebessegvektor meghatarozasahoz
    void calcVi(){
        v[0] = Vector();
        v[1] = (p[2] - p[1]).Normal();
        v[numCP-2] = (p[numCP-1] - p[numCP-2]).Normal();
        v[numCP-1] = Vector();
        
        for (int i=2; i<numCP-2; i++){
            v[i]=((p[i]-p[i-1])*Ai(i)+(p[i+1]-p[i])*Aim1(i)).Normal();
        }
    }
 
    void calcTi() {
        t[0] = 0;
        for (int i = 0; i < numCP-1; i++) {
            t[i+1] = t[i]+sqrt(pow((p[i+1].x-p[i].x),2.0)+pow((p[i+1].y-p[i].y),2.0));
        }
    }
 
    Vector findProjections(Projection j) {
        Vector point;
        Vector shift;
 
    switch (j.v) {
        case TOP:
            point = Vector(j.P.x,j.P.y);
            shift = Vector(-0.5,0.5);
            break;
        case FRONT:
            point = Vector(j.P.x,j.P.z);
            shift = Vector(-0.5,-0.5);
            break;
        case RIGHT:
            point = Vector(j.P.y, j.P.z);
            shift = Vector(0.5,-0.5);
            break;
    }
    return point*0.5+shift;
}
 
    void drawPointAt(Vector p) {
        const float r = 0.016;
        glBegin(GL_TRIANGLE_FAN);
        for(float angle = 0.0f; angle < 2*M_PI; angle += 0.5f){
            float x = p.x + r*sin(angle);
            float y = p.y + r*cos(angle);
            glVertex2f(x,y);
        }
        glEnd();
    }    
 
    Vector calcHermite(int i, float pB) {
        
        float dt = t[i+1] - t[i];
 
        Vector d = herm[0] = p[i];
        Vector c = herm[1] = v[i];
        Vector b = herm[2] = ((p[i+1]-p[i])*3)*(1/square(dt))-((v[i+1]+v[i]*2)*(1/dt));
        Vector a = herm[3] = ((p[i]-p[i+1])*2)*(1/cube(dt))+((v[i+1]+v[i])*(1/square(dt)));
 
        return a*cube(pB) + b*square(pB) + c*pB + d;
    }
 
    Vector findPointBetween(int i, float pB, View view){
        Vector r = calcHermite(i, pB);
        
        Projection p(r, view);
        return findProjections(p);
    }
    
    void drawPoints(){
        for (int i = 0; i < numCP; i++) {
            Projection point(p[i], TOP);
            drawPointAt(findProjections(point));
            point.v=FRONT;
            drawPointAt(findProjections(point));
            point.v=RIGHT;
            drawPointAt(findProjections(point));
        }
    }
    void drawCurve(View view){
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < numCP-1; i++) {
            for (double j = t[i]; j < t[i+1]; j += 0.02) {
             float progress = j - t[i];
             Vector point = findPointBetween(i, progress, view);
             glVertex2f(point.x, point.y); 
            }
        }
        glEnd();
    }
 
    float distance(float x0, float y0, float x1, float y1){
        return sqrt( pow((x0-x1),2.0) + pow((y0-y1),2.0));
    }
 
 /*  
    float distance(Vector i, Vector P){
        return (P - i).Length();
    }
  */  
    int findNearestIndex(Vector P) {
        float nearestDistance = 1000;
        float d = 6000.0;
        int foundIndex = 0;
        
        if (numCP == 0){}
        
        for(int i = 0; i<numCP; i++){
            d = distance(p[i].x, p[i].y, P.x, P.y);
            //d = distance(p[i], P);
            if (d < nearestDistance){
                nearestDistance = d;
                foundIndex = i;
            }
        }
    return foundIndex;
    }
 
};
 
RennerSpline spline;
 
long currentTime = 0;
 
bool animState = false;
 
Vector circleProjections[3];
Vector currentCircle;
Vector currentCircleVelocity;
 
int circleSection = 0;
float circleTime;
Vector circleVelocities[3];
 
int placingSpace = 2;
 
// Rajzolas, ha az alkalmazas ablak ervenytelenne valik, akkor ez a fuggveny hivodik meg
void onDisplay( ) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // kepernyo torles
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);        // torlesi szin beallitasa
 
    changeColor(GREEN);
    drawBorders();
 
    changeColor(YELLOW);
    spline.drawPoints();
 
    spline.calcVi();
    spline.calcTi();
 
    changeColor(WHITE);
    spline.drawCurve(TOP);
    spline.drawCurve(FRONT);
    spline.drawCurve(RIGHT);
 
    if (animState) {
        changeColor(RED);
        for (int i = 0; i < 3 ; i++) {
            spline.drawPointAt(circleProjections[i]);
           
            glBegin(GL_LINES);
             glVertex2f(circleProjections[i].x, circleProjections[i].y);
             glVertex2f(circleVelocities[i].x, circleVelocities[i].y);
            glEnd();
        }
    }
 
    glutSwapBuffers();                     // Buffercsere: rajzolas vege
 
}
 
// Billentyuzet esemenyeket lekezelo fuggveny (lenyomas)
void onKeyboard(unsigned char key, int x, int y) {
    if (key == 'd') glutPostRedisplay( );         // d beture rajzold ujra a kepet
    
    if (key == ' ') {       
        animState = !animState; //spacere toggle a piros potty
        circleSection = 0;
        circleTime = 0;
    }
}
 
// Billentyuzet esemenyeket lekezelo fuggveny (felengedes)
void onKeyboardUp(unsigned char key, int x, int y) {
 
}
 
// Eger esemenyeket lekezelo fuggveny
void onMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {  // A GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON illetve GLUT_DOWN / GLUT_UP
 
        int Q = getQuarter(x,y);
        Vector CP(x, y);
                
        if (spline.numCP == 0){
            placingSpace = Q;
        }
        
        if (Q != 1){
            Vector normd = convert(CP, Q);
            
            if (Q == placingSpace) {
                spline.addControlPoint(normd);
            } 
            else {
                spline.p[spline.findNearestIndex(normd)] = normd;
            }
        }
        glutPostRedisplay();                          // Ilyenkor rajzold ujra a kepet
    }
}
 
// Eger mozgast lekezelo fuggveny
void onMouseMotion(int x, int y){
 
}
 
Vector getCircleVelocity(float p){
    Vector c = spline.herm[1];
    Vector b = spline.herm[2];
    Vector a = spline.herm[3];
    Vector v = (a * square(p)*3 + b*p*2 + c)*0.5;    
    return v;
}
 
void animation(long tstart, long tend) {
    for (long t = tstart; t < tend; t++) {
        circleTime += 0.001;
        if (spline.t[circleSection+1] < circleTime) {
            circleSection++;
        }
 
        if (circleSection == spline.numCP) {
            circleSection = 0;
            circleTime = 0;
        }
 
        currentCircle = spline.calcHermite(circleSection, circleTime - spline.t[circleSection]);
        currentCircleVelocity = getCircleVelocity(circleTime - spline.t[circleSection]);
        
        Projection circleP(currentCircle, TOP);
        Projection circleV(currentCircle - currentCircleVelocity,TOP);
        
        circleProjections[TOP] = spline.findProjections(circleP);
        circleVelocities[TOP] = spline.findProjections(circleV);
        
        circleP.v=FRONT;
        circleV.v=FRONT;
        circleProjections[FRONT] = spline.findProjections(circleP);
        circleVelocities[FRONT] = spline.findProjections(circleV);
        
        circleP.v=RIGHT;
        circleV.v=RIGHT;
        circleProjections[RIGHT] = spline.findProjections(circleP);
        circleVelocities[RIGHT] = spline.findProjections(circleV);
 
    }
 
    glutPostRedisplay();
}
 
 
 
// `Idle' esemenykezelo, jelzi, hogy az ido telik, az Idle esemenyek frekvenciajara csak a 0 a garantalt minimalis ertek
void onIdle( ) {
    long prevTime = currentTime;
    currentTime = glutGet(GLUT_ELAPSED_TIME);        // program inditasa ota eltelt ido
 
    if (animState) {
        animation(prevTime, currentTime);
    }
            
}
 
// ...Idaig modosithatod
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
// A C++ program belepesi pontja, a main fuggvenyt mar nem szabad bantani
int main(int argc, char **argv) {
    glutInit(&argc, argv);                 // GLUT inicializalasa
    glutInitWindowSize(600, 600);            // Alkalmazas ablak kezdeti merete 600x600 pixel 
    glutInitWindowPosition(100, 100);            // Az elozo alkalmazas ablakhoz kepest hol tunik fel
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);    // 8 bites R,G,B,A + dupla buffer + melyseg buffer
 
    glutCreateWindow("Grafika hazi feladat");        // Alkalmazas ablak megszuletik es megjelenik a kepernyon
 
    glMatrixMode(GL_MODELVIEW);                // A MODELVIEW transzformaciot egysegmatrixra inicializaljuk
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);            // A PROJECTION transzformaciot egysegmatrixra inicializaljuk
    glLoadIdentity();
 
    onInitialization();                    // Az altalad irt inicializalast lefuttatjuk
 
    glutDisplayFunc(onDisplay);                // Esemenykezelok regisztralasa
    glutMouseFunc(onMouse); 
    glutIdleFunc(onIdle);
    glutKeyboardFunc(onKeyboard);
    glutKeyboardUpFunc(onKeyboardUp);
    glutMotionFunc(onMouseMotion);
 
    glutMainLoop();                    // Esemenykezelo hurok
 
    return 0;
}