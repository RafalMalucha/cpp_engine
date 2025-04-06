#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

#ifdef __linux__

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>

#endif

#ifdef _WIN32

std::string currentDateTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

#else

std::string currentDateTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm;
    localtime_r(&t, &tm);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

#endif

#ifdef __linux__

void launchNewTerminalOnLinux() {
    if (isatty(STDIN_FILENO)) {
        return;
    }

    std::cout << "Launching in a new terminal...\n";

    char execPath[1024];
    ssize_t len = readlink("/proc/self/exe", execPath, sizeof(execPath) - 1);
    if (len != -1) {
        execPath[len] = '\0';

        std::string command = "x-terminal-emulator -e bash -c \"" + std::string(execPath) + "; exec bash\" &";
        system(command.c_str());

        exit(0);
    } else {
        std::cerr << "Error: Could not determine executable path.\n";
    }
}

void closeTerminalOnLinux() {
    if (isatty(STDIN_FILENO)) {
        std::cout << "Closing terminal...\n";
        // Send SIGHUP to the parent shell (usually the terminal emulator)
        pid_t parentPid = getppid();
        kill(parentPid, SIGHUP);
        exit(0);
    }
}

#endif

float calculateFPS() {
    static double lastTime = glfwGetTime();
    static int frameCount = 0;
    static float fps = 0.0f;

    double currentTime = glfwGetTime();
    frameCount++;

    if (currentTime - lastTime >= 0.5) {
        fps = frameCount / (currentTime - lastTime);
        lastTime = currentTime;
        frameCount = 0;
    }

    return fps;
}