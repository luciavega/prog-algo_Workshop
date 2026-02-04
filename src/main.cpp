#include <sil/sil.hpp>
#include <glm/glm.hpp>
#include <algorithm>
#include <cmath>
#include "random.hpp"

void keep_green_only(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void swap_red_blue(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

void black_and_white(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
        color = glm::vec3(gray);
    }
}

void negative(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = glm::vec3(1.f) - color;
    }
}

void degraded(sil::Image& image)
{
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            float t = x / float(image.width() - 1);
            t = std::pow(t, 8.f);
            image.pixel(x, y) = glm::vec3(t);
        }
    }
}

void mirror(sil::Image& image)
{
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width() / 2; ++x)
        {
            int mx = image.width() - 1 - x;
            std::swap(image.pixel(x, y), image.pixel(mx, y));
        }
    }
}

void noisy(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        if (true_with_probability(0.25f)) 
        {
            color = glm::vec3(
                random_float(0.f, 1.f),
                random_float(0.f, 1.f),
                random_float(0.f, 1.f)
            );
        }
    }
}

int main()
{
    set_random_seed(0); 

    sil::Image image{"images/logo.png"};

    //keep_green_only(image);
    //swap_red_blue(image);
    //black_and_white(image);
    //negative(image);
    //sil::Image degraded_image{600, 200};
    //degraded(degraded_image);
    //mirror(image);

    noisy(image);
    image.save("output/noisy.png");

    return 0;
}
