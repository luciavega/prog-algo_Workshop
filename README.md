# prog-algo_Workshop

⭐ keep only green

Sets red and blue to 0, keeping only green.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output/keep_green_only.png" width="200" />
</p>

⭐ exchange channels

Swaps red and blue channels using `std::swap`.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\swap_red_blue.png" width="200" />
</p>

⭐ black & white

Converts image to grayscale using a weighted sum of RGB.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\black_white.png" width="200" />
</p>

⭐ negative

Inverts colors using `1 - color`.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\negative.png" width="200" />
</p>

⭐ degraded 

Creates a horizontal gradient using `std::pow`.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\degraded.png" width="200" />
</p>

⭐⭐ mirror 

Mirrors image horizontally using `std::swap`.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\mirror.png" width="200" />
</p>

⭐⭐ noisy image 

Adds random noise using `true_with_probability` and `random_float`.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\noisy.png" width="200" />
</p>

⭐⭐ 90° rotation

Rotates image using pixel indexing into a new image.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\rotate_90.png" width="200" />
</p>

⭐⭐ RGB split

Shifts red and blue channels using `std::min` and `std::max`.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\rgb_split.png" width="200" />
</p>

⭐⭐ brightness

Adjusts brightness using `std::pow` for brighter and darker images.

<p float="left">
  <img src="images\photo.jpg" width="200" />
  <img src="output\brightness_brighter.png" width="200" />
  <img src="output\brightness_darker.png" width="200" />
</p>

⭐⭐(⭐) disc

Draws a white disc using `glm::length` and `std::min`.

<p float="left">
  <img src="output\disc.png" width="200" />
</p>

⭐ circle

Draws a circle using `glm::length` and `std::min`.

<p float="left">
  <img src="output\circle.png" width="200" />
</p>

⭐⭐ animation

Generates frames of a moving disc using a loop and `sprintf`.

<p float="left">
  <img src="output\animation.gif" width="200" />
</p>

⭐⭐⭐ rosace

Draws a rosace pattern using `std::sqrt`, `std::cos`, and `std::sin`.

<p float="left">
  <img src="output\rosace.png" width="200" />
</p>

⭐⭐ mosaic

Tiles the image `grid_size`×`grid_size` to create a mosaic.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\mosaic.png" width="200" />
</p>

⭐⭐⭐⭐ mosaic mirror

Tiles and mirrors the image `grid_size`×`grid_size`.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\mosaic_mirror.png" width="200" />
</p>

⭐⭐⭐ sorting of pixels 

Sorts random horizontal segments using `std::sort` and `true_with_probability`.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\logo_sorted.png" width="200" />
</p>

⭐⭐⭐(⭐) degraded in the color space Lab 

Creates a horizontal gradient blending red → yellow → green in **OKLab** space using:
- `srgb_to_linear` / `linear_to_srgb` for color conversion
- `linear_rgb_to_oklab` / `oklab_to_linear_rgb` for OKLab
- `glm::mix` for interpolation

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\degraded_lab.png" width="200" />
</p>

⭐⭐⭐⭐ vortex 

Applies a vortex effect using `std::sqrt`, `std::cos`, and `std::sin`.

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\logo_vortex.png" width="200" />
</p>

⭐⭐⭐⭐ convolution

Applies a 2D convolution to the image using a kernel, e.g., for blur, sharpen, emboss, or outline.  

Uses `std::clamp` to handle edges and `glm::clamp` to keep colors in [0,1].

<p float="left">
  <img src="images/logo.png" width="200" />
  <img src="output\logo_blur.png" width="200" />
</p>

<p float="left">
  <img src="output\logo_emboss.png" width="200" />
  <img src="output\logo_outline.png" width="200" />
  <img src="output\logo_sharpen.png" width="200" />
</p>
