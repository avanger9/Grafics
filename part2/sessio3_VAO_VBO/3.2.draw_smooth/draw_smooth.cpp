#include "draw_smooth.h"
#include "glwidget.h"
#include <cmath>

void Draw_smooth::cleanUp() 
{
	GLWidget &g = *glwidget();	
	g.glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
	g.glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
	g.glDeleteBuffers(indexBuffers.size(),  &indexBuffers[0]);
	g.glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
	g.glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);

	g.glDeleteVertexArrays(VAOs.size(), &VAOs[0]);

	coordBuffers.clear();
	normalBuffers.clear();
	indexBuffers.clear();
	stBuffers.clear();
	colorBuffers.clear();
	VAOs.clear();

	numIndices.clear(); 
}

void Draw_smooth::onSceneClear() {
	cleanUp();
}

void Draw_smooth::onPluginLoad()
{
	for (unsigned int i=0; i<scene()->objects().size(); ++i)
		addVBO(i);
}

void Draw_smooth::onObjectAdd()
{
	addVBO(scene()->objects().size()-1);	
}

void Draw_smooth::addVBO(unsigned int currentObject)
{
	vector<float> vertices; // (x,y,z)    Final size: 3*number of corners
	vector<float> normals;  // (nx,ny,nz) Final size: 3*number of corners
	vector<float> st;       // (s,t)      Final size: 2*number of corners  
	vector<float> colors;   // (r,g,b)    Final size: 3*number of corners
	vector<int> indices;    //            Final size: 3*number of triangles  
  
  // V'=V. Això implica que cada vèrtex (x,y,z) apareix un sol cop al VBO (sense repetits), amb una única normal.
  // Per tant, totes les cares que fan servir aquest vèrtex el rebran amb la mateixa normal.
  // El mateix s’aplica a la resta d’atributs (color i coordenades de textura)
	const Object &obj=scene()->objects()[currentObject];
	const vector<Vertex> &verts=obj.vertices();
	const vector<Face> &faces=obj.faces();
	// fem que la normal d'un vertex sigui la mitja de les normals de les cares on surt aquest vertex
	vector<Vector> VN(obj.vertices().size(), Vector(0,0,0));    // suma de les normals de les diferents cares on apareixen els vertex
	vector<int> VC(obj.vertices().size(), 0);                   // conte de les normals de les diferents cares on apareixen els vertex
	for (int i=0; i<(int)faces.size(); ++i) {
	    const Face &face=faces[i];
	    const Vector &N=face.normal().normalized();
	    for (int j=0; j<(int)face.numVertices(); ++j) {
	    	VN[face.vertexIndex(j)]+=N; 
	    	++VC[face.vertexIndex(j)];
	    }
	}
  // els vertex i demes nomes apareixen 1 cop al VBO
	for (int i=0; i<(int)verts.size(); ++i) {
	    Vector N=VN[i]/VC[i];
	    const Point &P=verts[i].coord();
	    vertices.push_back(P.x()); vertices.push_back(P.y()); vertices.push_back(P.z());
	    normals.push_back(N.x()); normals.push_back(N.y()); normals.push_back(N.z());
	    float r=obj.boundingBox().radius();
	    float s=Vector::dotProduct((1.0/r)*Vector(1,0,1), P);
	    float t=Vector::dotProduct((1.0/r)*Vector(0,1,0), P);
	    if ((int)verts.size()==81) {    // plane: special case for /assig models
			s=0.5f*(P.x()+1.0);
			t=0.5f*(P.y()+1.0);
	    }
	    if ((int)verts.size()==386) {   // cube: special case for /assig models
			s=Vector::dotProduct((1.0/2.40)*Vector(1,0,1), P);
			t=Vector::dotProduct((1.0/2.0)*Vector(0,1,0), P);
	    }
	    st.push_back(s);
	    st.push_back(t);
	    colors.push_back(abs(N.x()));
	    colors.push_back(abs(N.y()));
	    colors.push_back(abs(N.z()));
	}
  // els index els hem de posar en ordre, pero
	for (int i=0; i<(int)faces.size(); ++i) {
		const Face &face=faces[i];
		for (int j=0; j<(int)face.numVertices(); ++j) 
			indices.push_back(face.vertexIndex(j));
	}

	// Step 2: Create empty buffers (coords, normals, st, indices)
	GLWidget &g = *glwidget();
	GLuint VAO;
	g.glGenVertexArrays(1, &VAO);
	VAOs.push_back(VAO);
	g.glBindVertexArray(VAO);

	GLuint coordBufferID;
	g.glGenBuffers(1, &coordBufferID);
	coordBuffers.push_back(coordBufferID);

	GLuint normalBufferID;
	g.glGenBuffers(1, &normalBufferID);
	normalBuffers.push_back(normalBufferID);

	GLuint colorBufferID;
	g.glGenBuffers(1, &colorBufferID);
	colorBuffers.push_back(colorBufferID);

	GLuint stBufferID;
	g.glGenBuffers(1, &stBufferID);
	stBuffers.push_back(stBufferID);

	GLuint indexBufferID;
	g.glGenBuffers(1, &indexBufferID);
	indexBuffers.push_back(indexBufferID);

	numIndices.push_back(indices.size());

	// Step 3: Define VBO data (coords, normals, indices)
	g.glBindBuffer(GL_ARRAY_BUFFER, coordBuffers[currentObject]);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
	g.glEnableVertexAttribArray(0);

	g.glBindBuffer(GL_ARRAY_BUFFER, normalBuffers[currentObject]);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
	g.glEnableVertexAttribArray(1);

	g.glBindBuffer(GL_ARRAY_BUFFER, colorBuffers[currentObject]);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
	g.glEnableVertexAttribArray(2);

	g.glBindBuffer(GL_ARRAY_BUFFER, stBuffers[currentObject]);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*st.size(), &st[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
	g.glEnableVertexAttribArray(3);

	g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[currentObject]);
	g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);

	g.glBindVertexArray(0);
	g.glBindBuffer(GL_ARRAY_BUFFER,0);
	g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

bool Draw_smooth::drawScene()
{
	GLWidget &g = *glwidget();
	for (unsigned int i=0; i<coordBuffers.size(); ++i)  {   // for each buffer (that is, for each object)
		g.glBindVertexArray(VAOs[i]);
		g.glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*) 0);
	}
	g.glBindVertexArray(0);
	return true;
}

bool Draw_smooth::drawObject(int i)
{
	GLWidget &g = *glwidget();
	g.glBindVertexArray(VAOs[i]);
	g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[i]);
	g.glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*) 0);

	g.glBindVertexArray(0);
	g.glBindBuffer(GL_ARRAY_BUFFER,0);
	g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	return true;
}

