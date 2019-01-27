#include "reflection.h"
#include "glwidget.h"

#include <QCoreApplication>

const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = 1024;

void Reflection::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("reflection.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("reflection.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    // Setup texture
    g.glActiveTexture(GL_TEXTURE0);
    g.glGenTextures( 1, &textureId);
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		      GL_LINEAR_MIPMAP_LINEAR );
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT,
		   0, GL_RGB, GL_FLOAT, NULL);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    // Resize to power-of-two viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);
}

void Reflection::resizeEvent(QResizeEvent *e){
    cout << e->size().width() << " " << e->size().height() << endl;
}

void drawRect(GLWidget &g)
{
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;
        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        // Create VBO with (x,y,z) coordinates
        float coords[] = { -1, -1, 0, 
                            1, -1, 0, 
                           -1,  1, 0, 
                            1,  1, 0};

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}

void Reflection::drawQuad(const Point& p0, const Point& p1, const Point& p2, const Point& p3)
{
    static bool created = false;
    static GLuint VAO_rect;
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        // Create VBO with (x,y,z) coordinates
        float coords[] = { p0.x(), p0.y(), p0.z(), p1.x(), p1.y(), p1.z(), p3.x(), p3.y(), p3.z(), p2.x(), p2.y(), p2.z() };

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        //glBindVertexArray(0);

        float normals[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0};

        GLuint VBO_normals;
        g.glGenBuffers(1, &VBO_normals);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
        g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(1);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray(VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}


bool Reflection::paintGL()
{
    GLWidget & g = *glwidget();
    //Pas 1:

    //Definim el color amb el que rentarem els buffers
    g.glClearColor(1,1,1,1);
    
    //Rentem els buffers
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    //Definim la modelViewProjectionMatrix
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    
    //Definim la modelViewProjectionMatrix per a invertir les y
    QMatrix4x4 MVPP = MVP;

    //Invertim la y i translladem l'objecte a l'origen
    MVPP.scale(1,-1,1);
    MVPP.translate(0,-(scene()->boundingBox().min().y()*2),0);

    //Assignem la MVPP al shader per defecte i dibuixem el reflex
    g.defaultProgram()->setUniformValue("modelViewProjectionMatrix", MVPP ); 
    if (drawPlugin()) drawPlugin()->drawScene();

    //Obtenim una textura de la escena dibuixada i la assignem a la texturaId 0
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,
              IMAGE_WIDTH, IMAGE_HEIGHT);
    g.glGenerateMipmap(GL_TEXTURE_2D);

    //Tornem a rentar els buffers amb el mateix color
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    //Assignem el nostre programa i enviem uniforms
    program->bind();
    program->setUniformValue("colorMap", 0);
    program->setUniformValue("SIZE", float(IMAGE_WIDTH));  

    //Notar que aquesta matriu es la MVP normal
    program->setUniformValue("modelViewProjectionMatrix", MVP );  

    //Dibuixem el planol en el que "projectarem" el reflex
    Point min = scene()->boundingBox().min();
    float r = scene()->boundingBox().radius();
    drawQuad(Point(-r,min.y(), r), Point( r,min.y(), r),
       Point( r,min.y(),  -r), Point(-r,min.y(), -r));

    //Restaurem el programa per defecte i li asignem la MVP normal per dibuixar l'objecte
    g.defaultProgram()->bind();
    g.defaultProgram()->setUniformValue("modelViewProjectionMatrix", MVP ); 
    if (drawPlugin()) drawPlugin()->drawScene();
    
    g.glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

