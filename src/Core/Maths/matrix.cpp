#include "matrix.hpp"
#include "assert.h"

using namespace Core::Maths;

Mat4::Mat4()
{
}

Mat4::~Mat4()
{
}

Mat4 Mat4::GetIdentityMatrix()
{
    Mat4 identity;

    identity.array[0]  = 1;
    identity.array[5]  = 1;
    identity.array[10] = 1;
    identity.array[15] = 1;

    return identity;
}

Mat4 operator+(const Mat4 &matrix1, const Mat4 &matrix2)
{
    Mat4 result;

    for (unsigned i = 0; i < 16 ; i++)
    {
        result.array[i] = matrix1.array[i] + matrix2.array[i];
    }

    return result;
}

Mat4 operator*(const Mat4 &matrix1, const Mat4 &matrix2)
{
    Mat4 result;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                result.array[i + j * 4] += matrix1.array[i + k * 4] * matrix2.array[k + j * 4];
            }
        }
    }
    return result;
}

Vec4 operator*(const Mat4 &matrix, const Vec4 &vect)
{
    Vec4 result;

    result.x = vect.x * matrix.array[0] + vect.y * matrix.array[1] + vect.z * matrix.array[2] + vect.w * matrix.array[3];
    result.y = vect.x * matrix.array[4] + vect.y * matrix.array[5] + vect.z * matrix.array[6] + vect.w * matrix.array[7];
    result.z = vect.x * matrix.array[8] + vect.y * matrix.array[9] + vect.z * matrix.array[10] + vect.w * matrix.array[11];
    result.w = vect.x * matrix.array[12] + vect.y * matrix.array[13] + vect.z * matrix.array[14] + vect.w * matrix.array[15];

    return result;
}

Mat4 operator*(const Mat4 &matrix, const float &multpliyer)
{
    Mat4 result;

    for (unsigned int i = 0 ; i < 16 ; i++)
    {
        result.array[i] = matrix.array[i] * multpliyer;
    }

    return result;
}

Mat4 Mat4::CreateTranslationMatrix(const Vec3 &translation)
{
    Mat4 translateMatrix;
    translateMatrix.array[0] = 1;
    translateMatrix.array[12] = translation.x;
    translateMatrix.array[5] = 1;
    translateMatrix.array[13] = translation.y;
    translateMatrix.array[10] = 1;
    translateMatrix.array[14] = translation.z;
    translateMatrix.array[15] = 1;
    return translateMatrix;
}

Mat4 Mat4::CreateScaleMatrix(const Vec3 &scale)
{

    Mat4 scaleMatrix;
    scaleMatrix.array[0] = scale.x;
    scaleMatrix.array[5] = scale.y;
    scaleMatrix.array[10] = scale.z;
    scaleMatrix.array[15] = 1;

    return scaleMatrix;
}

Mat4 Mat4::CreateXRotationMatrix(float angle)
{
    Mat4 rotationXMatrix;
    rotationXMatrix.array[0] = 1;
    rotationXMatrix.array[5] = cos(angle);
    rotationXMatrix.array[9] = -sin(angle);
    rotationXMatrix.array[6] = sin(angle);
    rotationXMatrix.array[10] = cos(angle);
    rotationXMatrix.array[15] = 1;

    return rotationXMatrix;
}

Mat4 Mat4::CreateYRotationMatrix(float angle)
{
    Mat4 rotationYMatrix;
    rotationYMatrix.array[0] = cos(angle);
    rotationYMatrix.array[8] = sin(angle);
    rotationYMatrix.array[5] = 1;
    rotationYMatrix.array[2] = -sin(angle);
    rotationYMatrix.array[10] = cos(angle);
    rotationYMatrix.array[15] = 1;

    return rotationYMatrix;
}

Mat4 Mat4::CreateZRotationMatrix(float angle)
{
    Mat4 rotationZMatrix;
    rotationZMatrix.array[0] = cos(angle);
    rotationZMatrix.array[4] = -sin(angle);
    rotationZMatrix.array[1] = sin(angle);
    rotationZMatrix.array[5] = cos(angle);
    rotationZMatrix.array[10] = 1;
    rotationZMatrix.array[15] = 1;

    return rotationZMatrix;
}

