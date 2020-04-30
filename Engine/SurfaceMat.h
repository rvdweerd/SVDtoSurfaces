#pragma once
#include "Eigen/Dense"
#include "Surface.h"

using namespace Eigen;

class SurfaceMatrix
{
    //MatrixXf A;
    size_t maxres = 64;
    size_t curres = 0;
    std::vector<MatrixXf> Mvec;
public:
    SurfaceMatrix(Surface& surf)
    {   
        //surf.Clip();
        //surf.Scale(2.f);
        //surf.Scale(2.f);
        MatrixXf A(surf.GetHeight(), surf.GetWidth());
        for (size_t y = 0; y < surf.GetHeight(); y++)
        {
            for (size_t x = 0; x < surf.GetWidth(); x++)
            {
                auto r = surf.GetPixel(x, y).GetR();
                auto g = surf.GetPixel(x, y).GetG();
                auto b = surf.GetPixel(x, y).GetB();
                float avg = (r + g + b) / 3.0f;
                A(y, x) = avg;
                //A(y, x) = surf.GetPixel(x, y).GetR();
            }
        }
        JacobiSVD<MatrixXf> svd(A, ComputeThinU | ComputeThinV);
        
        
        Mvec.push_back(svd.matrixU().col(0)* svd.matrixV().col(0).transpose()* svd.singularValues()(0));
        for (int i = 1; i < maxres; i++)
        {
            Mvec.push_back(Mvec[i - 1] + svd.matrixU().col(i) * svd.matrixV().col(i).transpose() * svd.singularValues()(i));
        }
        
        A = Mvec[curres];
        for (size_t y = 0; y < surf.GetHeight(); y++)
        {
            for (size_t x = 0; x < surf.GetWidth(); x++)
            {
                Color c;
                c.SetR((unsigned  int)A(y, x) + 1);
                c.SetG((unsigned  int)A(y, x) + 1);
                c.SetB((unsigned  int)A(y, x) + 1);

                surf.PutPixel(x, y, c);
                //surf.PutPixel(x, y, (unsigned  int)A ( y, x )+1);
                
            }
        }


        //MatrixXf A = MatrixXf(2, 2);
        //A(0, 0) = 2;
        //A(0, 1) = 2;
        //A(1, 0) = -1;
        //A(1, 1) = 1;

        //JacobiSVD<MatrixXf> svd(A, ComputeThinU | ComputeThinV);
        //auto test = svd.singularValues();
        //float test0 = test(0);
        //float test1 = test(1);
        //auto U = svd.matrixU();
        //auto V = svd.matrixV();
       
        //MatrixXf A0 = MatrixXf(2, 2);
        //MatrixXf A1 = MatrixXf(2, 2);
        //Vector2f u0 = U.col(0);
        //Vector2f v0 = V.col(0);
        //Vector2f u1 = U.col(1);
        //Vector2f v1 = V.col(1);
        //A0 = u0 * v0.transpose() * test0 ;
        //float a0 = A0(0, 0);
        //float b0 = A0(0, 1);
        //float c0 = A0(1, 0);
        //float d0 = A0(1, 1);
        //
        //A1 = u1 * v1.transpose() * test1;
        //float a1 = A1(0, 0);
        //float b1 = A1(0, 1);
        //float c1 = A1(1, 0);
        //float d1 = A1(1, 1);


        //m(0, 0) = 3;
        //m(1, 0) = 2.5;
        //m(0, 1) = -1;
        //m(1, 1) = m(1, 0) + m(0, 1);
        //const std::string mesg = std::to_string(m(1, 1));
        //OutputDebugStringA(mesg.c_str());
        //OutputDebugStringW
    }
    void IncreaseResolution(Surface& surf)
    {
        MatrixXf A(surf.GetHeight(), surf.GetWidth());
        curres = std::min(maxres-1, curres + 1);
        A = Mvec[curres];
        for (size_t y = 0; y < surf.GetHeight(); y++)
        {
            for (size_t x = 0; x < surf.GetWidth(); x++)
            {
                Color c;
                
                c.SetR((unsigned  int)A(y, x) + 1);
                c.SetG((unsigned  int)A(y, x) + 1);
                c.SetB((unsigned  int)A(y, x) + 1);
                surf.PutPixel(x, y, c);
                //surf.PutPixel(x, y, (unsigned  int)A(y, x)+1);
                
            }
        }

    }
};
