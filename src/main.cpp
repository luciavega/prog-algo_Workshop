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

int main()
{
    sil::Image image{"images/logo.png"};

    keep_green_only(image); 

    swap_red_blue(image);
    image.save("output/swap_red_blue.png"); 

    return 0;
}
