#include "res/drawable/header/floor.h"

void Floor::genGrid() {
    for (int i=0;i<this->width;i++) {
        for (int j=0;j<this->height;j++) {
            grid[i][j]=0;
        }
    }
}

Floor::Floor(int gwidth,int gheight) {
    this->width=gwidth;
    this->height=gheight;

    for (int i=0;i<gwidth;i++) {
        QVector<float> temp=QVector<float>(gheight);
        grid.append(temp);
    }
    Floor::genGrid();
}


void Floor::initialize(QOpenGLShaderProgram  *program)
{

   QString subDirPath = "data/floor/";

   m_transform.translate(0.0f,0.0f,0.0f);

   QVector<QVector3D> vertices;

   for (int i=0;i<this->width-1;i++) {
       for (int j=0;j<this->height-1;j++) {
           vertices.append(QVector3D(i,grid[i][j],j));
           vertices.append(QVector3D(i,grid[i][j+1],j+1));
           vertices.append(QVector3D(i+1,grid[i+1][j+1],j+1));
           vertices.append(QVector3D(i,grid[i][j],j));
           vertices.append(QVector3D(i+1,grid[i+1][j+1],j+1));
           vertices.append(QVector3D(i+1,grid[i+1][j],j));
       }
   }


   QString extension = ".jpg";
   QString texturePath = "texture";

   m_textures.append(new QOpenGLTexture(QOpenGLTexture::Target2D));
   QOpenGLTexture *ftexture=m_textures[0];
   ftexture->create();
   ftexture->bind();
   ftexture->setSize(2048,2048);
   ftexture->setFormat(QOpenGLTexture::RGBAFormat);
   ftexture->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::LinearMipMapLinear);
   ftexture->generateMipMaps();
   ftexture->allocateStorage();
   QImage tex;
   ftexture->setWrapMode(QOpenGLTexture::MirroredRepeat);

   if (!tex.load(subDirPath+texturePath+extension)) {
       qDebug()<<"Couldnt load Texture";
   }

   ftexture->setData(tex);

   program->addShaderFromSourceFile(QOpenGLShader::Vertex, subDirPath+"vertexshader.vsh");
   program->addShaderFromSourceFile(QOpenGLShader::Fragment, subDirPath+"fragmentshader.fsh");
   program->link();


   m_vertexBuffer.create();
   m_vertexBuffer.bind();
   m_vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   m_vertexBuffer.allocate(vertices.data(),vertices.size()*sizeof(QVector3D));

   m_vao.create();
   m_vao.bind();


   program->enableAttributeArray(0);
   program->setAttributeBuffer(0,GL_FLOAT,0,3,0);



   m_vertexBuffer.release();
   m_vao.release();
   program->release();

}

void Floor::draw(QOpenGLFunctions & functions)
{
   draw(GL_TRIANGLES, functions);
}

void Floor::draw(const GLenum mode, QOpenGLFunctions & functions)
{
   m_vao.bind();
   m_textures[0]->bind();

   functions.glDrawArrays(mode, 0, 6*(width-1)*(height-1));
}




