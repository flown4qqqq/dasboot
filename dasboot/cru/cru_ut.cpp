#include <gtest/gtest.h>

#include <iostream>
#include <iomanip>

#include <dasboot/cru/common.hpp>
#include <dasboot/cru/os.hpp>

TEST(CruUt, CheckMakeString) {
    std::string message;
    message += "word ";
    message += std::to_string(1);
    message += " 0.755";
    message += "\n";

    std::string str = MakeString() << std::fixed << std::setprecision(3) << "word " << 1 << " " << 0.755 << "\n";
    EXPECT_EQ(message, str);
}

TEST(CruUt, CheckTPipeBase) {
    NOs::TPipe pipe;
    std::string message = "Hello, World!";
    pipe.Write(message);
    std::string readMessage = pipe.ReadAll();
    EXPECT_EQ(message, readMessage);
}

TEST(CruUt, CheckTPipeWithFork) {
    NOs::TPipe pipe;
    std::string message = "Hello, World!";
    pid_t pid = fork();
    if (pid == 0) {
        pipe.CloseWrite();
        std::string readMessage = pipe.ReadAll();
        EXPECT_EQ(message, readMessage);
        exit(0);
    } else if (pid > 0) {
        pipe.CloseRead();
        pipe.Write(message);
        waitpid(pid, nullptr, 0);
    } else {
        FAIL() << "Fork failed";
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();
    return result;
}
