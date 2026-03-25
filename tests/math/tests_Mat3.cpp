#include <doctest/doctest.h>

#include <nfx/graphics/math/Mat3.h>

#include <numbers>

using namespace nfx::graphics::math;

namespace
{
    // Build a column-major 4x4 identity matrix
    void makeIdentity4(float out[16])
    {
        for (int i = 0; i < 16; ++i)
        {
            out[i] = 0.f;
        }
        out[0] = out[5] = out[10] = out[15] = 1.f;
    }

    // Multiply 3x3 column-major matrices  C = A * B
    void mat3Mul(float out[9], const float a[9], const float b[9])
    {
        for (int col = 0; col < 3; ++col)
            for (int row = 0; row < 3; ++row)
            {
                float s = 0.f;
                for (int k = 0; k < 3; ++k)
                {
                    s += a[k * 3 + row] * b[col * 3 + k];
                }
                out[col * 3 + row] = s;
            }
    }

    // Check 3x3 column-major matrix against expected column-major values
    void checkMat3(const float m[9], const float expected[9], float eps = 1e-5f)
    {
        for (int i = 0; i < 9; ++i)
        {
            CHECK(m[i] == doctest::Approx(expected[i]).epsilon(eps));
        }
    }
} // namespace

TEST_SUITE("Mat3")
{
    TEST_CASE("mat3Identity writes identity matrix")
    {
        float m[9];
        mat3Identity(m);

        const float expected[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
        checkMat3(m, expected);
    }

    TEST_CASE("mat3Scale writes diagonal scale matrix")
    {
        float m[9];
        mat3Scale(m, 2.f, 3.f, 4.f);

        const float expected[9] = { 2, 0, 0, 0, 3, 0, 0, 0, 4 };
        checkMat3(m, expected);
    }

    TEST_CASE("mat3RotateX writes expected rotation matrix")
    {
        float m[9];
        mat3RotateX(m, std::numbers::pi_v<float> * 0.5f);

        const float expected[9] = {
            1, 0, 0, 0, 0, 1, 0, -1, 0,
        };
        checkMat3(m, expected, 1e-5f);
    }

    TEST_CASE("mat3RotateY writes expected rotation matrix")
    {
        float m[9];
        mat3RotateY(m, std::numbers::pi_v<float> * 0.5f);

        const float expected[9] = {
            0, 0, -1, 0, 1, 0, 1, 0, 0,
        };
        checkMat3(m, expected, 1e-5f);
    }

    TEST_CASE("mat3RotateZ writes expected rotation matrix")
    {
        float m[9];
        mat3RotateZ(m, std::numbers::pi_v<float> * 0.5f);

        const float expected[9] = {
            0, 1, 0, -1, 0, 0, 0, 0, 1,
        };
        checkMat3(m, expected, 1e-5f);
    }

    TEST_CASE("identity 4x4 produces identity normal matrix")
    {
        float m4[16];
        makeIdentity4(m4);

        float n[9];
        mat3InverseTranspose(n, m4);

        // Expected: identity 3x3 column-major
        const float expected[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
        checkMat3(n, expected);
    }

    TEST_CASE("uniform scale produces reciprocal diagonal normal matrix")
    {
        // Uniform scale S: inverse-transpose = (1/S) * I
        float m4[16];
        makeIdentity4(m4);
        m4[0] = m4[5] = m4[10] = 2.f;

        float n[9];
        mat3InverseTranspose(n, m4);

        const float s = 0.5f;
        const float expected[9] = { s, 0, 0, 0, s, 0, 0, 0, s };
        checkMat3(n, expected);
    }

    TEST_CASE("translation in 4x4 does not affect normal matrix")
    {
        float m4[16];
        makeIdentity4(m4);
        // Add translation (column 3)
        m4[12] = 5.f;
        m4[13] = -3.f;
        m4[14] = 7.f;

        float n[9];
        mat3InverseTranspose(n, m4);

        // Upper-left 3x3 is still identity -> normal matrix is identity
        const float expected[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
        checkMat3(n, expected);
    }

    TEST_CASE("non-uniform scale: normal matrix is inverse-transpose of diagonal")
    {
        // M33 = diag(2, 4, 8)  ->  inv-transpose = diag(1/2, 1/4, 1/8)
        float m4[16];
        makeIdentity4(m4);
        m4[0] = 2.f;
        m4[5] = 4.f;
        m4[10] = 8.f;

        float n[9];
        mat3InverseTranspose(n, m4);

        const float expected[9] = { 0.5f, 0, 0, 0, 0.25f, 0, 0, 0, 0.125f };
        checkMat3(n, expected);
    }

    TEST_CASE("zero determinant produces zero matrix")
    {
        float m4[16];
        makeIdentity4(m4);
        // Make upper-left 3x3 singular: zero out a row
        m4[0] = m4[4] = m4[8] = 0.f;

        float n[9];
        mat3InverseTranspose(n, m4);

        for (int i = 0; i < 9; ++i)
            CHECK(n[i] == doctest::Approx(0.f));
    }

    TEST_CASE("90-degree rotation around Z: normal matrix equals rotation matrix")
    {
        // R = rot_z(90°): col-major
        // col0=(0,1,0), col1=(-1,0,0), col2=(0,0,1)
        float m4[16];
        makeIdentity4(m4);
        m4[0] = 0.f;
        m4[1] = 1.f;
        m4[2] = 0.f; // col 0
        m4[4] = -1.f;
        m4[5] = 0.f;
        m4[6] = 0.f; // col 1
        m4[8] = 0.f;
        m4[9] = 0.f;
        m4[10] = 1.f; // col 2

        float n[9];
        mat3InverseTranspose(n, m4);

        // For orthogonal matrix: inv-transpose = M itself
        const float expected[9] = { 0, 1, 0, -1, 0, 0, 0, 0, 1 };
        checkMat3(n, expected, 1e-5f);
    }

    TEST_CASE("normal matrix transpose times original matrix is identity for orthogonal input")
    {
        // Rot 45° around Y
        const float c = std::cos(std::numbers::pi_v<float> * 0.25f);
        const float s = std::sin(std::numbers::pi_v<float> * 0.25f);

        float m4[16];
        makeIdentity4(m4);
        m4[0] = c;
        m4[1] = 0.f;
        m4[2] = -s; // col 0
        m4[4] = 0.f;
        m4[5] = 1.f;
        m4[6] = 0.f; // col 1
        m4[8] = s;
        m4[9] = 0.f;
        m4[10] = c; // col 2

        float n[9];
        mat3InverseTranspose(n, m4);

        // Extract upper-left 3x3 of m4 as m3
        const float m3[9] = { m4[0], m4[1], m4[2], m4[4], m4[5], m4[6], m4[8], m4[9], m4[10] };

        // For orthogonal m3, n = (m3^-1)^T = m3. Therefore n^T * m3 = I
        float nT[9];
        // Transpose n (col-major -> row swap)
        nT[0] = n[0];
        nT[1] = n[3];
        nT[2] = n[6];
        nT[3] = n[1];
        nT[4] = n[4];
        nT[5] = n[7];
        nT[6] = n[2];
        nT[7] = n[5];
        nT[8] = n[8];

        float result[9];
        mat3Mul(result, nT, m3);

        const float identity[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
        checkMat3(result, identity, 1e-5f);
    }
}
