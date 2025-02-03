#include <iostream>   
#include <GL/glut.h>       
#include <GL/freeglut.h>    
#include <math.h>         
using namespace std; 

struct Move {
    float rotate = 0.0;   
    float scale = 1.0;    
    float translateX = 0.0; 
    float translateY = 0.0; 
} coklat;

bool isMoving = true;      
bool is2DMode = false;       
bool hiddenCarte = false; 
bool Loading = true;  
float loadingProgress = 0.0; 
bool show =true;  

void Coklat();
void Kartesius() {
    glLineWidth(2.0);
    glBegin(GL_LINES);
    // Sumbu X (Merah)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-50.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    // Sumbu Y (Hijau)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -50.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);
    // Sumbu Z (Biru)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -50.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();
}


void Text(float x, float y, float z, string text, int fontSize) {
    glColor3ub(84, 51, 16); 
    glPushMatrix();
    glTranslatef(x, y, z);   
    glRasterPos2f(0,0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)text.c_str());
    glPopMatrix();
}


void LoadingScene() { 
    glPushMatrix();
    Text(-20.0, 0.0, 0.0, "GRAFIKA KOMPUTER", 90); 

    glPushMatrix();
    glRotatef(30, 0, 1, 0); 
    glColor3ub(84, 51, 16);  
    float progressWidth = (loadingProgress / 100.0) * 40.0; 
    glTranslatef(-20.0 + progressWidth / 2.0, -2.0, 0.1); 
    glScalef(progressWidth, 2.0, 1.0); 
    glutSolidCube(1.0); 
    glPopMatrix();

    loadingProgress += 0.5;
    if (loadingProgress >= 100.0) {
        Loading = false;  
        loadingProgress = 0.0;
        Coklat();    
    }
    glPopMatrix();
}

void Background() {
    glDisable(GL_DEPTH_TEST); 
    glBegin(GL_QUADS);

    // Warna sudut kiri bawah
    glColor3ub(158, 223, 156);
	glColor3ub(82, 110, 72);  
    glVertex2f(-1.0f, -1.0f);

    // Warna sudut kanan bawah
    glColor3ub(98, 130, 93); 
    glVertex2f(1.0f, -1.0f);

    // Warna sudut kanan atas
    glColor3ub(82, 110, 72); 
    glVertex2f(1.0f, 1.0f);

    // Warna sudut kiri atas
    glColor3ub(194, 255, 199);
    glVertex2f(-1.0f, 1.0f);

    glEnd();
    glEnable(GL_DEPTH_TEST); 
}

void Coklat() {
    glPushMatrix();
    glTranslatef(coklat.translateX, coklat.translateY, 0.0); 
    glRotatef(coklat.rotate, 0.0, 1.0, 0.0); 
    glScalef(coklat.scale, coklat.scale, coklat.scale); 

	glColor3ub(110, 142, 89); 
    glPushMatrix();
    glScalef(10.0, 1.0, 3.0);
    glutSolidCube(1.5);
    glPopMatrix();
    
    glColor3ub(98, 130, 93);
    for (int i = -4; i <= 4; i++) {
        glPushMatrix();
        glTranslatef(i * 1.6, 1.0, 0.0); 
        glScalef(1.0, 0.5, 2.5); 
        glutSolidCube(1.5);
        glPopMatrix();
    }
    glPopMatrix();
    glPopMatrix();

}

void update(int value) { 
    if (isMoving) { 
        coklat.rotate += 1.0;   
    }
    glutPostRedisplay(); 
    glutTimerFunc(1000 / 60, update, 0); // Jadwalkan pembaruan berikutnya
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            coklat.scale += 0.1;
                if (coklat.scale >= 5){
                	coklat.scale -=0.1;
				}
            break;
        case '-':
            // Perkecil skala objek saat tombol '-' ditekan
            coklat.scale -= 0.1;
                 if (coklat.scale <= 0.5){
                	coklat.scale +=0.1;
                }
            break;
        case 'w':
        case 'W':
            // Geser objek ke atas
            coklat.translateY += 1.0;
                if (coklat.translateY >= 30){
                	coklat.translateY -=1.0;
				}
            break;
        case 's':
        case 'S':
            // Geser objek ke bawah
            coklat.translateY -= 1.0;
                if (coklat.translateY <= -30){
                	coklat.translateY +=1.0;
				}
            break;
        case 'd':
        case 'D':
            // Geser objek ke kanan
            coklat.translateX += 1.0;
                if (coklat.translateX >= 30){
                	coklat.translateX -=1.0;
				}
            break;
        case 'a':
        case 'A':
            // Geser objek ke kiri
                coklat.translateX -= 1.0;
                if (coklat.translateX <= -30){
                	coklat.translateX +=1.0;
				}
            break;
        case 'c':
        case 'C':
//cartesius
            hiddenCarte = !hiddenCarte;
            break;
        case 'r':
        case 'R':
            // rotasi
            isMoving = !isMoving;
            break;
    }
    glutPostRedisplay(); 
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1); 
    Background(); 
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (Loading) {
        LoadingScene(); 
    } else {
        if (hiddenCarte) {
			Kartesius();
        }
        if (show) {
            Coklat();
        }
    }
    glutSwapBuffers(); 
}

void init3D()
{
    glEnable(GL_DEPTH_TEST);     
    glEnable(GL_COLOR_MATERIAL); 
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float lightPos[] = {-10.0f, 10.0f, 10.0f, 1.0f}; 
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f}; 
    GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1.0, 100.0);                     
    gluLookAt(30.0, 30.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(800, 600); 
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("2306143_Salma Aulia Nisa_UASGRAFKOM2024_E");  
    init3D(); 
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); 
    glutTimerFunc(1000 / 60, update, 0); 
    glutMainLoop(); 
    return 0; 
}