Mat4 Mat4::CreateFixedAngleEulerRotationMatrix(const Vec3 &angle)
{
    Mat4 rotationMatrix = Mat4::CreateYRotationMatrix(angle.y) *
                          Mat4::CreateXRotationMatrix(angle.x) *
                          Mat4::CreateZRotationMatrix(angle.z);
                          

    return rotationMatrix;
}

Mat4 Mat4::CreateRotationAroundAxeMatrix (const Vec3 &axe, float angle)
{
    Mat4 first;

    first.array[0]  = axe.x * axe.x;
    first.array[1]  = axe.y * axe.x;
    first.array[2]  = axe.z * axe.x;

    first.array[4]  = axe.x * axe.y;
    first.array[5]  = axe.y * axe.y;
    first.array[6]  = axe.z * axe.y;

    first.array[8]  = axe.x * axe.z;
    first.array[9]  = axe.y * axe.z;
    first.array[10] = axe.z * axe.z;

    first.array[15] = 1;

    first = first * (1 - cos(angle));

    Mat4 second = GetIdentityMatrix() * cos(angle);

    Mat4 third;

    third.array[1] = axe.z;
    third.array[2] = -axe.y;
    third.array[4] = -axe.z;
    third.array[6] = axe.x;
    third.array[8] = axe.y;
    third.array[9] = -axe.x;

    third = third * sin(angle);

    return first + second + third;

}

Mat4 Mat4::CreateTransformMatrix(const Vec3 &rotation, const Vec3 &position, const Vec3 &scale)
{
    Mat4 matrixTRS = CreateTranslationMatrix(position) *
                     CreateFixedAngleEulerRotationMatrix(rotation) *
                     CreateScaleMatrix(scale);

    return matrixTRS;
}

Mat4 Mat4::CreatePerspectiveProjectionMatrix(int width, int height, float near, float far, float fov)
{
    Mat4 projection;
    float yMax = tanf(fov * M_PI / 360);
    float xMax = yMax * ((float)width / height);

    projection.array[0] = 1 / xMax;

    projection.array[5] = 1 / yMax;

    projection.array[10] = - (float)(near + far) / (far - near);
    projection.array[11] = - 1;

    projection.array[14] = - (float)(2 * far * near) / (far - near);

    return projection;

}

Mat4 Mat4::CreateOrthographicMatrix(int width, int height, float near, float far)
{
    Mat4 ortho;

    ortho.array[0]  = (float)height / width ;
    ortho.array[5]  = 1;
    ortho.array[10] = -2 / (far - near);

    ortho.array[12] = 0;
    ortho.array[13] = 0;
    ortho.array[14] = - (far + near) / (far - near);
    ortho.array[15] = 1;

    return ortho;
}

Mat4 Mat4::CreateViewportMatrix(int width, int height, float near, float far)
{
    Mat4 viewport;

    viewport.array[0] = width / 2;
    viewport.array[3] = width / 2;

    viewport.array[5] = -height / 2;
    viewport.array[7] = height / 2;

    viewport.array[10] = (far - near) / 2;
    viewport.array[11] = (far + near) / 2;

    viewport.array[15] = 1;

    return viewport;
}

Mat4 Mat4::CreateCameraMatrix(const Vec3 &eye, const Vec3 &position, const Vec3 &up)
{
    Mat4 cameraTranslation; // Matrix used to move all the vertex depending of the position of the camera

    cameraTranslation.array[0] = 1;
    cameraTranslation.array[5] = 1;
    cameraTranslation.array[10] = 1;

    cameraTranslation.array[12] = - position.x;
    cameraTranslation.array[13] = - position.y;
    cameraTranslation.array[14] = - position.z;

    cameraTranslation.array[15] = 1;

    Mat4 cameraRotation; // Matrix used to move all the vertex depending of the point aimed by the camera
                         // A repere is create with the vector eye, posistion and up
                         // the repere is set in a matrix so it can be used
                         // The matrix make a transformation local to world

    Vec3 F = eye - position; // determine the vector repere for the z value
    Vec3 f = F.Normalize();

    Vec3 U = up.Normalize();

    Vec3 s = CrossProduct(f, U); // determine the vector used for the x value

    s.Normalize();
    F = eye - position;

    Vec3 u = CrossProduct(s, f); // determine the vector used for the y value

    u.Normalize();

    cameraRotation.array[0] = s.x;
    cameraRotation.array[4] = s.y;
    cameraRotation.array[8] = s.z;

    cameraRotation.array[1] = u.x;
    cameraRotation.array[5] = u.y;
    cameraRotation.array[9] = u.z;

    cameraRotation.array[2] = -f.x;
    cameraRotation.array[6] = -f.y;
    cameraRotation.array[10] = -f.z;

    cameraRotation.array[15] = 1;

    return cameraRotation * cameraTranslation;
}

