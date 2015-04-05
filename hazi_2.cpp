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
// Nev    : Kosztka Sandor
// Neptun : J9RYP4
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
   float operator*(const Vector& v) { 	// dot product
	return (x * v.x + y * v.y + z * v.z); 
   }
   Vector operator%(const Vector& v) { 	// cross product
	return Vector(y*v.z-z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
   }
   
   bool operator==(const Vector &v) const {
        return x == v.x && y == v.y && z == v.z;
    }
   
   float Length() {
        return sqrt(x * x + y * y + z * z); }
   Vector Normal(){ 
       return *this * (1 / this->Length()); }
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

//konstansok definialasa
const float FLT_MAX=1048576.1048576;
const float G=10;//m/s^2
const double EPS = 1e-3; 
const double DMAX = 5;
const int screenWidth = 600;	// alkalmazás ablak 
const int screenHeight = 600;

class Material{
 public:
    Color kd, ks, ka;
    float shininess;
    Color n;
    Color k;
    bool reflective;
    bool refractive;
};

class Light{
 public:
    Vector position;
    Color color;
    float intensity;
    Light(Color c=Color(0,0,0), Vector p=Vector(0,0,0)) {
		color=c;
		position=p;
	}
/*
	Color calculateColor(Intersection inter) {
		Vector tav=pos-inter.pos;
		float s=1/pow(tav.Length(),2.0);
		float intensity =((inter.normal* tav.normalize())>0?(inter.normal* tav.normalize()): 0.0f);
		Color ret=color*s*intensity;
		return ret.tonemap();
	}*/
};

class Ray{
public:
   Vector origin, direction;
    Ray() {
        origin = Vector(0, 0, 0);
        direction = Vector(0, 0, 0);
    }
    
    Ray(Vector ori, Vector dir) {
	this->origin = ori;
	this->direction = dir.Normal();
    }
    Vector getOrig() const {
	return origin;
    }

    Vector getDir() const {
        return direction;
    }
};

class Object{
public:
  Material* material;
  virtual double intersect(Ray& ray) = 0; 
  
};

struct Scene {
    Object* objects[1000];
    Light light;
    int numO;
        
    Scene(){
        numO = 0;
    }
        
    void add(Object* object)
    {
        objects[numO++] = object;
    }
    
    void add(Object* object, Color objColor, Color n, Color k, bool reflective, bool refractive) //objektum hozzáadása a színtérhez
    {
        objects[numO] = object;
        objects[numO]->Material.color = objColor; 
        objects[numO]->Ka = objColor * 0.2;
        objects[numO]->material.n = n;
        objects[numO]->material.k = k; 
        objects[numO]->material.reflective = reflective; 
        objects[numO]->material.refractive = refractive;
        numO++;
    }

};

class Plane: public Object {
	Vector point;
	Vector normal;
public:
	Plane(Vector p, Vector n) {
		point = p;
		normal = n;
	}

	float intersect(const Ray& ray) {
		float d = normal * ray.getDir();
		if (d == 0.0f) {
			return -1.0f;
		}

		float t = (normal * (point - ray.getOrig())) / (normal * ray.getDir());

		if (t > 0.01f)
			return t;
		if (t > 0.0f)
			return 0.0f;
		return -1.0f;
	}

	float intersect(const Ray& ray, float t1, float t2) {
		return intersect(ray);
	}

	Color getColor(const Vector& p) {
		float a = fabsf(p.z);
		float b = fabsf(p.x);

		if ((int) roundf(a) % 2 == 0 && (int) roundf(b) % 2 == 0) {
			return Color(1.0f, 1.0f, 1.0f);
		} else if ((int) roundf(a) % 2 == 1 && (int) roundf(b) % 2 == 1) {
			return Color(1.0f, 1.0f, 1.0f);
		} else {
			return Color(0.0f, 0.0f, 0.0f);
		}
	}

	Vector getNormal(const Vector& v) {
		return normal;
	}
};

class Triangle : public Object{
public:
    Vector            a, b, c;        
    long            ai, bi, ci;        
 
    Vector            normal;    
    Vector            Na, Nb, Nc;    
 
    Triangle(Vector p0, Vector p1, Vector p2, Vector n0, Vector n1, Vector n2) {
        a = p0;
        b = p1;
        c = p2;
 
        Na = n0.Normal();
        Nb = n1.Normal();
        Nc = n2.Normal();
 
        normal = (b - a) % (c - a);
        normal.Normal();
    }
 
    double intersect(Ray& ray) {
        double cost = normal * ray.direction;
    
        if (fabs(cost) <= EPS) {
            return -1;
        }
 
        double t = ((a - ray.origin) * normal) / cost;
        if(t < EPS) 
            return -1;
 
        Vector ip = ray.origin + ray.direction * t;
 
        double c1 = (((b - a) % (ip - a)) * normal);
        double c2 = (((c - b) % (ip - b)) * normal);
        double c3 = (((a - c) % (ip - c)) * normal);
        
        if (c1 >= 0 && c2 >= 0 && c3 >= 0)
        {
            return t;
        }
        if (c1 <= 0 && c2 <= 0 && c3 <= 0)
        {
            return t;
        }
        return -1;
    }
 
    Vector getNormal(Vector& intersect)    {
 
        float u, v;
        Vector v0, v1, v2;
 
        v0 = c - a;
        v1 = b - a;
        v2 = intersect - a;
 
        u = ((v1 * v1) * (v2 * v0) - (v1 * v0) * (v2 * v1)) / ((v0 * v0) * (v1 * v1) - (v0 * v1) * (v1 * v0));
        v = ((v0 * v0) * (v2 * v1) - (v0 * v1) * (v2 * v0)) / ((v0 * v0) * (v1 * v1) - (v0 * v1) * (v1 * v0));
 
        return Nc * u + Nb * v + Na * (1 - (u + v));
    }
 
};

void buildTorus(Vector center,  Scene& scene)
{
    float R = 140;
    float r = 40;    
 
     for(int i = 0; i < 10; i++){
 
        float AngleOuter = (2.0*M_PI/10);
                
        for(int j = 0; j < 5; j++){
 
            float AngleInner = (2.0*M_PI/5);
 
            Vector v1, v2, v3, v4;
 
            v1.x = cos (AngleOuter * i) * (R + r * cos(AngleInner * j));
            v1.y = sin (AngleOuter * i) * (R + r * cos(AngleInner * j));
            v1.z = r * sin (AngleInner * j);
 
            v2.x = cos (AngleOuter * (i+1)) * (R + r * cos(AngleInner * j));
            v2.y = sin (AngleOuter * (i+1)) * (R + r * cos(AngleInner * j));
            v2.z = r * sin (AngleInner * j);
 
            v3.x = cos (AngleOuter * (i)) * (R + r * cos(AngleInner * (j+1)));
            v3.y = sin (AngleOuter * (i)) * (R + r * cos(AngleInner * (j+1)));
            v3.z = r * sin (AngleInner * (j+1));
 
            v4.x = cos (AngleOuter * (i+1)) * (R + r * cos(AngleInner * (j+1)));
            v4.y = sin (AngleOuter * (i+1)) * (R + r * cos(AngleInner * (j+1)));
            v4.z = r * sin (AngleInner * (j+1));
 
            Vector p1, p2, p3, p4;
        
            p1 = center + v1;
            p2 = center + v2;
            p3 = center + v3;
            p4 = center + v4;
 
            scene.add(new Triangle(p1, p2, p3,
                (v1 - Vector(cos( AngleOuter * i) * R, sin( AngleOuter * i) * R, 0)),
                (v2 - Vector(cos( AngleOuter * (i+1)) * R, sin( AngleOuter * (i+1)) * R, 0)),
                (v3 - Vector(cos( AngleOuter * i) * R, sin( AngleOuter * i) * R, 0))), Color(0.1, 0.8, 0.2), Color(0.17, 0.35, 1.5),Color(3.1, 2.7, 1.9),true, false);
 
            scene.add(new Triangle(p4, p3, p2,
                (v4 - Vector(cos(AngleOuter * (i+1)) * R, sin( AngleOuter * (i+1)) * R, 0)),
                (v3 - Vector(cos(AngleOuter * i) * R, sin( AngleOuter * i) * R, 0)),
                (v2 - Vector(cos(AngleOuter * (i+1)) * R, sin( AngleOuter * (i+1)) * R, 0))), Color(0.1, 0.8, 0.2), Color(0.17, 0.35, 1.5), Color(3.1, 2.7, 1.9), true, false);
        }
    }
}


/*
float3 trace(Ray ray) {
  Hit hit = firstIntersect(ray);
  if(hit.t < 0) return La; // nothing
  float3 outRadiance (0, 0, 0);
  for(each light source i){
    Ray shadowRay(x + Nepsilon, Li);
    Hit shadowHit = firstIntersect(shadowRay);
    if(shadowHit.t < 0 || shadowHit.t > |x - yi| )
       outRadiance += hit.material->shade(N,V,Li, Intensi);
  }
  if(hit.material->reflective){
    float3 reflectionDir = reflect(V,N);
    Ray reflectedRay(x + Nepsilon, reflectionDir );
    outRadiance +=trace(reflectedRay)*F(V,N);
  }
  if(hit.material->refractive) {
    float3 refractionDir = refract(V,N);
    Ray refractedRay(x - Nepsilon, refractionDir );
    outRadiance +=trace(refractedRay)*(float3(1,1,1)-F(V,N));
  }
  return outRadiance;
}
*/
/*
Render( )
     for each pixel p
	Ray r = GetRay( eye -> pixel p )
      	color = trace(ray)
	WritePixel(p, color)
     endfor
end
*/

class Camera {
 public:
    Vector eye;
    Vector lookAt;
    Vector right;
    Vector up;
    float width;
    float height;
    Camera(Vector &eye, Vector &lookAt, float width, float height)
            : eye(eye), lookAt(lookAt), width(width), height(height) {
        up = Vector(0, 0, 1);
        if ((lookAt - eye).Normal() == up) {
            up = Vector(1, 0, 0);
        } else if ((eye - lookAt).Normal() == up) {
            up = Vector(0, 1, 0);
        }
        right = ((lookAt - eye) % up).Normal();
        up = (right % (lookAt - eye)).Normal();
    }

    Ray getRay(unsigned int x, unsigned int y) {
        Vector p = lookAt + right * (2 * (x + 0.5f) / width - 1) + up * (2 * (y + 0.5f) / height - 1);
        return Ray(eye, p - eye);
    }
};


Color image[screenWidth*screenHeight];	// egy alkalmazás ablaknyi kép


// Inicializacio, a program futasanak kezdeten, az OpenGL kontextus letrehozasa utan hivodik meg (ld. main() fv.)
void onInitialization( ) { 
	glViewport(0, 0, screenWidth, screenHeight);

    // Peldakent keszitunk egy kepet az operativ memoriaba
    for(int Y = 0; Y < screenHeight; Y++)
		for(int X = 0; X < screenWidth; X++)
			image[Y*screenWidth + X] = Color((float)X/screenWidth, (float)Y/screenHeight, 0);

    
    Material gold;
    gold.setN(Color(0.17f, 0.35f, 1.5f));
    gold.setK(Color(3.1f, 2.7f, 1.9f));
    gold.setReflective(true);
}

// Rajzolas, ha az alkalmazas ablak ervenytelenne valik, akkor ez a fuggveny hivodik meg
void onDisplay( ) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);		// torlesi szin beallitasa
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // kepernyo torles

    // ..

    // Peldakent atmasoljuk a kepet a rasztertarba
    glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, image);
    // ...

    glutSwapBuffers();     				// Buffercsere: rajzolas vege

}

