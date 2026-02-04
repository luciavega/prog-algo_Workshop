#include <sil/sil.hpp>
#include <glm/glm.hpp>
#include <algorithm> 

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
        color.r = gray;
        color.g = gray;
        color.b = gray;
    }
}

void negative(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 1.f - color.r;
        color.g = 1.f - color.g;
        color.b = 1.f - color.b;
    }
}

int main()
{
    sil::Image image{"images/logo.png"};

    // keep_green_only(image);   
    // swap_red_blue(image);    
    // black_and_white(image); 

    negative(image);        
    image.save("output/negative.png");

    return 0;
}