Mat4 Mat4::CreateCameraAroundOrigin(float rotationX, float rotationY, float length)
{
    rotationX *= PI / 180;
    rotationY *= PI / 180;

    Vec4 newPosition({0, 0, length}, 1);
    newPosition = CreateYRotationMatrix(rotationX) * CreateXRotationMatrix(rotationY) * newPosition;

    return CreateCameraMatrix({0, 0, 0}, {newPosition.x, newPosition.y, newPosition.z}, {0, 1, 0});
}


void Mat4::display()
{
    for (unsigned int i = 0 ; i < 16 ; i += 1)
    {
        std::cout << array[i] << " | ";
        if (i % 4 == 3)
        {
            std::cout << std::endl;
        }
    }
};











// General Usage Matrix


Matrix::Matrix()
{
    n = 0;
    m = 0;
    array = nullptr;
}

Matrix::Matrix(int N, int M)
{
    array = new float [N*M];
    n = N;
    m = M;

    for (int i = 0 ; i < m*n ; i++)
    {
        array[i] = 0;
    }
}

Matrix::Matrix (const Matrix& N)
{
    n = N.n;
    m = N.m;

    array = new float [n*m];
    for (int i = 0 ; i < m*n ; i++)
    {
        array[i] = N.array[i];
    }

}

Matrix::~Matrix()
{
    delete[] array;
}

void Matrix::Init(int N, int M)
{
    n = N;
    m = M;
    array = new float [n*m];
}


float& Matrix::accessor(unsigned int N, unsigned int M)
{
    int get = (N - 1) + (M - 1) * n;
    return array[get];
}

float Matrix::accessor(unsigned int N, unsigned int M) const
{
    int get = (N - 1) + (M - 1) * n;
    return array[get];
}

void Matrix::display() const
{
    int countN = 0;
    int countM = 0;
    for (int i = 0 ; i < n*m ; i++)
    {
        std::cout << "| " <<  array[countN + countM * n] << " |";
        if (countM == m -1 )
        {
            countN++;
            countM = 0;
            std::cout << std::endl;
        }
        else
        {
            countM++;
        }       
    }
}

int Matrix::N()
{
    return n;
}

int Matrix::M()
{
    return m;
}

int Matrix::N() const
{
    return n;
}

int Matrix::M() const 
{
    return m;
}

Matrix Matrix::zero()
{
    for (int i = 0 ; i < m*n ; i++)
    {
        array[i] = 0;
    }

    return *this;
}

Matrix Matrix::identity()
{
    if (n != m)
    {
        std::cout << "the matrix isn't square\n" << std::endl;
        return *this;
    }
    int countM = 0;
    int countN = 0;
    
    for (int i = 0 ; i < m*n ; i++)
    {
       array[i] = 0;
       if (i == countN + countM)
       {
           array[i] = 1;
           countN++;
           countM += n;
       }
    }

    return *this;
}

Matrix Matrix::transpose()
{
    Matrix M(m,n);

    for (int i = 1 ; i <= M.n ; i++)
    {
        for (int e = 1 ; e <= M.m ; e++)
        {
            M.accessor(i,e) = this->accessor(e,i);
        }
    }

    return M;
}

Matrix operator+(const Matrix& mat1, const Matrix& mat2)
{
    Matrix result (mat1.n, mat1.m);
    if (mat1.n != mat2.n || mat1.m != mat2.m)
    {
        std::cout << "incompatible matrix for addition" << std::endl;
        return result;
    }
    for (int i = 0 ; i < result.n*result.m ; i++)
    {
        result[i] = mat1[i] + mat2[i];
    }
    return result;
}

Matrix operator-(const Matrix& mat1, const Matrix& mat2)
{
    Matrix result (mat1.n, mat1.m);
    if (mat1.n != mat2.n || mat1.m != mat2.m)
    {
        std::cout << "incompatible matrix for addition" << std::endl;
        return result;
    }
    for (int i = 0 ; i < result.n*result.m ; i++)
    {
        result[i] = mat1[i] - mat2[i];
    }
    return result;
}

