/*double currentAngle = 0.0;
double stepAngle = 1.0;
double x_rotation = 0.0;
double y_rotation = 0.0;
double z_rotation = 0.0;
double pulseLight = -1.0;
double stepPulse = 0.01;
const double Xmin = -1.0, Xmax = 1.0;
const double Ymin = -1.0, Ymax = 1.0;
const double Zmin = -10000.0, Zmax = 10000.0;

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

float DIFFUSE_LIGHT[] = { 1.0f, 1.0f,  1.0f, 1.0f };
float AMBIENT_LIGHT[] = { 1.0f, 1.0f,  1.0f, 1.0f };
float light_pos[] = { 0.0f, 0.0f, 0.0f, 0.0f };

void initRendering()
{
    glEnable(GL_DEPTH_TEST);	// Depth testing must be turned on
    //glEnable(GL_LIGHT0);
    //glEnable (GL_LIGHTING);
    //glEnable(GL_TEXTURE_2D);
    //glEnable (GL_COLOR_MATERIAL);

}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
    double scale, center;
    double windowXmin, windowXmax, windowYmin, windowYmax;

    // Define the portion of the window used for OpenGL rendering.
    glViewport( 0, 0, w, h );	// View port uses whole window

    // Set up the projection view matrix: orthographic projection
    // Determine the min and max values for x and y that should appear in the window.
    // The complication is that the aspect ratio of the window may not match the
    //		aspect ratio of the scene we want to view.
    w = (w==0) ? 1 : w;
    h = (h==0) ? 1 : h;
    if ( (Xmax-Xmin)/w < (Ymax-Ymin)/h ) {
        scale = ((Ymax-Ymin)/h)/((Xmax-Xmin)/w);
        center = (Xmax+Xmin)/2;
        windowXmin = center - (center-Xmin)*scale;
        windowXmax = center + (Xmax-center)*scale;
        windowYmin = Ymin;
        windowYmax = Ymax;
    }
    else {
        scale = ((Xmax-Xmin)/w)/((Ymax-Ymin)/h);
        center = (Ymax+Ymin)/2;
        windowYmin = center - (center-Ymin)*scale;
        windowYmax = center + (Ymax-center)*scale;
        windowXmin = Xmin;
        windowXmax = Xmax;
    }

    // Now that we know the max & min values for x & y
    //		that should be visible in the window,
    //		we set up the orthographic projection.
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // indicate the bound of projection
    // if an object is after Zmax and Zmin it will not be displayed
    glOrtho( windowXmin, windowXmax, windowYmin, windowYmax, Zmin, Zmax);
}

void drawSnowMan() {

    glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
    glTranslatef(0.0f ,0.75f, 0.0f);
    glutSolidSphere(0.75f,20,20);

// Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f,20,20);

// Draw Eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();

// Draw Nose
    glColor3f(1.0f, 0.5f , 0.5f);
    glRotatef(0.0f,1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f,0.5f,10,2);
}

void drawScene()
{

    // Clear Color and Depth Buffers

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();
    gluLookAt(	x, 1.0f, z,
            x+lx, 0.0f,  z+lz,
            0.0f, 1.0f,  0.0f);

        // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

        // Draw 36 SnowMen
    int i,j;
    for(i = -3; i < 3; i++)
        for(j=-3; j < 3; j++) {
            glPushMatrix();
            glTranslatef(i*10.0,0,j * 10.0);
            drawSnowMan();
            glPopMatrix();
        }
    drawSnowMan();
    glFlush();
    glutSwapBuffers();
}



void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(x_rotation || y_rotation || z_rotation)
    {
        currentAngle += stepAngle;
        if(currentAngle > 360.0)
        {
            currentAngle = currentAngle - 360.0*(int)(currentAngle/360.0);
        }
        glRotatef( currentAngle, x_rotation, y_rotation, z_rotation);
    }

    //  glLightfv(GL_LIGHT0,GL_AMBIENT , AMBIENT_LIGHT);
    //glLightfv(GL_LIGHT0,GL_DIFFUSE , DIFFUSE_LIGHT);
    //glLightfv(GL_LIGHT0,GL_POSITION, light_pos    );
    //glLightfv(GL_LIGHT0,GL_EMISSION , AMBIENT_LIGHT);
    //glLightfv(GL_LIGHT0,GL_POSITION, light_pos    );

        pulseLight += stepPulse;
        if(pulseLight > 1.0)
        {
            pulseLight = -1.0;
        }

        float yellow_mat[] = {1.0, 1.0, 0.0};
        float zero_mat[] = {0.0,0.0,0.0};

        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow_mat);

         *GL_AMBIENT
params contains four fixed-point or floating-point values that specify the ambient RGBA reflectance of the material. The values are not clamped. The initial ambient reflectance is (0.2, 0.2, 0.2, 1.0).

GL_DIFFUSE
params contains four fixed-point or floating-point values that specify the diffuse RGBA reflectance of the material. The values are not clamped. The initial diffuse reflectance is (0.8, 0.8, 0.8, 1.0).

GL_SPECULAR
params contains four fixed-point or floating-point values that specify the specular RGBA reflectance of the material. The values are not clamped. The initial specular reflectance is (0, 0, 0, 1).

GL_EMISSION
params contains four fixed-point or floating-point values that specify the RGBA emitted light intensity of the material. The values are not clamped. The initial emission intensity is (0, 0, 0, 1).

GL_SHININESS
params is a single fixed-point or floating-point value that specifies the RGBA specular exponent of the material. Only values in the range [0, 128] are accepted. The initial specular exponent is 0.

GL_AMBIENT_AND_DIFFUSE
Equivalent to calling glMaterial twice with the same parameter values, once with GL_AMBIENT and once with GL_DIFFUSE.

        glutSolidSphere(0.5,10,10);

        glPushMatrix();
        glTranslatef(0.7,0.7,+1.0);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, zero_mat);
        //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero_mat);
        //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, zero_mat);
        glutSolidSphere(0.2,10,10);
        glPopMatrix();
        float mat_ambient[] = {pulseLight, pulseLight, pulseLight, pulseLight};
        float mat_ambient_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
        //
        float mat_color_diffuse[] = {1.0f, 1.0f, 1.0f, pulseLight};
        float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        float no_shininess = 0.0f;
        float low_shininess[] = {5.0f};
        float high_shininess[] = {0.0f};
        float mat_emission[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_color_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        //gluSphere(quadric, 1.0f, 16, 16);

    // stop overflows ?
    currentAngle += stepAngle;
    if(currentAngle > 360.0)
    {
        currentAngle = currentAngle - 360.0*(int)(currentAngle/360.0);
    }

    // Rotate the image
    glMatrixMode( GL_MODELVIEW );			// Current matrix affects objects positions
    glLoadIdentity();						// Initialize to the identity
    //glTranslatef( 1.5, 1.5, 0.0 );					// Translate rotation center from origin

    //glVertex3f(-0.7f,-1.5f,-5.0f);
    //glVertex3f(0.7f,-1.5f,-5.0f);
    //glVertex3f(0.4f,-0.5f,-5.0f);

    //glVertex3f(-0.7f,-1.5f,-5.0f);
    //glVertex3f(0.4f,-0.5f,-5.0f);
    //glVertex3f(-0.4f,-0.5f,-5.0f);
    //glScalef(2,2,2);

    //trapezoid
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    glRotatef( currentAngle, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f( -0.2, -0.1, 0.0);
    glVertex3f( -0.1, 0.1, 0.0);
    glVertex3f( 0.2, -0.1, 0.0);

    glVertex3f( -0.1, 0.1, 0.0);
    glVertex3f( 0.1, 0.1, 0.0);
    glVertex3f( 0.2, -0.1, 0.0);
    glEnd();
    glPopMatrix();

    // house (pentagon)
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.0);
    glRotatef( currentAngle, 1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f( -0.2, 0.0, 0.0);
    glVertex3f( 0.0, 0.2, 0.0);
    glVertex3f( 0.2, 0.0, 0.0);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f( -0.2, 0.0, 0.0);
    glVertex3f( 0.2, 0.0, 0.0);
    glVertex3f( 0.2, -0.2, 0.0);
    glVertex3f( -0.2, -0.2, 0.0);
    glEnd();
    glPopMatrix();

    //romboids
    glPushMatrix();
    glTranslatef(-0.5, 0.5, 0.0);
    glScalef(1.5,1.5,1.5);
    glRotatef( currentAngle, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f( -0.2, 0.0, 0.0);
    glVertex3f( 0.0, 0.1, 0.0);
    glVertex3f( 0.2, 0.0, 0.0);
    glVertex3f( 0.0, -0.1, 0.0);
    glEnd();
    glPopMatrix();


    // Flush the pipeline, swap the buffers
    glFlush();
    glutSwapBuffers();
    //glutPostRedisplay();
}

void handleKeypress(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 27:
            exit (0);
            break;
    }
}

void handleSpecialKeypress(unsigned char key,int x,int y)
{
    // "special key" definition is very ambiguous
    int mod = glutGetModifiers();
    // if a modifiers button is pressed in this case (ctrl, alt or shift)
    // perform another set of action
    if (mod == GLUT_ACTIVE_CTRL || mod == GLUT_ACTIVE_SHIFT || mod == GLUT_ACTIVE_ALT)
    {
        switch(key)
        {
        case GLUT_KEY_LEFT:
            //y_rotation= 0.0;
            break;
        case GLUT_KEY_RIGHT:
            //y_rotation= 1.0;
            break;
        case GLUT_KEY_UP:
            //x_rotation= 1.0;
            break;
        case GLUT_KEY_DOWN:
            //x_rotation= 0.0;
            break;
        case GLUT_KEY_PAGE_UP:
            //z_rotation= 1.0;
            break;
        case GLUT_KEY_PAGE_DOWN:
            //z_rotation= 0.0;
            break;
        }
    }
    else
    {
        switch(key)
        {
        case GLUT_KEY_LEFT:
            y_rotation= 0.0;
            break;
        case GLUT_KEY_RIGHT:
            y_rotation= 1.0;
            break;
        case GLUT_KEY_UP:
            x_rotation= 1.0;
            break;
        case GLUT_KEY_DOWN:
            x_rotation= 0.0;
            break;
        case GLUT_KEY_PAGE_UP:
            z_rotation= 1.0;
            break;
        case GLUT_KEY_PAGE_DOWN:
            z_rotation= 0.0;
            break;
        }
    }
}

int main( int argc, char** argv )
{
    glutInit(&argc,argv);

    // We're going to animate it, so double buffer

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Window position (from top corner), and size (width and hieght)
    // -1 -1 automatic positioning
    glutInitWindowPosition(0, 0);
    glutInitWindowSize( 512, 512 );
    glutCreateWindow("SVDRV_as02");

    // Initialize OpenGL as we like it..
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc(handleKeypress);			// Handles "normal" ascii symbols
    glutSpecialFunc(handleSpecialKeypress);
    // called in case of resize
    glutReshapeFunc( resizeWindow );
    // call this whenever window needs redrawing
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);

    fprintf(stdout, "Press esc to exit\n");
    glutMainLoop();

    return(0);	// This line is never reached.
}


 *#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

// sphere proprieties
#define SPHERE_SLICE 100
#define SPHERE_STACKS 100

// time step
#define TIME_STEP 10
#define STEP_TIME_STEP 1

// font
#define DEFAULT_FONT GLUT_BITMAP_TIMES_ROMAN_24
#define DEFAULT_FONT_R 1.0
#define DEFAULT_FONT_G 1.0
#define DEFAULT_FONT_B 1.0
#define DEFAULT_FONT_HEIGHT 24.0
#define DEFAULT_BG_POSITION -100.0
#define DEFAULT_DELTA_FRACTION 1;
#define DEFAULT_WEEL_STEP 5;

typedef struct
{
    double radius;
    int rotationTime;
    double r;
    double g;
    double b;
    double angle; //angle of rotation
    //texture proprieties;
    GLuint textureId;
} RotatingTexturedSphere;

typedef struct
{
    double x,y,z, light_intensity; //position
    char* name;
    //light proprieties
    RotatingTexturedSphere sphereModel;
} Star;

typedef struct
{
    Star *star;
    char *name;
    int revolutionTime;
    double x,y,z; //position
    double angle; //angle of revolution
    RotatingTexturedSphere sphereModel;
} Planet;

void initStar(Star *star, char* name, double radius, double x, double y, double z, int rotationTime) //add texture!
{
    star->name = name;
    star->sphereModel.radius = radius;
    star->x = x;
    star->y = y;
    star->z = z;
    star->sphereModel.rotationTime = rotationTime;
    star->sphereModel.angle = 0.0;
}

void setStarLight(Star *star, double light_intensity)
{
    star->light_intensity = light_intensity;
}

void setStarColor(Star *star, double r, double g, double b)
{
    star->sphereModel.r = r;
    star->sphereModel.g = g;
    star->sphereModel.b = b;
}

void setPlanetColor(Planet *planet, double r, double g, double b)
{
    planet->sphereModel.r = r;
    planet->sphereModel.g = g;
    planet->sphereModel.b = b;
}

void initPlanet(Planet *planet, char* name, Star *star, double radius, double x, double y, double z, int rotationTime, int revolutionTime)
{
    planet->name = name;
    planet->star = star;
    planet->sphereModel.radius = radius;
    planet->x = x;
    planet->y = y;
    planet->z = z;
    planet->sphereModel.rotationTime = rotationTime;
    planet->sphereModel.angle = 0.0;
    planet->revolutionTime = revolutionTime;
    planet->angle = 0.0;
}

void updateStarPosition(Star *star, int hours)
{
    int rotationHours = hours%star->sphereModel.rotationTime;

    double rotationAngle = 360.0*((double)rotationHours/(double)star->sphereModel.rotationTime);
    star->sphereModel.angle = rotationAngle;
}

void updatePlanetPosition(Planet *planet, int hours)
{
    int rotationHours = hours%planet->sphereModel.rotationTime;
    int revolutionDays = (hours/planet->sphereModel.rotationTime)%planet->revolutionTime;

    double rotationAngle = 360.0*((double)rotationHours/(double)planet->sphereModel.rotationTime);
    double revolutionAngle = 360.0*((double)revolutionDays/(double)planet->revolutionTime);

    planet->angle = revolutionAngle;
    planet->sphereModel.angle = rotationAngle;
}

void handleKeypress(unsigned char key,int x,int y);
void handleSpecialKeypress(unsigned char key,int x,int y);
void drawScene();
void idleScene();
void initRendering();
void changeSize(int w, int h);
void drawStar(Star *star);
void drawPlanet(Planet *planet);
void initModel();
void draw2DText(double x, double y, char* text);
void draw3DText(double x, double y, double z, char* text);
void initRotatingTexturedSphere(RotatingTexturedSphere *sphere, char* filename, GLenum rgbMode);
void initTextureId(GLuint *textureId, char* filename, GLenum rgbMode);
void mouseMove(int x, int y);
void mouseButton(int button, int state, int x, int y);
void pressKey(int key, int xx, int yy);
void releaseKey(int key, int x, int y);

Star sun, universe;
Planet p1,p2,p3,p4,p5,p6,p7,p8;
double hours;
int showLabels, isRunning, activeKeyModifiers;
GLuint bgTextureId;
double startX, startY, startZ, deltaX, deltaY, deltaZ, deltaXMin, deltaXMax, deltaYMin, deltaYMax, deltaZMin, deltaZMax;
int xOrigin, yOrigin;

void initRotatingTexturedSphere(RotatingTexturedSphere *sphere, char* filename, GLenum rgbMode)
{
    initTextureId(&sphere->textureId, filename, rgbMode);
}

void initTextureId(GLuint *textureId, char* filename, GLenum rgbMode)
{
    SDL_Surface* surface = IMG_Load(filename);
    if (surface==NULL)
    {
        printf("Error: \"%s\"\n",SDL_GetError());
        exit(1);
    }

    glGenTextures(1,textureId);
    //Select (bind) the texture we just generated as the current 2D texture OpenGL is using/modifying.
    //All subsequent changes to OpenGL's texturing state for 2D textures will affect this texture.
    glBindTexture(GL_TEXTURE_2D,textureId[0]);
    //Specify the texture's data.  This function is a bit tricky, and it's hard to find helpful documentation.  A summary:
    //   GL_TEXTURE_2D:    The currently bound 2D texture (i.e. the one we just made)
    //               0:    The mipmap level.  0, since we want to update the base level mipmap image (i.e., the image itself,
    //                         not cached smaller copies)
    //         GL_RGBA:    The internal format of the texture.  This is how OpenGL will store the texture internally (kinda)--
    //                         it's essentially the texture's type.
    //      surface->w:    The width of the texture
    //      surface->h:    The height of the texture
    //               0:    The border.  Don't worry about this if you're just starting.
    //          GL_RGB:    The format that the *data* is in--NOT the texture!  Our test image doesn't have an alpha channel,
    //                         so this must be RGB.
    //GL_UNSIGNED_BYTE:    The type the data is in.  In SDL, the data is stored as an array of bytes, with each channel
    //                         getting one byte.  This is fairly typical--it means that the image can store, for each channel,
    //                         any value that fits in one byte (so 0 through 255).  These values are to interpreted as
    //                         *unsigned* values (since 0x00 should be dark and 0xFF shold be bright).
    // surface->pixels:    The actual data.  As above, SDL's array of bytes.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w,surface->h, 0, rgbMode,GL_UNSIGNED_BYTE,surface->pixels);
    //Set the minification and magnification filters.  In this case, when the texture is minified (i.e., the texture's pixels (texels) are
    /smaller* than the screen pixels you're seeing them on, linearly filter them (i.e. blend them together).  This blends four texels for
    //each sample--which is not very much.  Mipmapping can give better results.  Find a texturing tutorial that discusses these issues
    //further.  Conversely, when the texture is magnified (i.e., the texture's texels are *larger* than the screen pixels you're seeing
    //them on), linearly filter them.  Qualitatively, this causes "blown up" (overmagnified) textures to look blurry instead of blocky.
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //Unload SDL's copy of the data; we don't need it anymore because OpenGL now stores it in the texture.
    SDL_FreeSurface(surface);
}

int main( int argc, char** argv )
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    // Window position (from top corner), and size (width and hieght)
    // -1 -1 automatic positioning
    glutInitWindowPosition(0, 0);
    // i want 16:10 => 1024x768
    // i want 16:9 => 1280x800
    //glutInitWindowSize( 1600, 1000 );
    glutInitWindowSize( 1600, 900);
    glutCreateWindow("SVDRV_as02");
    // Initialize OpenGL
    initRendering();
    // Inizialize Model, Inizialize Texture moved in Inizialize Model: MUST BE AFTER INIT RENDERING!!!
    initModel();
    // Set up callback functions for key presses
    // Handles "normal" ascii symbols
    glutKeyboardFunc(handleKeypress);
    // Handles other key (not used)
    // glutSpecialFunc(handleSpecialKeypress);
    glutIgnoreKeyRepeat(GL_TRUE);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    // mouse handling
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    // called in case of resize
    glutReshapeFunc(changeSize);
    // call this whenever window needs redrawing
    glutDisplayFunc(drawScene);
    // call function during execution (to not use glutPostRedisplay();)
    glutIdleFunc(idleScene);

    // start main loop
    fprintf(stdout, "Press esc to exit\n");
    glutMainLoop();

    return(0);	// This line is never reached.
}

void handleKeypress(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 27:
            exit (0);
            break;
        case 't':
        case 'T':
            showLabels = !showLabels;
            break;
        case 'r':
        case 'R':
            isRunning = !isRunning;
            break;
        case 's':
        case 'S':
            if(isRunning) isRunning = !isRunning;
            hours += STEP_TIME_STEP;
            break;
        case 'i':
            hours = 0;
            initModel();
            break;
    }
}

void pressKey(int key, int xx, int yy)
{
    switch (key)
    {
        case GLUT_KEY_CTRL_L:
        case GLUT_KEY_ALT_L:
        case GLUT_KEY_ALT_R:
        case GLUT_KEY_CTRL_R:
        case GLUT_KEY_SHIFT_L:
        case GLUT_KEY_SHIFT_R: activeKeyModifiers = 1;
    }
}

void releaseKey(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_CTRL_L:
        case GLUT_KEY_ALT_L:
        case GLUT_KEY_ALT_R:
        case GLUT_KEY_CTRL_R:
        case GLUT_KEY_SHIFT_L:
        case GLUT_KEY_SHIFT_R: activeKeyModifiers = 0;
    }
}

// not used!!
void handleSpecialKeypress(unsigned char key,int x,int y)
{

    // "special key" definition is very ambiguous
    int mod = glutGetModifiers();
    // if a modifiers button is pressed in this case (ctrl, alt or shift)
    // perform another set of action
    if (mod == GLUT_ACTIVE_CTRL || mod == GLUT_ACTIVE_SHIFT || mod == GLUT_ACTIVE_ALT)
    {
        switch(key)
        {
        case GLUT_KEY_LEFT:
            //y_rotation= 0.0;
            break;
        case GLUT_KEY_RIGHT:
            //y_rotation= 1.0;
            break;
        case GLUT_KEY_UP:
            //x_rotation= 1.0;
            break;
        case GLUT_KEY_DOWN:
            //x_rotation= 0.0;
            break;
        case GLUT_KEY_PAGE_UP:
            //z_rotation= 1.0;
            break;
        case GLUT_KEY_PAGE_DOWN:
            //z_rotation= 0.0;
            break;
        }
    }
    else
    {
        switch(key)
        {
        case GLUT_KEY_LEFT:
            y_rotation= 0.0;
            break;
        case GLUT_KEY_RIGHT:
            y_rotation= 1.0;
            break;
        case GLUT_KEY_UP:
            x_rotation= 1.0;
            break;
        case GLUT_KEY_DOWN:
            x_rotation= 0.0;
            break;
        case GLUT_KEY_PAGE_UP:
            z_rotation= 1.0;
            break;
        case GLUT_KEY_PAGE_DOWN:
            z_rotation= 0.0;
            break;
        }
    }

}

void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0) h = 1;
    if (w == 0) w = 1;
    float ratio =  w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    //gluPerspective(60.0, ratio, 1, 20.0);
    gluPerspective(60.0, ratio, 1, -1);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}


void initRendering()
{
    glEnable(GL_DEPTH_TEST);	// Depth testing must be turned on
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_CULL_FACE);
}

void drawStar(Star *star)
{
    glPushMatrix();
        glTranslated(star->x,star->y,star->z);
        if(showLabels) draw3DText(star->x,star->y+1.25*star->sphereModel.radius,star->z, star->name);
        glRotated(star->sphereModel.angle,0.0,1.0,0.0); // rotate around y axis of star

        // rotate to has right texture position
        glRotated(90.0,1.0,0.0,0.0); // rotate around x axis of star
        //glRotated(0.0,0.0,1.0,0.0); // rotate around y axis of star
        //glRotated(0.0,0.0,0.0,1.0); // rotate around z axis of star

        glColor3d(star->sphereModel.r, star->sphereModel.g, star->sphereModel.b);

        // case solid sphere
        //glutSolidSphere(star->sphereModel.radius,SPHERE_SLICE,SPHERE_STACKS);

        // draw textured sphere
        // when draw a star, it is not affected by the light!!!
        glDisable(GL_LIGHTING);
        GLUquadric *quad;
        quad = gluNewQuadric();
        glBindTexture(GL_TEXTURE_2D,star->sphereModel.textureId);
        gluQuadricTexture(quad,GL_TRUE);
        gluSphere(quad,star->sphereModel.radius,SPHERE_SLICE,SPHERE_STACKS);
        // re enable light
        glEnable(GL_LIGHTING);

        // STAR light
        glEnable(GL_LIGHT0);
        GLfloat light0_position[] = {0.0,0.0,0.0,star->light_intensity};
        GLfloat light0_ambient[] = {0.2,0.2,0.2,star->light_intensity};
        GLfloat light0_diffused[] = {1.0,1.0,1.0,star->light_intensity};
        GLfloat light0_specular[] = {1.0,1.0,1.0,star->light_intensity};
        glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffused);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    glPopMatrix();
}

void drawPlanet(Planet *planet)
{
    glPushMatrix();
        glTranslated(planet->star->x,planet->star->y,planet->star->z);
        glRotated(planet->angle,0.0,1.0,0.0); // rotate around y axis of planet's star
        glPushMatrix();
            //drawText(planet->x,planet->y+3*planet->sphereModel.radius,planet->z, planet->name);
            if(showLabels) draw3DText(planet->x,planet->y,planet->z, planet->name);
            glTranslated(planet->x,planet->y,planet->z);
            glRotated(planet->sphereModel.angle,0.0,1.0,0.0); // rotate around y axis of planet

            // rotate to has right texture position
            glRotated(90.0,1.0,0.0,0.0); // rotate around x axis of star
            //glRotated(0.0,0.0,1.0,0.0); // rotate around y axis of star
            //glRotated(0.0,0.0,0.0,1.0); // rotate around z axis of star

            glColor3d(planet->sphereModel.r, planet->sphereModel.g, planet->sphereModel.b);
            //glutSolidSphere(planet->sphereModel.radius,SPHERE_SLICE,SPHERE_STACKS);
            GLUquadric *quad;
            quad = gluNewQuadric();
            //glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,planet->sphereModel.textureId);
            gluQuadricTexture(quad,GL_TRUE);
            gluSphere(quad,planet->sphereModel.radius,SPHERE_SLICE,SPHERE_STACKS);
            // red dot, check rotation time
            //glColor3d(1.0,0.0,0.0);
            //glTranslated(planet->sphereModel.radius,0.0,0.0);
            //glutSolidSphere(0.1,SPHERE_SLICE,SPHERE_STACKS);
            // texture?
        glPopMatrix();
    glPopMatrix();
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glLoadIdentity();

    gluLookAt(	startX+deltaX, startY+deltaY, startZ+deltaZ, //camera pos
                0.0, 0.0,   0.0, //looking at
                0.0, 1.0,   0.0); //up orientation

    drawStar(&universe);
    drawStar(&sun);
    drawPlanet(&p1);
    drawPlanet(&p2);
    drawPlanet(&p3);
    drawPlanet(&p4);
    drawPlanet(&p5);
    drawPlanet(&p6);
    drawPlanet(&p7);
    drawPlanet(&p8);

    char time[10000];
    int int_hours = ceil(hours);
    int int_days = int_hours/24;
    int int_years = int_days/365;
    sprintf(time, "Time:\tY-%d\tD-%d\tH-%d", int_years, int_days%365, int_hours%24);
    draw2DText(1.0,GLUT_WINDOW_HEIGHT*1.89, time);

    char legend[10000];
    sprintf(legend, "\"ESC\" for exit, \"t\" for planet label, \"s\" for step animation, \"r\" for running animation, Mouse moves camera (wheel or ctrl \| shift \| alt for zoom) ");
    draw2DText(1.0, 1.0, legend);

    glFlush();
    glutSwapBuffers();
}

void draw2DText(double x, double y, char* text)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, GLUT_SCREEN_WIDTH, 0, GLUT_SCREEN_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING); //disable lighting during text drawing
    glDisable(GL_TEXTURE_2D); //disable texture during text drawing

    //draw text
    glColor3d(DEFAULT_FONT_R, DEFAULT_FONT_G, DEFAULT_FONT_B);
    void *font= DEFAULT_FONT;
    char c;
    int i;
    glRasterPos2d(x, y);

    for(i=0; i<strlen(text); i++)
    {
        c = text[i];
        glutBitmapCharacter(font, c);
    }
    //end draw text

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING); //enable lighting after text drawing
    glEnable(GL_TEXTURE_2D); //enable texture after text drawing
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void draw3DText(double x, double y, double z, char* text)
{
    glPushMatrix();
    glDisable(GL_LIGHTING); //disable lighting during text drawing
    glDisable(GL_TEXTURE_2D); //disable texture during text drawing
    glColor3d(DEFAULT_FONT_R, DEFAULT_FONT_G, DEFAULT_FONT_B);
    void *font= DEFAULT_FONT;
    char c;
    int i;
    glRasterPos3d(x, y, z);

    for(i=0; i<strlen(text); i++)
    {
        c = text[i];
        glutBitmapCharacter(font, c);
    }
    glEnable(GL_LIGHTING); //enable lighting after text drawing
    glEnable(GL_TEXTURE_2D); //enable texture after text drawing
    glPopMatrix();
}

void initModel()
{
    startX=0;
    startY= 500.0;
    startZ= -500.0;
    deltaZMax = -(startZ/2.0);
    deltaZMin = -10000.0;
    // not used
    deltaXMax = -500.0;
    deltaXMin = +500.0;
    deltaYMax = -500.0;
    deltaYMin = +500.0;
    // end not used
    showLabels = 0; //true
    isRunning = 1; //true

    // it's for background stars effect
    initStar(&universe,"universe", 18000.0,0.0,0.0,0.0,1000000.0);
    setStarColor(&universe, 1.0, 1.0, 1.0);
    setStarLight(&universe, 0.0);
    initRotatingTexturedSphere(&universe.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/8192x4096.png", GL_RGB);

    // add a star in this case sun
    // i make the sun really small cause i can't respect proportion
    // diam = 1391000km
    // tr = 27d 6h = ~650h (?)
    initStar(&sun,"SUN", 139.1000,0.0,0.0,0.0,650);
    setStarColor(&sun, 1.0, 1.0, 1.0);
    setStarLight(&sun, 1.0);
    initRotatingTexturedSphere(&sun.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/sun.jpg", GL_RGB);

    // add a planet in this case earth
    // diam 12756km
    // tr 24 h
    // tR 365 g
    // orbit 6.1 UA
    initPlanet(&p1, "Earth", &sun, 127.56, 610,0.0,0.0,24,365);
    setPlanetColor(&p1, 0.0, 1.0, 1.0);
    initRotatingTexturedSphere(&p1.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/earthmap1k.jpg", GL_RGB);

    // add a planet in this case Mercury
    // diam 4879km
    // tr 58g
    // tR 88g
    // orbit 4.5 UA
    initPlanet(&p2, "Mercury", &sun, 48.79, 450,0.0,0.0,58*24,88);
    setPlanetColor(&p2, 0.0, 1.0, 1.0);
    initRotatingTexturedSphere(&p2.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/mercurymap.jpg", GL_RGB);

    // add a planet in this case Venus
    // diam 12103km
    // tr 243g
    // tR 224g
    // orbit 2.4 UA
    initPlanet(&p3, "Venus", &sun, 12.103, 240,0.0,0.0,243*24,224);
    setPlanetColor(&p3, 0.0, 1.0, 1.0);
    initRotatingTexturedSphere(&p3.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/venusmap.jpg", GL_RGB);

    // add a planet in this case Mars
    // diam 6804km
    // tr 24h
    // tR 687g
    // orbit 9.5 UA
    initPlanet(&p4, "Mars", &sun, 6.804, 950,0.0,0.0,24,687);
    setPlanetColor(&p4, 0.0, 1.0, 1.0);
    initRotatingTexturedSphere(&p4.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/mars_1k_color.jpg", GL_RGB);

    // add a planet in this case Jupiter
    // diam 142984km
    // tr 10h
    // tR 4333g
    // orbit 32,67 UA
    initPlanet(&p5, "Jupiter", &sun, 142.984, 3267,0.0,0.0,9,4333);
    setPlanetColor(&p5, 0.0, 1.0, 1.0);
    initRotatingTexturedSphere(&p5.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/jupitermap.jpg", GL_RGB);

    // add a planet in this case Saturn
    // diam 120536km
    // tr 11h
    // tR 10756g
    // orbit 59,9 UA
    initPlanet(&p6, "Saturn", &sun, 120.536, 5990,0.0,0.0,11,10756);
    setPlanetColor(&p6, 0.0, 1.0, 1.0);
    initRotatingTexturedSphere(&p6.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/plutomap1k.jpg", GL_RGB); // da cambiare

    // add a planet in this case Uranus
    // diam 51118km
    // tr 17h
    // tR 42718 d
    // orbit 120,5 UA
    initPlanet(&p7, "Uranus", &sun, 51.118, 12050,0.0,0.0,17,42718);
    setPlanetColor(&p7, 0.0, 1.0, 1.0);
    initRotatingTexturedSphere(&p7.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/uranusmap.jpg", GL_RGB);

    // add a planet in this case Neptune
    // diam 49528km
    // tr 16h
    // tR 60233g
    // orbit 189 UA
    initPlanet(&p8, "Neptune", &sun, 49.528, 18900,0.0,0.0,16,60233);
    setPlanetColor(&p8, 0.0, 1.0, 1.0);
    initRotatingTexturedSphere(&p8.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/neptunemap.jpg", GL_RGB);

    // add another planet in this case mars?
    // GIOVUS has a day of 12 hours, but has a year of 730 "giovus days",
    // so a GIOVUS year is equal to a earth year
    initPlanet(&p2, "MARS", &sun, 2, 25.0,0.0,0.0,12,365*2);
    setPlanetColor(&p2, 1.0, 0.8, 0.7);
    initRotatingTexturedSphere(&p2.sphereModel, "/home/mellowonpsx/Documents/DIP SVDRV/Project/SVDRV_as02/image/mars_1k_color.jpg", GL_RGB);
}

void idleScene()
{
    if(isRunning) hours += TIME_STEP;

    // indipendentemente
    updateStarPosition(&universe, hours);
    updateStarPosition(&sun, hours);
    updatePlanetPosition(&p1, hours);
    updatePlanetPosition(&p2, hours);
    updatePlanetPosition(&p3, hours);
    updatePlanetPosition(&p4, hours);
    updatePlanetPosition(&p5, hours);
    updatePlanetPosition(&p6, hours);
    updatePlanetPosition(&p7, hours);
    updatePlanetPosition(&p8, hours);
    drawScene();
}

void mouseMove(int x, int y)
{
    // this will only be true when the left button is down
    if (xOrigin >= 0)
    {
        // don't like this but is what i have
        if(activeKeyModifiers)
        {
             deltaZ = -(y - yOrigin)*DEFAULT_DELTA_FRACTION;
        }
        else
        {
            deltaX = (x - xOrigin)*DEFAULT_DELTA_FRACTION;
            deltaY = (y - yOrigin)*DEFAULT_DELTA_FRACTION;
        }
    }
}

void mouseButton(int button, int state, int x, int y)
{
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON)
    {
        // when the button is released
        if (state == GLUT_UP)
        {
            xOrigin = -1;
            yOrigin = -1;
        }
        else
        {
            // state = GLUT_DOWN
            xOrigin = x;
            yOrigin = y;
        }
    }
    // Wheel reports as button 3(scroll up) and button 4(scroll down)
    if (button == 3) // It's a wheel event
    {
        if(state == GLUT_DOWN)
            if(deltaZ <= deltaZMax)
            {
                deltaZ+= DEFAULT_WEEL_STEP;
            }
    }
    if (button == 4)
    {
        if(state == GLUT_DOWN)
            if(deltaZ >= deltaZMin)
            {
                deltaZ-= DEFAULT_WEEL_STEP;
            }
    }
    //deltaY= -deltaZ;
}
*/
