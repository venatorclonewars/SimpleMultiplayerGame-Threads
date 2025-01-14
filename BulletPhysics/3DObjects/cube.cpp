#include "cube.h"

Cube::Cube(const Vector3f& position, bool isRigidBody, btDiscreteDynamicsWorld* dynamicsWorld, const Vector3f& lightDir)
{
    m_technique = new ObjectTechnique();
    if (!m_technique->init())
        exit(1);

    m_technique->setLightDir(lightDir);
    m_lightDir = lightDir;

    m_dynamicsWorld = dynamicsWorld;
    transform = position;
    setPosition(position);

   // Lightweight version - bad for lighting
   /* m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, 0.5f)));
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, -0.5f)));
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, 0.5f)));
    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, -0.5f)));
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, -0.5f)));
    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, -0.5f)));
    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, 0.5f)));
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, 0.5f)));*/



    /*m_indices = 
    {
        0, 1, 2,
        1, 3, 4,
        5, 6, 3,
        7, 3, 6,
        2, 4, 7,
        0, 7, 6,
        0, 5, 1,
        1, 5, 3,
        5, 0, 6,
        7, 4, 3,
        2, 1, 4,
        0, 2, 7
    };*/

    // Define vertices with positions and normals
    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f)));  // Right face
    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f))); // Right face
    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f))); // Right face
    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f)));  // Right face

    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f))); // Left face
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f))); // Left face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f))); // Left face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f))); // Left face

    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f)));  // Top face
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f))); // Top face
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f))); // Top face
    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f)));  // Top face

    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f))); // Bottom face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f))); // Bottom face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f))); // Bottom face
    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f))); // Bottom face

    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f))); // Front face
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f))); // Front face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f))); // Front face
    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f)));  // Front face

    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(0.0f, 0.0f, 1.0f)));  // Back face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(0.0f, 0.0f, 1.0f))); // Back face
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(0.0f, 0.0f, 1.0f)));  // Back face
    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(0.0f, 0.0f, 1.0f)));   // Back face

    m_indices =
    {
         0, 1, 2, 2, 3, 0,   // Right face
        4, 5, 6, 6, 7, 4,   // Left face
        8, 9, 10, 10, 11, 8, // Top face
        12, 13, 14, 14, 15, 12, // Bottom face
        16, 17, 18, 18, 19, 16, // Front face
        20, 21, 22, 22, 23, 20  // Back face
    };


    m_isRigidBody = isRigidBody;

    if (isRigidBody)
        createRigidBody();

    createGLState();
    populateBuffers();

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Cube::Cube(const Vector3f& position, const Vector3f& lightDir)
{
    m_technique = new ObjectTechnique();
    if (!m_technique->init()) 
    {
        printf("ObjectTechnique initialization failed!");
        exit(1);
    }

    m_technique->setLightDir(lightDir);
    m_lightDir = lightDir;

    transform = position;
    setPosition(position);

     // Define vertices with positions and normals
    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f)));  // Right face
    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f))); // Right face
    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f))); // Right face
    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f)));  // Right face

    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f))); // Left face
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f))); // Left face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f))); // Left face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f))); // Left face

    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f)));  // Top face
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f))); // Top face
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f))); // Top face
    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f)));  // Top face

    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f))); // Bottom face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f))); // Bottom face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f))); // Bottom face
    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f))); // Bottom face

    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f))); // Front face
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f))); // Front face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f))); // Front face
    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f)));  // Front face

    m_vertices.push_back(Vert(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(0.0f, 0.0f, 1.0f)));  // Back face
    m_vertices.push_back(Vert(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(0.0f, 0.0f, 1.0f))); // Back face
    m_vertices.push_back(Vert(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(0.0f, 0.0f, 1.0f)));  // Back face
    m_vertices.push_back(Vert(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(0.0f, 0.0f, 1.0f)));   // Back face

    m_indices =
    {
         0, 1, 2, 2, 3, 0,   // Right face
        4, 5, 6, 6, 7, 4,   // Left face
        8, 9, 10, 10, 11, 8, // Top face
        12, 13, 14, 14, 15, 12, // Bottom face
        16, 17, 18, 18, 19, 16, // Front face
        20, 21, 22, 22, 23, 20  // Back face
    };


    m_isRigidBody = false;

    createGLState();
    populateBuffers();

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Cube::createRigidBody()
{
    btCollisionShape* fallShape = new btBoxShape(btVector3(0.5, 0.5, 0.5));  // Cube of size 2x2x2
    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(transform.x, transform.y, transform.z)));  // Initial position (0, 10, 0)
    btScalar mass = 1.0f;

    btVector3 fallInertia(0, 0, 0);
    fallShape->calculateLocalInertia(mass, fallInertia);

    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
    m_rigidBody = new btRigidBody(fallRigidBodyCI);
    m_dynamicsWorld->addRigidBody(m_rigidBody);
}

void Cube::updateRigidBody()
{
    btTransform worldTransform;
    m_objectTransform.setIdentity();

    m_rigidBody->getMotionState()->getWorldTransform(worldTransform);

    m_objectTransform.setTranslation(worldTransform.getOrigin());
    m_objectTransform.setQuaternion(worldTransform.getRotation());

}

void Cube::render(const Matrix4f& WVP, const Matrix4f& modelMatrix)
{
    glBindVertexArray(m_VAO);
    //IF using lightweight remove this
    glDisable(GL_CULL_FACE);

    m_technique->enable();
    m_technique->setWVP(WVP);
    m_technique->setLightDir(m_lightDir);
    m_technique->setModelMatrix(modelMatrix);

    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

    glEnable(GL_CULL_FACE);

    glBindVertexArray(0);
}

void Cube::update(const Matrix4f& WVP, const Matrix4f& modelMatrix)
{
    if (m_isRigidBody)
        updateRigidBody();

    render(WVP, modelMatrix);
}

void Cube::createGLState()
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

    int POS_LOC = 0;
    int NORM_LOC = 1;

    size_t numFloats = 0;

    glEnableVertexAttribArray(POS_LOC);
    glVertexAttribPointer(POS_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (const void*)(numFloats * sizeof(float)));
    numFloats += 3;
    glEnableVertexAttribArray(NORM_LOC);
    glVertexAttribPointer(NORM_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (const void*)(numFloats * sizeof(float)));
    numFloats += 3;

}

void Cube::populateBuffers()
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
}

Matrix4f& Cube::getTransform()
{

    return m_objectTransform;
}

void Cube::setPosition(const Vector3f& position)
{
    m_objectTransform.setTranslation(position);
}