// Billentyuzet esemenyeket lekezelo fuggveny (lenyomas)
void onKeyboard(unsigned char key, int x, int y) {
    if (key == 'd') glutPostRedisplay( ); 		// d beture rajzold ujra a kepet
}
// Billentyuzet esemenyeket lekezelo fuggveny (felengedes)
void onKeyboardUp(unsigned char key, int x, int y) {}

// Eger esemenyeket lekezelo fuggveny
void onMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)   // A GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON illetve GLUT_DOWN / GLUT_UP
		glutPostRedisplay( ); 						 // Ilyenkor rajzold ujra a kepet
}
// Eger mozgast lekezelo fuggveny
void onMouseMotion(int x, int y){}
// `Idle' esemenykezelo, jelzi, hogy az ido telik, az Idle esemenyek frekvenciajara csak a 0 a garantalt minimalis ertek
void onIdle( ) {
     long time = glutGet(GLUT_ELAPSED_TIME);		// program inditasa ota eltelt ido
}

// ...Idaig modosithatod
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// A C++ program belepesi pontja, a main fuggvenyt mar nem szabad bantani
int main(int argc, char **argv) {
    glutInit(&argc, argv); 				// GLUT inicializalasa
    glutInitWindowSize(600, 600);			// Alkalmazas ablak kezdeti merete 600x600 pixel 
    glutInitWindowPosition(100, 100);			// Az elozo alkalmazas ablakhoz kepest hol tunik fel
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	// 8 bites R,G,B,A + dupla buffer + melyseg buffer

    glutCreateWindow("Grafika hazi feladat");		// Alkalmazas ablak megszuletik es megjelenik a kepernyon

    glMatrixMode(GL_MODELVIEW);				// A MODELVIEW transzformaciot egysegmatrixra inicializaljuk
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);			// A PROJECTION transzformaciot egysegmatrixra inicializaljuk
    glLoadIdentity();

    onInitialization();					// Az altalad irt inicializalast lefuttatjuk

    glutDisplayFunc(onDisplay);				// Esemenykezelok regisztralasa
    glutMouseFunc(onMouse); 
    glutIdleFunc(onIdle);
    glutKeyboardFunc(onKeyboard);
    glutKeyboardUpFunc(onKeyboardUp);
    glutMotionFunc(onMouseMotion);

    glutMainLoop();					// Esemenykezelo hurok
    
    return 0;
}
