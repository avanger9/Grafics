#include "modelInfo1.h"

void ModelInfo1::onPluginLoad()
{
  glwidget()->makeCurrent();
  int nObjectes    = 0;
  int nPoligons    = 0;
  int nVertexs     = 0;
  int nTriangles   = 0;
  
  // tractament de l'escena
  Scene* scn = scene();
  nObjectes  = scn->objects().size();
  for (int i = 0; i < nObjectes; i++){
    Object& obj = scn->objects()[i];
    int nPolObj = obj.faces().size();
    nPoligons   = nPoligons + nPolObj;
    for (int j = 0; j < nPolObj; j++){ 
      Face cara     = obj.faces()[j];
      int nVertices = cara.numVertices();
      nVertexs      = nVertexs + nVertices;
      if (nVertexs == 3) nTriangles = nTriangles + 1;
    }
  }
  float propTriangles = nTriangles / nPoligons * 200;

  cout << "n objectes: " << nObjectes << endl;
  cout << "n poligons: " << nPoligons << endl;
  cout << "n vertexs:  " << nVertexs << endl;
  cout << "Proporcio triangles : " << propTriangles << endl;

}

void ModelInfo1::postFrame() 
{
  
 
}



