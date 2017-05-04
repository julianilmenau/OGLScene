#include "res/drawable/header/unitcube.h"

#include <iterator>
#include <algorithm>

std::array<QVector3D, 8> UnitCube::vertices()
{
   return std::array<QVector3D, 8>{{
       QVector3D(-1, -1,  1)
   ,   QVector3D( 1, -1,  1)
   ,   QVector3D( 1,  1,  1)
   ,   QVector3D(-1,  1,  1)
   ,   QVector3D(-1, -1, -1)
   ,   QVector3D( 1, -1, -1)
   ,   QVector3D( 1,  1, -1)
   ,   QVector3D(-1,  1, -1)
   }};
}

std::array<UnitCube::Face, 12> UnitCube::indices()
{
   return std::array<Face, 12>{{
       Face{{ 0, 1, 2 }}
   ,   Face{{ 2, 3, 0 }}
   ,   Face{{ 3, 2, 6 }}
   ,   Face{{ 6, 7, 3 }}
   ,   Face{{ 7, 6, 5 }}
   ,   Face{{ 5, 4, 7 }}
   ,   Face{{ 4, 5, 1 }}
   ,   Face{{ 1, 0, 4 }}
   ,   Face{{ 4, 0, 3 }}
   ,   Face{{ 3, 7, 4 }}
   ,   Face{{ 1, 5, 6 }}
   ,   Face{{ 6, 2, 1 }}
   }};
}

UnitCube::UnitCube()
{

}


UnitCube::~UnitCube()
{

   m_vertexBuffer.destroy();
   m_colorBuffer.destroy();
   m_normalBuffer.destroy();

}

void UnitCube::initialize(QOpenGLShaderProgram  *program)
{
   static auto v(vertices());

   std::vector<QVector3D> vertices(36);
   std::vector<QVector3D> normals(36);

   int i = 0;
   for (const Face & face : indices())
   {
       vertices[i] = v[face[0]];
       vertices[i+1] = v[face[1]];
       vertices[i+2] = v[face[2]];

       QVector3D v0 = vertices[i+1] - vertices[i];
       QVector3D v1 = vertices[i+2] - vertices[i];

       QVector3D normal = QVector3D::crossProduct(v0, v1).normalized();

       normals[i] = normal;
       normals[i+1] = normal;
       normals[i+2] = normal;

       i += 3;
   }


   QString subDirPath = "data/cube/";

   m_transform.translate(0.0f,0.0f,0.0f);


   std::vector<QVector3D> colors = vertices;

   program->addShaderFromSourceFile(QOpenGLShader::Vertex, subDirPath+"vertexshader.vsh");
   program->addShaderFromSourceFile(QOpenGLShader::Fragment, subDirPath+"fragmentshader.fsh");
   program->link();

   QString extension = ".png";
   QString texturePaths[6]= {"posx"+extension,
                             "negx"+extension,
                             "posy"+extension,
                             "negy"+extension,
                             "posz"+extension,
                             "negz"+extension};


   m_textures.append(new QOpenGLTexture(QOpenGLTexture::TargetCubeMap));
   QOpenGLTexture *texture=m_textures[0];
   texture->create();
   texture->bind();
   texture->setSize(2048,2048);
   texture->setFormat(QOpenGLTexture::RGBAFormat);
   texture->allocateStorage();
   texture->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);



   for ( i=0;i<6;i++) {
       QImage face;
       QString path=subDirPath+texturePaths[i];
       if (!face.load(path)) {
           qDebug()<<"couldnt load face: "<<i<<" at: "<<path;
       } else {
           texture->setData(0,0,static_cast<QOpenGLTexture::CubeMapFace>(0x8515+i),QOpenGLTexture::BGRA,QOpenGLTexture::UInt8,(void*)face.bits());
       }

   }
   texture->release();


   m_vertexBuffer.create();
   m_vertexBuffer.bind();
   m_vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   m_vertexBuffer.allocate(vertices.data(),vertices.size()*sizeof(QVector3D));

   m_vao.create();
   m_vao.bind();


   program->enableAttributeArray(0);
   program->setAttributeBuffer(0,GL_FLOAT,0,3,0);


   m_colorBuffer.create();
   m_colorBuffer.bind();
   m_colorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   m_colorBuffer.allocate(colors.data(),colors.size()*sizeof(QVector3D));


   program->enableAttributeArray(1);
   program->setAttributeBuffer(1,GL_FLOAT,0,3,0);



   m_vertexBuffer.release();
   m_colorBuffer.release();
   m_vao.release();
   program->release();

}

void UnitCube::draw(QOpenGLFunctions & functions)
{
   draw(GL_TRIANGLES, functions);
}

void UnitCube::draw(const GLenum mode, QOpenGLFunctions & functions)
{
   m_vao.bind();
   m_textures[0]->bind(0);

   functions.glDrawArrays(mode, 0, 36);
}

