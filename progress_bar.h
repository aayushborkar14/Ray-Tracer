#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <iostream>

class ProgressBar {
  private:
    std::ostream &out;
    std::string progress_char;
    int bar_width = 70;
    float progress;

  public:
    ProgressBar(std::string progress_char, std::ostream &out = std::cout,
                int bar_width = 70, float progress = 0.0f);

    ProgressBar(std::ostream &out = std::cout, std::string progress_char = "#",
                int bar_width = 70, float progress = 0.0f);

    void update(float new_progress);
};

#endif
