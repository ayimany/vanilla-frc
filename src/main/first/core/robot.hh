#pragma once

#include <optional>

#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>

namespace vanilla::internal {

class robot: public frc::TimedRobot {
public:
    robot() noexcept;

    void RobotPeriodic() override;

    void DisabledInit() override;

    void DisabledPeriodic() override;

    void DisabledExit() override;

    void AutonomousInit() override;

    void AutonomousPeriodic() override;

    void AutonomousExit() override;

    void TeleopInit() override;

    void TeleopPeriodic() override;

    void TeleopExit() override;

    void TestInit() override;

    void TestPeriodic() override;

    void TestExit() override;

private:
};

}