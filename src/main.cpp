#include <sil/sil.hpp>
#include <glm/glm.hpp>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
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

void rgb_split(const sil::Image& img, sil::Image& out)
{
    int w = img.width(), h = img.height();
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            int r = std::min(x + 5, w - 1);
            int l = std::max(x - 5, 0);
            out.pixel(x, y) = glm::vec3(img.pixel(r, y).r, img.pixel(x, y).g, img.pixel(l, y).b);
        }
    }
}

void brightness(const sil::Image& img, sil::Image& brighter, sil::Image& darker)
{
    int w = img.width(), h = img.height();
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            glm::vec3 c = img.pixel(x, y);
            brighter.pixel(x, y) = glm::vec3(std::pow(c.r, 0.5f), std::pow(c.g, 0.5f), std::pow(c.b, 0.5f));
            darker.pixel(x, y) = glm::vec3(std::pow(c.r, 1.5f), std::pow(c.g, 1.5f), std::pow(c.b, 1.5f));
        }
    }
}

void disc(sil::Image& image, int offset_x = 0)
{
    int w = image.width(), h = image.height();
    glm::vec2 center(w / 2.f, h / 2.f);
    float radius = std::min(w, h) * 0.3f;
    center.x += offset_x;
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
    int w = image.width(), h = image.height();
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

void animate_disc()
{
    int w = 500;
    int h = 500;
    int frames = 10;
    int max_offset = 100;

    for (int i = 0; i < frames; ++i)
    {
        sil::Image frame{w, h};
        int offset = (i * max_offset) / (frames - 1);
        disc(frame, offset);
        char filename[64];
        sprintf(filename, "output/disc_frame_%02d.png", i);
        frame.save(filename);
    }
}

void rosace()
{
    int w = 500;
    int h = 500;
    sil::Image image{w, h};

    float thickness = 2.f;
    float rayon = w / 4.f;
    float pi = 3.14159265f;
    int num_outer = 6;  

    for (glm::vec3& c : image.pixels()) c = glm::vec3(0.f);

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            float xc = x - w / 2.f;
            float yc = y - h / 2.f;

            bool draw = false;

            float dist_center = std::sqrt(xc * xc + yc * yc);
            if (std::abs(dist_center - rayon) < thickness) draw = true;

            for (int i = 0; i < num_outer; i++)
            {
                float angle = i * 2.f * pi / num_outer;
                float x_offset = rayon * std::cos(angle);
                float y_offset = rayon * std::sin(angle);

                float dx = xc - x_offset;
                float dy = yc - y_offset;
                float dist = std::sqrt(dx * dx + dy * dy);

                if (std::abs(dist - rayon) < thickness) draw = true;
            }

            if (draw)
                image.pixel(x, y) = glm::vec3(1.f); 
        }
    }

    image.save("output/rosace.png");
}

sil::Image create_mosaic(const sil::Image& img, int grid_size)
{
    int w = img.width();
    int h = img.height();
    sil::Image mosaic{w * grid_size, h * grid_size};

    for (int i = 0; i < grid_size * grid_size; ++i)
    {
        int row = i / grid_size;
        int col = i % grid_size;

        for (int y = 0; y < h; ++y)
        {
            for (int x = 0; x < w; ++x)
            {
                mosaic.pixel(col * w + x, row * h + y) = img.pixel(x, y);
            }
        }
    }

    return mosaic;
}

sil::Image mosaic_mirror(const sil::Image& img, int grid_size)
{
    int w = img.width();
    int h = img.height();
    sil::Image mosaic{w * grid_size, h * grid_size};

    for (int row = 0; row < grid_size; ++row)
    {
        for (int col = 0; col < grid_size; ++col)
        {
            for (int y = 0; y < h; ++y)
            {
                for (int x = 0; x < w; ++x)
                {
                    int srcX = (col % 2 == 0) ? x : w - 1 - x;
                    int srcY = (row % 2 == 0) ? y : h - 1 - y;

                    mosaic.pixel(col * w + x, row * h + y) = img.pixel(srcX, srcY);
                }
            }
        }
    }

    return mosaic;
}

void sort_pixels(sil::Image& image)
    {
    int width = image.width();
    int height = image.height();

    auto pixels = image.pixels();

    for (int y = 0; y < height; ++y)
    {
        if (!true_with_probability(0.5f))
            continue;

        int startX = random_int(0, width - 1);
        int segmentLength = random_int(1, 150);
        if (startX + segmentLength > width)
            segmentLength = width - startX;

        std::vector<glm::vec3> segment(segmentLength);
        for (int i = 0; i < segmentLength; ++i)
            segment[i] = pixels[y * width + startX + i];

        std::sort(segment.begin(), segment.end(),
                  [](const glm::vec3& a, const glm::vec3& b) {
                      return (a.r + a.g + a.b) < (b.r + b.g + b.b);
                  });

        for (int i = 0; i < segmentLength; ++i)
            pixels[y * width + startX + i] = segment[i];
    }

    image.pixels() = pixels;
}

int main()
{
    set_random_seed(0);

    sil::Image logo{"images/logo.png"};

    sort_pixels(logo);
    logo.save("output/logo_sorted.png");

    return 0;
}
