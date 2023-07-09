#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include "cuda_img.h"
// Demo kernel to transform RGB color schema to BW schema
__global__ void kernel_inversion(CudaImg t_color_cuda_img, CudaImg t_bw_cuda_img, int n, int s)
{
    // X,Y coordinates and check image dimensions
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    if (l_y >= t_color_cuda_img.m_size.y)
        return;
    if (l_x >= t_color_cuda_img.m_size.x)
        return;
    // Get point from color picture
    uchar3 l_bgr = t_color_cuda_img.m_p_uchar3[l_y * t_color_cuda_img.m_size.x + l_x];

    int x = t_color_cuda_img.m_size.x / 2;
    int y = t_color_cuda_img.m_size.y / 2;
    int x2 = l_x;
    int y2 = l_y;
    if (n == 0)
    {
        if (l_x < x)
        {
            x2 = l_x + (t_color_cuda_img.m_size.x - x);
        }
        else
        {
            x2 = l_x - x;
        }
    }
    else
    {
        if (l_y < y)
        {
            y2 = l_y + (t_color_cuda_img.m_size.y - y);
        }
        else
        {
            y2 = l_y - y;
        }
    }
    /*// Store BW point to new image
    //t_bw_cuda_img.m_p_uchar1[ l_y * t_bw_cuda_img.m_size.y + l_y ].y = l_bgr.y * 0.11 + l_bgr.y * 0.59 + l_bgr.z * 0.30;
    t_bw_cuda_img.m_p_uchar3[ y2 * t_bw_cuda_img.m_size.x + x2].x = l_bgr.x;
    t_bw_cuda_img.m_p_uchar3[ y2* t_bw_cuda_img.m_size.x + x2].y = l_bgr.y;
    t_bw_cuda_img.m_p_uchar3[ y2 * t_bw_cuda_img.m_size.x + x2].z = l_bgr.z;*/
    // Store BW point to new image
    // t_bw_cuda_img.m_p_uchar1[ l_y * t_bw_cuda_img.m_size.x + l_x ].x = l_bgr.x * 0.11 + l_bgr.y * 0.59 + l_bgr.z * 0.30;
    /*t_bw_cuda_img.m_p_uchar3[ y2 * t_bw_cuda_img.m_size.x + x2].x = l_bgr.x;
    t_bw_cuda_img.m_p_uchar3[ y2 * t_bw_cuda_img.m_size.x + x2].y = l_bgr.y;
    t_bw_cuda_img.m_p_uchar3[ y2 * t_bw_cuda_img.m_size.x + x2].z = l_bgr.z;*/
    t_bw_cuda_img.at3(y2, x2).x = l_bgr.x;
    t_bw_cuda_img.at3(y2, x2).y = l_bgr.y;
    t_bw_cuda_img.at3(y2, x2).z = l_bgr.z;
}

__global__ void kernel_colourChange(CudaImg t_color_cuda_img, CudaImg t_bw_cuda_img, int r, int g, int b)
{
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    if (l_y >= t_color_cuda_img.m_size.y)
        return;
    if (l_x >= t_color_cuda_img.m_size.x)
        return;
    // Get point from color picture
    uchar3 l_bgr = t_color_cuda_img.m_p_uchar3[l_y * t_color_cuda_img.m_size.x + l_x];

    int x2 = l_x;
    int y2 = l_y;
    // Store BW point to new image
    // t_bw_cuda_img.m_p_uchar1[ l_y * t_bw_cuda_img.m_size.x + l_x ].x = l_bgr.x * 0.11 + l_bgr.y * 0.59 + l_bgr.z * 0.30;
    t_bw_cuda_img.m_p_uchar3[y2 * t_bw_cuda_img.m_size.x + x2].x = l_bgr.x * r;
    t_bw_cuda_img.m_p_uchar3[y2 * t_bw_cuda_img.m_size.x + x2].y = l_bgr.y * g;
    t_bw_cuda_img.m_p_uchar3[y2 * t_bw_cuda_img.m_size.x + x2].z = l_bgr.z * b;
}

void cu_run_inversion(CudaImg t_color_cuda_img, CudaImg t_bw_cuda_img, int n, int s)
{
    cudaError_t l_cerr;
    // Grid creation, size of grid must be equal or greater than images
    int l_block_size = 16;
    dim3 l_blocks((t_color_cuda_img.m_size.x + l_block_size - 1) / l_block_size, (t_color_cuda_img.m_size.y + l_block_size - 1) / l_block_size);
    dim3 l_threads(l_block_size, l_block_size);
    kernel_inversion<<<l_blocks, l_threads>>>(t_color_cuda_img, t_bw_cuda_img, n, s);
    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));
    cudaDeviceSynchronize();
}

