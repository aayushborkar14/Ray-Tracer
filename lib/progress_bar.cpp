#include "progress_bar.h"
#include <iostream>

ProgressBar::ProgressBar(std::string progress_char, std::ostream &out,
                         int bar_width, float progress)
    : progress_char(progress_char), out(out), progress(progress) {
    update(progress);
}

ProgressBar::ProgressBar(std::ostream &out, std::string progress_char,
                         int bar_width, float progress)
    : progress_char(progress_char), out(out), progress(progress) {
    update(progress);
}

void ProgressBar::update(float new_progress) {
    progress = new_progress;
    out << "[";
    int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos)
            out << progress_char;
        else
            out << " ";
    }
    out << "] " << int(progress * 100.0) << " %\r";
    out.flush();
}

void ProgressBar::completed() {
    update(1.0);
    out << std::endl;
}
