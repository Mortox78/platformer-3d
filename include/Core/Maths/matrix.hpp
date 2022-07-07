#ifndef _MATRIX_
#define _MATRIX_

#define PI 3.141559

#include "vector4D.hpp"

#include <iostream>

namespace Core
{
    namespace Maths
    {
        class Mat4
        {
        public:
            Mat4();
            ~Mat4();
            float array[16]{0};

            static Mat4 GetIdentityMatrix                   ();

            static Mat4 CreateTransformMatrix               (const Vec3 &rotation, const Vec3 &position, const Vec3 &scale);
            static Mat4 CreateTranslationMatrix             (const Vec3 &translation);
            static Mat4 CreateScaleMatrix                   (const Vec3 &scale);
            static Mat4 CreateXRotationMatrix               (float angle);
            static Mat4 CreateYRotationMatrix               (float angle);
            static Mat4 CreateZRotationMatrix               (float angle);
            static Mat4 CreateFixedAngleEulerRotationMatrix (const Vec3 &angle);
            static Mat4 CreateRotationAroundAxeMatrix       (const Vec3 &axe, float angle);

            static Mat4 CreatePerspectiveProjectionMatrix   (int width, int height, float near, float far, float fov);
            static Mat4 CreateOrthographicMatrix            (int width, int height, float near, float far);

            static Mat4 CreateViewportMatrix                (int width, int height, float near, float far);

            static Mat4 CreateCameraMatrix              (const Vec3 &eye, const Vec3 &position, const Vec3 &angleZ);
            static Mat4 CreateCameraAroundOrigin        (float rotationX, float rotationY, float length);

            void display();

            friend std::ostream& operator<<(std::ostream& os, const Mat4& mat)
            {
                for (unsigned int i = 0; i < 16; ++i)
                {
                    os << mat.array[i] << std::endl;
                }

                return os;
            }

            friend std::istream& operator>>(std::istream& is, Mat4& mat)
            {
                for (unsigned int i = 0; i < 16; ++i)
                {
                    is >> mat.array[i];
                }

                return is;
            }
        };


        class Matrix
        {
        protected:
        public:
            float *array;
            int n;
            int m;
        
            Matrix();
            Matrix(int, int);
            Matrix(const Matrix &);
            ~Matrix();
        
            void Init(int, int);
        
            float &accessor(unsigned int, unsigned int);
            float accessor(unsigned int, unsigned int) const;
        
            void display() const;
        
            int N();
            int M();
        
            int N() const;
            int M() const;
        
            Matrix zero();
            Matrix identity();
        
            Matrix transpose();
        
        
            float &operator[](unsigned int);
            float operator[](unsigned int) const;
        
            float determinant();
        
            static float Determinant_Matrix_1(const Matrix &);
            static float Determinant_Matrix_2(const Matrix &);
            static float Determinant_Matrix_3(const Matrix &);
            static float Determinant_Matrix_4(const Matrix &);
        
            static Matrix GetSubMatrix(const Matrix &matrix, int excludedColumnIndex, int excludedLineIndex);
            static float GetDeterminant(const Matrix &matrix);
        
            static float GetMinor(const Matrix &, unsigned int line, unsigned int column);
            static float GetCofactor(const Matrix &matrix, unsigned int line, unsigned int column);
        
            static Matrix GetComatrix(const Matrix &matrix);
            static Matrix GetMatrixTranspose(const Matrix &matrix);
            static Matrix GetMatrixAdjointe(const Matrix &matrix);
            static Matrix GetMatrixInverse(const Matrix &matrix);
            static Matrix ResolveEquation(const Matrix &calcul, const Matrix &result);
        };
    }
} // namespace Core

Core::Maths::Mat4 operator+     (const Core::Maths::Mat4 &, const Core::Maths::Mat4 &);
Core::Maths::Mat4 operator*     (const Core::Maths::Mat4 &, const Core::Maths::Mat4 &);
Core::Maths::Vec4 operator*     (const Core::Maths::Mat4 &, const Core::Maths::Vec4 &);
Core::Maths::Mat4 operator*     (const Core::Maths::Mat4 &, const float &);

Core::Maths::Matrix operator+(const Core::Maths::Matrix &, const Core::Maths::Matrix &);
Core::Maths::Matrix operator-(const Core::Maths::Matrix &, const Core::Maths::Matrix &);
Core::Maths::Matrix operator/(const Core::Maths::Matrix &, float);
Core::Maths::Matrix operator*(const Core::Maths::Matrix &, float);

float Power(float A, float B);

#endif