void cu_run_colourChange(CudaImg t_color_cuda_img, CudaImg t_bw_cuda_img, int r, int g, int b)
{
    cudaError_t l_cerr;
    // Grid creation, size of grid must be equal or greater than images
    int l_block_size = 16;
    dim3 l_blocks((t_color_cuda_img.m_size.x + l_block_size - 1) / l_block_size, (t_color_cuda_img.m_size.y + l_block_size - 1) / l_block_size);
    dim3 l_threads(l_block_size, l_block_size);
    kernel_colourChange<<<l_blocks, l_threads>>>(t_color_cuda_img, t_bw_cuda_img, r, g, b);
    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));
    cudaDeviceSynchronize();
}
cuda_img.h

#pragma once
#include <opencv2/core/mat.hpp>
    // Structure definition for exchanging data between Host and Device
    struct CudaImg
{
    uint3 m_size; // size of picture
    union
    {
        void *m_p_void;     // data of picture
        uchar1 *m_p_uchar1; // data of picture
        uchar3 *m_p_uchar3; // data of picture
        uchar4 *m_p_uchar4; // data of picture
    };
    __device__ uchar1 &at1(int y, int x) { return m_p_uchar1[y * m_size.x + x]; };
    __device__ uchar3 &at3(int y, int x) { return m_p_uchar3[y * m_size.x + x]; };
    __device__ uchar4 &at4(int y, int x) { return m_p_uchar4[y * m_size.x + x]; };
};
main4_unm.cpp

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <opencv2/opencv.hpp>
#include "uni_mem_allocator.h"
#include "cuda_img.h"
    namespace cv
{
}
// Function prototype from .cu file
void cu_run_inversion(CudaImg t_bgr_cuda_img, CudaImg t_bw_cuda_img, int n, int s);

void cu_run_colourChange(CudaImg t_color_cuda_img, CudaImg t_bw_cuda_img, int r, int g, int b);

int main(int t_numarg, char **t_arg)
{
    // Uniform Memory allocator for Mat
    UniformAllocator allocator;
    cv::Mat::setDefaultAllocator(&allocator);
    if (t_numarg < 2)
    {
        printf("Enter picture filename!\n");
        return 1;
    }
    // Load image
    cv::Mat l_bgr_cv_img = cv::imread(t_arg[1], cv::IMREAD_COLOR); // CV_LOAD_IMAGE_COLOR );
    if (!l_bgr_cv_img.data)
    {
        printf("Unable to read file '%s'\n", t_arg[1]);
        return 1;
    }
    // create empty BW image
    cv::Mat l_bw_cv_img(l_bgr_cv_img.size(), CV_8UC3);
    cv::Mat l_bw_cv_img2(l_bgr_cv_img.size(), CV_8UC3);
    cv::Mat l_colour_cv_img(l_bgr_cv_img.size(), CV_8UC3);
    // data for CUDA
    CudaImg l_bgr_cuda_img, l_bw_cuda_img, l_bw_cuda_img2, l_colour_cuda_img;
    l_bgr_cuda_img.m_size.x = l_bw_cuda_img2.m_size.x = l_bw_cuda_img.m_size.x = l_colour_cuda_img.m_size.x = l_bgr_cv_img.size().width;
    l_bgr_cuda_img.m_size.y = l_bw_cuda_img2.m_size.y = l_bw_cuda_img.m_size.y = l_colour_cuda_img.m_size.y = l_bgr_cv_img.size().height;
    l_bgr_cuda_img.m_p_uchar3 = (uchar3 *)l_bgr_cv_img.data;
    l_bw_cuda_img.m_p_uchar3 = (uchar3 *)l_bw_cv_img.data;
    l_bw_cuda_img2.m_p_uchar3 = (uchar3 *)l_bw_cv_img2.data;
    l_colour_cuda_img.m_p_uchar3 = (uchar3 *)l_colour_cv_img.data;
    // Function calling from .cu file
    cu_run_inversion(l_bgr_cuda_img, l_bw_cuda_img, 0, 100);
    cu_run_inversion(l_bgr_cuda_img, l_bw_cuda_img2, 1, 100);
    cu_run_colourChange(l_bgr_cuda_img, l_colour_cuda_img, 0.5, 0.25, 1);
    // Show the Color and BW image
    cv::imshow("Color", l_bgr_cv_img);
    cv::imshow("Inversion", l_bw_cv_img);
    cv::imshow("Inversion2", l_bw_cv_img2);
    cv::imshow("ColourChange", l_colour_cv_img);
    cv::waitKey(0);
}