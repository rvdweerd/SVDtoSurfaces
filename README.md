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
    // Define A using Eigen matrix type for floats
    MatrixXf A(surf.GetHeight(), surf.GetWidth());
    
    // Fill Matrix with image information (convert RGB to GreyColor)
    for (size_t y = 0; y < surf.GetHeight(); y++)
    {
        for (size_t x = 0; x < surf.GetWidth(); x++)
        {
            auto r = surf.GetPixel(x, y).GetR();
            auto g = surf.GetPixel(x, y).GetG();
            auto b = surf.GetPixel(x, y).GetB();
            float avg = (r + g + b) / 3.0f;
            A(y, x) = avg;
        }
    }
    
    // Perform SVD decomposition
    JacobiSVD<MatrixXf> svd(A, ComputeThinU | ComputeThinV);
    
    // Fill the vector Mvec (class data member) with composite matrices with increasing rank
    Mvec.push_back(svd.matrixU().col(0)* svd.matrixV().col(0).transpose()* svd.singularValues()(0));
    for (int i = 1; i < maxResolution; i++)
    {
        Mvec.push_back(Mvec[i - 1] + svd.matrixU().col(i) * svd.matrixV().col(i).transpose() * svd.singularValues()(i));
    }
    ...
}
```
