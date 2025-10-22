#pragma once
#include <cmath>
#include <algorithm>
#include "Vector3.h"
#include "Quaternion.h"

namespace math
{
    /**
     * @class Mat4
     * @brief Represents a 4x4 transformation matrix.
     *
     * This class supports common operations for 3D transformations such as
     * translation, rotation, scaling, projection, and matrix inversion.
     *
     * @tparam T Numeric type (float, double, etc.)
     *
     * @example Mat4_Class_Examples.cpp
     */
    template <typename T>
    class Mat4
    {
    public:
        /**
         * @brief Constructs an identity matrix.
         *
         * @snippet Mat4_Class_Examples.cpp Mat4_DefaultConstructor
         */
        Mat4();

        /**
         * @brief Constructs a matrix with explicit values.
         * @param m00..m33 Matrix elements in row-major order.
         *
         * @snippet Mat4_Class_Examples.cpp Mat4_ParameterizedConstructor
         */
        Mat4(T m00, T m01, T m02, T m03,
            T m10, T m11, T m12, T m13,
            T m20, T m21, T m22, T m23,
            T m30, T m31, T m32, T m33);

        /**
         * @brief Destructor.
         */
        ~Mat4();

        /**
         * @brief Returns the identity matrix.
         * @return A 4x4 identity matrix.
         */
        static Mat4<T> Identity();

        /**
         * @brief Returns a zero-filled matrix.
         * @return A 4x4 zero matrix.
         */
        static Mat4<T> Zero();

        /**
         * @brief Builds a transformation matrix from translation, rotation, and scale.
         * @param position Translation vector.
         * @param rotation Rotation quaternion.
         * @param scale Scaling vector.
         * @return The composed transformation matrix.
         *
         * @snippet Mat4_Class_Examples.cpp Mat4_TRS
         */
        static Mat4<T> TRS(const Vector3<T>& position, const Quaternion& rotation, const Vector3<T>& scale);

        /**
         * @brief Builds a perspective projection matrix.
         * @param fovYRadians Field of view in radians.
         * @param aspect Aspect ratio.
         * @param nearZ Near clipping plane.
         * @param farZ Far clipping plane.
         * @return The perspective projection matrix.
         *
         * @snippet Mat4_Class_Examples.cpp Mat4_Perspective
         */
        static Mat4<T> Perspective(T fovYRadians, T aspect, T nearZ, T farZ);

        /**
         * @brief Builds an orthographic projection matrix.
         * @param left Left clipping plane.
         * @param right Right clipping plane.
         * @param bottom Bottom clipping plane.
         * @param top Top clipping plane.
         * @param nearZ Near clipping plane.
         * @param farZ Far clipping plane.
         * @return The orthographic projection matrix.
         *
         * @snippet Mat4_Class_Examples.cpp Mat4_Ortho
         */
        static Mat4<T> Ortho(T left, T right, T bottom, T top, T nearZ, T farZ);

        /**
         * @brief Builds a LookAt view matrix.
         * @param eye Camera position.
         * @param target Target position.
         * @param up Up vector.
         * @return The view matrix.
         *
         * @snippet Mat4_Class_Examples.cpp Mat4_LookAt
         */
        static Mat4<T> LookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up);

        /**
         * @brief Returns a transposed copy of this matrix.
         * @return The transposed matrix.
         */
        Mat4<T> Transpose() const;

        /**
         * @brief Returns the inverse of this matrix.
         * @return The inverted matrix.
         * @throws std::runtime_error if the matrix is singular.
         */
        Mat4<T> Inverse() const;

        /**
         * @brief Computes the determinant of this matrix.
         * @return The determinant value.
         */
        T Determinant() const;

        /**
         * @brief Multiplies this matrix with another.
         * @param other The matrix to multiply with.
         * @return The resulting matrix.
         *
         * @snippet Mat4_Class_Examples.cpp Mat4_MultiplyMatrix
         */
        Mat4<T> operator*(const Mat4<T>& other) const;

        /**
         * @brief Multiplies this matrix by a 3D point (assuming w=1).
         * @param v The input 3D point.
         * @return The transformed point.
         *
         * @snippet Mat4_Class_Examples.cpp Mat4_MultiplyPoint
         */
        Vector3<T> MultiplyPoint(const Vector3<T>& v) const;

        /**
         * @brief Multiplies this matrix by a direction vector (ignores translation).
         * @param v The input 3D vector.
         * @return The transformed direction.
         *
         * @snippet Mat4_Class_Examples.cpp Mat4_MultiplyVector
         */
        Vector3<T> MultiplyVector(const Vector3<T>& v) const;

        /**
         * @brief Extracts the rotation component as a quaternion.
         * @return The extracted rotation.
         */
        Quaternion ExtractRotation() const;

        /**
         * @brief Returns true if this matrix represents a valid TRS transform.
         * @return True if valid TRS, false otherwise.
         */
        bool ValidTRS() const;

        /**
         * @brief Checks equality between two matrices (with tolerance).
         * @param other The matrix to compare with.
         * @return True if both matrices are approximately equal.
         */
        bool operator==(const Mat4<T>& other) const;

        /**
         * @brief Checks inequality between two matrices.
         * @param other The matrix to compare with.
         * @return True if the matrices differ.
         */
        bool operator!=(const Mat4<T>& other) const;

        /**
         * @brief Extracts the translation component of the matrix.
         * @return The extracted position as a Vector3.
         */
        Vector3<T> ExtractPosition() const;

        /**
         * @brief Extracts the scale component of the matrix.
         * @return The extracted scale as a Vector3.
         */
        Vector3<T> ExtractScale() const;

        /**
         * @brief Returns a specific row of the matrix as a Vector3.
         * @param index The row index (0�3).
         * @return The row as a Vector3.
         */
        Vector3<T> GetRow(int index) const;

        /**
         * @brief Returns a specific column of the matrix as a Vector3.
         * @param index The column index (0�3).
         * @return The column as a Vector3.
         */
        Vector3<T> GetColumn(int index) const;

        /**
         * @brief Creates a translation matrix.
         * @param position The translation vector.
         * @return The translation matrix.
         */
        static Mat4<T> Translate(const Vector3<T>& position);

        /**
         * @brief Creates a uniform scaling matrix.
         * @param scale The scaling vector.
         * @return The scaling matrix.
         */
        static Mat4<T> Scale(const Vector3<T>& scale);

        /**
         * @brief Creates a rotation matrix from a quaternion.
         * @param rotation The rotation quaternion.
         * @return The rotation matrix.
         */
        static Mat4<T> Rotate(const Quaternion& rotation);

        /**
         * @brief Provides access to an element of the matrix by row and column.
         * @param row The row index.
         * @param col The column index.
         * @return Reference to the element.
         */
        T& operator()(int row, int col);

        /**
         * @brief Provides read-only access to an element of the matrix by row and column.
         * @param row The row index.
         * @param col The column index.
         * @return The element value.
         */
        const T& operator()(int row, int col) const;

    public:
        /** @brief Matrix elements in row-major order. */
        T m[4][4];
    };
}

#include "../src/Mat4.inl"
