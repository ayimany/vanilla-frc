#include "first/core/robot.hh"

#include <frc2/command/CommandScheduler.h>

namespace vanilla::internal
{

robot::robot() noexcept
{
}

void robot::RobotPeriodic()
{
	frc2::CommandScheduler::GetInstance().Run();
}

void robot::DisabledInit()
{
}

void robot::DisabledPeriodic()
{
}

void robot::DisabledExit()
{
}

void robot::AutonomousInit()
{
}

void robot::AutonomousPeriodic()
{
}

void robot::AutonomousExit()
{
}

void robot::TeleopInit()
{
}

void robot::TeleopPeriodic()
{
}

void robot::TeleopExit()
{
}

void robot::TestInit()
{
	frc2::CommandScheduler::GetInstance().CancelAll();
}

void robot::TestPeriodic()
{
}

void robot::TestExit()
{
}

}