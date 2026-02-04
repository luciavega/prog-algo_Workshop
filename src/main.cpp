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

void rgb_split(const sil::Image& image, sil::Image& new_image)
{
    int w = image.width();
    int h = image.height();
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            int right = std::min(x + 5, w - 1);
            int left  = std::max(x - 5, 0);
            glm::vec3 color;
            color.r = image.pixel(right, y).r;
            color.g = image.pixel(x, y).g;
            color.b = image.pixel(left, y).b;
            new_image.pixel(x, y) = color;
        }
    }
}

void brightness(const sil::Image& image, sil::Image& brighter, sil::Image& darker)
{
    int w = image.width();
    int h = image.height();
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            glm::vec3 color = image.pixel(x, y);
            brighter.pixel(x, y) = glm::vec3(std::pow(color.r, 0.5f), std::pow(color.g, 0.5f), std::pow(color.b, 0.5f));
            darker.pixel(x, y)   = glm::vec3(std::pow(color.r, 1.5f), std::pow(color.g, 1.5f), std::pow(color.b, 1.5f));
        }
    }
}

void disc(sil::Image& image)
{
    int w = image.width();
    int h = image.height();
    glm::vec2 center(w / 2.f, h / 2.f);
    float radius = std::min(w, h) * 0.3f;

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            glm::vec2 pos(x, y);
            float dist = glm::length(pos - center);
            if (dist <= radius)
                image.pixel(x, y) = glm::vec3(1.f);
            else
                image.pixel(x, y) = glm::vec3(0.f);
        }
    }
}

void circle(sil::Image& image)
{
    int w = image.width();
    int h = image.height();
    glm::vec2 center(w / 2.f, h / 2.f);
    float radius = std::min(w, h) * 0.3f;
    float thickness = radius * 0.1f;

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            glm::vec2 pos(x, y);
            float dist = glm::length(pos - center);
            if (dist >= radius - thickness && dist <= radius + thickness)
                image.pixel(x, y) = glm::vec3(1.f); 
            else
                image.pixel(x, y) = glm::vec3(0.f);
        }
    }
}

int main()
{
    set_random_seed(0);

    //sil::Image image{"images/photo.jpg"};
    //keep_green_only(image);
    //swap_red_blue(image);
    //black_and_white(image);
    //negative(image);
    //sil::Image degraded_image{600, 200};
    //degraded(degraded_image);
    //mirror(image);
    //noisy(image);
    //sil::Image rgb_image{image.width(), image.height()};
    //rgb_split(image, rgb_image);
    //sil::Image brighter_image{image.width(), image.height()};
    //sil::Image darker_image{image.width(), image.height()};
    //brightness(image, brighter_image, darker_image);
    //sil::Image disc_image{500, 500};
    //disc(disc_image);

    sil::Image circle_image{500, 500};
    circle(circle_image);
    circle_image.save("output/circle.png");

    return 0;
}
