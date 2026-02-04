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
        float gray = (color.r + color.g + color.b) / 3.f;
        color.r = color.g = color.b = gray;
    }
}

int main()
{
    sil::Image image{"images/logo.png"};

    keep_green_only(image);  
    swap_red_blue(image);   

    black_and_white(image);  
    image.save("output/black_white.png");

    return 0;
}
