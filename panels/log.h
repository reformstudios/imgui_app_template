// log.h
#pragma once
#ifndef LOG_H
#define LOG_H

#include <vector>
#include <string>
#include "imgui.h"

struct ExampleAppLog
{
    ImGuiTextBuffer Buf;        // Buffer to store log messages
    ImGuiTextFilter Filter;     // Text filter for log messages
    ImVector<int> LineOffsets;  // Offsets of each line in the buffer
    bool AutoScroll;            // Flag to enable auto-scrolling

    ExampleAppLog();
    void Clear();
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);   // Add a log message
    void Draw(const char* title, bool* p_open = NULL); // Draw the log window
};

void ShowExampleAppLog(bool* p_open); // Declaration of ShowExampleAppLog function

#endif // LOG_H
