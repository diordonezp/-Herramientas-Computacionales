# include "fmt/printf.h"
# include "fmt/color.h"

int main(void)
{
    fmt::print("I'd rather be {1} than {0}.\n", "right", "happy"); // Positional arguments
    fmt::print("Numbers : {1:24.16e} {0:24.16e}\n", -9.8765, 2.34); // Python + printf like printing
    fmt::printf("Elapsed time: %.2f seconds\n", 1.23); // printf like printing
    
// Text color and style manipulation : https://vorbrodt.blog/2019/03/31/fmt/
    fmt::print(fmt::emphasis::bold, "The text is bold\n");
    fmt::print(fmt::fg(fmt::color::red) | fmt::bg(fmt::color::green), "The color is red and green\n");
    fmt::print("\n");
    
// Alignment
    fmt::print("{:-<30}\n", "left aligned");
    fmt::print("{:->30}\n", "right aligned");
    fmt::print("{:-^30}\n", "centered");
    
    return 0;
}