Matrix operator/(const Matrix& mat,  float multiplyer)
{
    Matrix result(mat.n, mat.m);
    for (int i = 1 ; i <= mat.n ; i++)
    {
        for (int j = 1 ; j <= mat.m ; j++)
        {
            result.accessor(i, j) = mat.accessor(i, j) / multiplyer;
        }
    }
    return result; 
}

Matrix operator*(const Matrix& mat,  float multiplyer)
{
    Matrix result(mat.n, mat.m);
    for (int i = 1 ; i <= mat.n ; i++)
    {
        for (int j = 1 ; j <= mat.m ; j++)
        {
            result.accessor(i, j) = mat.accessor(i, j) * multiplyer;
        }
    }
    return result; 
}


Matrix operator*(const Matrix& mat1, const Matrix& mat2)
{
    if (mat1.m != mat2.n && mat1.n != mat2.m)
        return Matrix(1,1);

    Matrix M(mat2.n, mat2.m);

    for (int i = 1 ; i <= mat1.n ; i++)
    {
        for (int e = 1 ; e <= mat2.m ; e++)
            {
                for (int k = 1 ; k <= mat1.m ; k++)
                {
                    M.accessor(i,e) += mat1.accessor(i,k) * mat2.accessor(k,e);
                }
            }
    }
    return M;
}

float& Matrix::operator[](unsigned int i)
{
    return array[i];
}


float Matrix::operator[](unsigned int i) const
{
    return array[i];
}

float Matrix::determinant()
{
    if (n != m)
        {
            std::cout << "The Matrix isn't square";
            return -1;
        }
    if (n == 1)
        return Determinant_Matrix_1(*this);
    if (n == 2)
        return Determinant_Matrix_2(*this);
    if (n == 3)
        return Determinant_Matrix_3(*this);
    if (n == 4)
        return Determinant_Matrix_4(*this);
    else 
    {
        float result = 0;
        for (int i = 1 ; i <= n; i++)
        {
            if (i%2 != 0)
                result += accessor(i, 1) * GetDeterminant(GetSubMatrix(*this, i,1));
            else
                result -= accessor(i, 1) * GetDeterminant(GetSubMatrix(*this, i,1));
        }
        return result;
    }

    
}

float Matrix::Determinant_Matrix_1(const Matrix& matrix)
{
    return matrix.accessor(1,1);
}

float Matrix::Determinant_Matrix_2(const Matrix& matrix)
{
    return (matrix.accessor(1,1) * matrix.accessor(2,2)) - (matrix.accessor(2,1) * matrix.accessor(1,2));
}

float Matrix::Determinant_Matrix_3(const Matrix& matrix)
{
    float result = matrix.accessor(1,1) * ((matrix.accessor(2,2) * matrix.accessor(3,3)) - (matrix.accessor(2,3) * matrix.accessor(3,2)));
    result -= matrix.accessor(1,2) * ((matrix.accessor(2,1) * matrix.accessor(3,3)) - (matrix.accessor(2,3) * matrix.accessor(3,1)));
    result += matrix.accessor(1,3) * ((matrix.accessor(2,1) * matrix.accessor(3,2)) - (matrix.accessor(2,2) * matrix.accessor(3,1)));

    return result;
}

float Matrix::Determinant_Matrix_4(const Matrix& matrix)
{
    float result = matrix[0] * (  (matrix[5] * ((matrix[10] * matrix[15]) - (matrix[11]  * matrix[14])))\
                                - (matrix[6] * ((matrix[9]  * matrix[15])  - (matrix[11] * matrix[13])))\
                                + (matrix[7] * ((matrix[9]  * matrix[14])  - (matrix[10] * matrix[13]))));

    result -= matrix[1] * (       (matrix[4] * ((matrix[10] * matrix[15])  - (matrix[11]  * matrix[14])))\
                                - (matrix[6] * ((matrix[8]  * matrix[15])  - (matrix[11]  * matrix[12])))\
                                + (matrix[7] * ((matrix[8]  * matrix[14])  - (matrix[10]  * matrix[12]))));

    result += matrix[2] * (       (matrix[4] * ((matrix[9]  * matrix[15])  - (matrix[11]  * matrix[13])))\
                                - (matrix[5] * ((matrix[8]  * matrix[15])  - (matrix[11]  * matrix[12])))\
                                + (matrix[7] * ((matrix[8]  * matrix[13])  - (matrix[9]   * matrix[12]))));

    result += matrix[3] * (       (matrix[4] * ((matrix[9]  * matrix[14])  - (matrix[10]  * matrix[13])))\
                                - (matrix[6] * ((matrix[8]  * matrix[14])  - (matrix[10]  * matrix[12])))\
                                + (matrix[7] * ((matrix[8]  * matrix[13])  - (matrix[9]   * matrix[12]))));
    return result;
}

