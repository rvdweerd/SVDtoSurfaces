# SVDtoSurfaces
Applying SVD to bitmap surfaces (experimenting with compression)
* Loads a bitmap image into an image matrix
* Applies SVD
* Lets user choose the amount of singular values to be included in the compressed image

This demo uses:
* The C++ Eigen library for matrix functions (all header files included in solution)
* The Chili DirectX Framework for the putpixel calls & graphics window

Demo:
* Visualizes the increase in rank r (i.e. how many singular values are used to build the compressed image matrix)
* The composite matrix is the sum over r of: r'th left singular vector * r'th singular value * r'th right singular vector

![demo](svd_dog_demo1.gif)

Note:
The essence of the code is in "SurfaceMat.h" (Surface is the type that holds the original sprite):
```cpp
SurfaceMatrix(Surface& surf)
{
    MatrixXf A(surf.GetHeight(), surf.GetWidth());
    JacobiSVD<MatrixXf> svd(A, ComputeThinU | ComputeThinV);
    Mvec.push_back(svd.matrixU().col(0)* svd.matrixV().col(0).transpose()* svd.singularValues()(0));
    for (int i = 1; i < maxResolution; i++)
    {
        Mvec.push_back(Mvec[i - 1] + svd.matrixU().col(i) * svd.matrixV().col(i).transpose() * svd.singularValues()(i));
    }
    ...
}
```
