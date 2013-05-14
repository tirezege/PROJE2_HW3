//
//  NormalShaderNode.h
//  Ders 7
//
//  Created by Gurel Erceis on 4/1/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef NormalShaderNode_h
#define NormalShaderNode_h
#include <windows.h>
#include "Camera.h"
#include "ShadedGeometry.h"

class NormalShaderNode: public ShadedGeometry{
public:
	GLuint frameCount;
    NormalShaderNode(char *filename):
    ShadedGeometry(filename,
                   "fresnel.vert",
                   "fresnel.frag")
    {
        generateBuffers();    
    }
    ~NormalShaderNode(){
        
    }
    void draw(SceneNode *camera){

		frameCount++;
        glUseProgram(programId);
        
        glm::mat4 MVPmatrix = ((Camera*)camera)->projectionMatrix * camera->getInverseModelMatrix() * getModelMatrix();
        
        glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVPmatrix[0][0]);
        
		glm::mat4 MVmatrix = camera->getInverseModelMatrix() *  getModelMatrix();
        
		glUniformMatrix4fv(UniformMV, 1, GL_FALSE, &MVmatrix[0][0]);

		glUniform1f(UniformColor, frameCount/1000.f );

        // vertex bufferi bagla
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // normal buffer i bagla
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // indiceleri bagla
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);
        
        // Attributelari enable et
        glEnableVertexAttribArray(AttributePosition);
        glEnableVertexAttribArray(AttributeNormal);
        
        // ciz
        glDrawElements(GL_TRIANGLES, int(faceArray.size()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
        
        
        // baglantilari kopar
        glDisableVertexAttribArray(AttributeNormal);
        glDisableVertexAttribArray(AttributePosition);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        
        glUseProgram(0);
    }
private:
    GLuint UniformMVP, UniformMV, UniformColor;
    GLuint AttributePosition,AttributeNormal;
    
    
    void generateBuffers(){
        
        UniformMVP = glGetUniformLocation(programId, "MVP");
        printf("UniformMVP: %d\n",UniformMVP);

		UniformMV = glGetUniformLocation(programId, "ModelView");
        printf("UniformMV: %d\n",UniformMV);
        
        AttributePosition = glGetAttribLocation(programId, "Position");
        printf("Position Attribute: %d\n", AttributePosition);
        
        AttributeNormal = glGetAttribLocation(programId, "Normal");
        printf("Normal Attribute: %d\n", AttributeNormal);
        
		UniformColor = glGetUniformLocation(programId, "color");
        printf("UniformColor: %d\n",UniformColor);
    }
};

#endif