float Matrix::GetDeterminant(const Matrix& matrix)
{
    if (matrix.N() != matrix.M())
    {
        std::cout << "The Matrix isn't square" << std::endl;
        return -1;
    }
    if (matrix.N() == 1)
        return Determinant_Matrix_1(matrix);
    
    else if (matrix.N() == 2)
        return Determinant_Matrix_2(matrix);
    
    else if (matrix.N() == 3)
        return Determinant_Matrix_3(matrix);
    else if (matrix.N() == 4)
        return Determinant_Matrix_4(matrix);
    
    else 
    {
        float result = 0;
        for (int i = 1 ; i <= matrix.N(); i++)
        {
            if (i%2 != 0)
                result += matrix.accessor(i, 1) * GetDeterminant(GetSubMatrix(matrix, i,1));
            else
                result -= matrix.accessor(i, 1) * GetDeterminant(GetSubMatrix(matrix, i,1));
        }
        return result;
    }
    
}

Matrix Matrix::GetSubMatrix(const Matrix& matrix, int excludedLineIndex, int excludedColumnIndex)
{
    Matrix newMatrix(matrix.N() - 1, matrix.M() - 1);

    int n = 1;
    int m = 1;

    for (int i = 1; i <= matrix.N() ; i++)
    {
        if (i != excludedLineIndex)
        {
            for (int e = 1; e <= matrix.M() ; e++)
            {
                if (e != excludedColumnIndex )
                {
                    newMatrix.accessor(n,m) = matrix.accessor(i,e);
                    m++;
                }
            }
            n++;
            m = 1;
        }
    }
    return newMatrix;
}


float Matrix::GetMinor(const Matrix& matrix, unsigned int line, unsigned int column)
{
    return GetDeterminant(GetSubMatrix(matrix, line, column));
}

float Matrix::GetCofactor(const Matrix& matrix, unsigned int line, unsigned int column)
{
    return GetDeterminant(GetSubMatrix(matrix, line, column)) * Power(-1, line + column);
}

Matrix Matrix::GetComatrix(const Matrix& matrix)
{
    if (matrix.N() != matrix.M())
    {
        std::cout << "The Matrix isn't square" << std::endl;
        return Matrix();
    }
    Matrix Comatrix(matrix.N(), matrix.M());

    for (int n = 1 ; n <= matrix.N() ; n++)
    {
        for (int m = 1 ; m <= matrix.M() ; m++)
        {
            Comatrix.accessor(n, m) = GetCofactor(matrix, n, m);
        }
    }
    return Comatrix;
}

Matrix Matrix::GetMatrixTranspose(const Matrix& matrix)
{
    Matrix Transpose(matrix.M(), matrix.N());

    for (int n = 1 ; n <= matrix.N() ; n++)
    {
        for (int m = 1 ; m <= matrix.M() ; m++)
        {
            Transpose.accessor(n, m) = matrix.accessor(m, n);
        }
    }
    return Transpose;
}

Matrix Matrix::GetMatrixAdjointe(const Matrix& matrix)
{
    return GetMatrixTranspose(GetComatrix(matrix));
}

Matrix Matrix::GetMatrixInverse(const Matrix& matrix)
{
    if (GetDeterminant(matrix) == 0)
    {
        std::cout << "Inverse dosen't exist for this matrix" << std::endl;
        return matrix;
    }
    return GetMatrixAdjointe(matrix)/GetDeterminant(matrix);
}

Matrix Matrix::ResolveEquation(const Matrix& calcul, const Matrix& result)
{
    if (calcul.m == calcul.n && result.n == calcul.n && result.m == 1)
    {
        return GetMatrixInverse(calcul) * result;
    }

    return result;
}

float Power(float A, float B)
{
    float result = A;
    for (int i = 0 ; i <= B ; i++)
    {
        result *= A;
    }
    return result;
}