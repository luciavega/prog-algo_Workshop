#include <sil/sil.hpp>
#include <glm/glm.hpp>
#include <algorithm>
#include <cmath>

// ===== Ejercicio 1
void keep_green_only(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

// ===== Ejercicio 2
void swap_red_blue(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

// ===== Ejercicio 3
void black_and_white(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
        color = glm::vec3(gray);
    }
}

// ===== Ejercicio 4
void negative(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = glm::vec3(1.f) - color;
    }
}

// ===== Ejercicio 5 (EL QUE SE GUARDA)
void degraded(sil::Image& image)
{
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            float t = x / float(image.width() - 1);
            t = std::pow(t, 2.f); // 👈 mayoría negro, blanco solo al final

            image.pixel(x, y) = glm::vec3(t);
        }
    }
}

int main()
{
    // ----- ejercicios anteriores (NO se guardan)
    sil::Image image{"images/logo.png"};
    keep_green_only(image);
    swap_red_blue(image);
    black_and_white(image);
    negative(image);

    // ----- ejercicio actual (SÍ se guarda)
    sil::Image degraded_image{300, 200};
    degraded(degraded_image);
    degraded_image.save("output/degraded.png");

    return 0;
}
