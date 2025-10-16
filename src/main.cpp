#include "../include/main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

// #include "Subsystems/clampSubsystem.hpp"
#include "Subsystems/driveTrainSubsystem.hpp"
// #include "Subsystems/intakeSubsystem.hpp"
// #include "Subsystems/ladyBrownSubsystem.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "liblvgl/misc/lv_timer.h"
#include "pros/misc.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <chrono>

DriveTrainSubsystem robotDriveTrainSubsystem;
// ClampSubsystem robotClampSubsystem;
// IntakeSubsystem robotIntakeSubsystem('b');
// LadyBrownSubsystem robotLadyBrownSubsystem;

pros::Controller controller(pros::E_CONTROLLER_MASTER);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "I was pressed!");
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::lcd::initialize(); // initialize brain screen

  robotDriveTrainSubsystem.init();
  // robotLadyBrownSubsystem.init();
  robotDriveTrainSubsystem.chassis.calibrate();

  // robotDriveTrainSubsystem.chassis.setPose(0, 0, 0);
  // chassis.calibrate();     // calibrate sensors

  // // the default rate is 50. however, if you need to change the rate, you
  // // can do the following.
  // // lemlib::bufferedStdout().setRate(...);
  // // If you use bluetooth or a wired connection, you will want to have a rate
  // of
  // // 10ms

  // // for more information on how the formatting for the loggers
  // // works, refer to the fmtlib docs

  // // thread to for brain screen and position logging

  // leftMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
  // rightMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
  // pros::Task screenTask([&]() {
  //   while (true) {
  //     // print robot location to the brain screen
  //     pros::lcd::print(0, "X: %f", chassis.getPose().x);         // x
  //     pros::lcd::print(1, "Y: %f", chassis.getPose().y);         // y
  //     pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
  //     // log position telemetry
  //     lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
  //     // delay to save resources
  //     pros::delay(50);
  //   }
  // });

  //   pros::lcd::initialize(); // initialize brain screen
  //   while (true) {           // infinite loop
  //     // print measurements from the adi encoder
  //     pros::lcd::print(1, "vert Sensor: %i", verticalEnc.get_position());
  //     pros::lcd::print(2, "hort Sensor: %i", horizontalEnc.get_position());
  //     pros::delay(10); // delay to save resources. DO NOT REMOVE
  //   }
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

// ASSET(Path1_txt)
// ASSET(Path2_txt)
// ASSET(Path3_txt)
// ASSET(Path4_txt)
// ASSET(Path5_txt)
// ASSET(Path6_txt)

// ASSET(Path7_txt)
// ASSET(Path8_txt)
// ASSET(Path9_txt)
// ASSET(Path10_txt)
// ASSET(Path11_txt)
// ASSET(Path12_txt)

// ASSET(Sk1_txt)
// ASSET(Sk2_txt)
// ASSET(Sk3_txt)
// ASSET(Sk4_txt)
// ASSET(Sk5_txt)
// ASSET(Sk6_txt)
// ASSET(Sk7_txt)
// ASSET(Sk8_txt)
// ASSET(Sk9_txt)
// ASSET(Sk10_txt)
// ASSET(Sk11_txt)
// ASSET(Sk12_txt)
// ASSET(Sk13_txt)
// ASSET(Sk14_txt)
// ASSET(Sk15_txt)
// ASSET(Sk16_txt)

// //   void skillsAuton1() {

// //     /*stuff to optimize
// //     - maybe decrease clamp delay + speed
// //     - 3 in a row time
// //     - fix far ring??
// //     - shorter intake time?
// //     */
// //     // beginning pose
// //     robotDriveTrainSubsystem.chassis.setPose(-59, 0, 90);
// //     robotClampSubsystem.ClampUp();

// //       //SECTION 1

// //     //score on alliance wall

// //     robotIntakeSubsystem.turnOnIntake();
// //     pros::delay(500);
// //     robotIntakeSubsystem.turnOffIntake();

// //     //drive forward
// //     robotDriveTrainSubsystem.chassis.moveToPoint(-48, 0, 5000);

// //     //drive to and clamp mogoal
//     robotDriveTrainSubsystem.chassis.turnToHeading(0,1000);
//     robotDriveTrainSubsystem.chassis.moveToPoint(-48, -24, 5000,
//     {.forwards=false, .maxSpeed=60}); pros::delay(600);//test
//     robotClampSubsystem.ClampDown();
//     pros::delay(200);

//     //ring 1
//     robotIntakeSubsystem.turnOnIntake();
//     robotDriveTrainSubsystem.chassis.moveToPoint(-24, -24, 5000 );

//     //drive to far ring & intake
//     robotDriveTrainSubsystem.chassis.moveToPoint(-24, -50, 250);//avoid
//     ladder (DO NOT DELETE) robotDriveTrainSubsystem.chassis.moveToPoint(24,
//     -50, 5000, {.forwards = true, .maxSpeed = 80}); pros::delay(400);
//     //robotDriveTrainSubsystem.chassis.moveToPoint(28, -54, 1500, {.forwards
//     = true, .maxSpeed = 80});

//     //intake all rings in a line (3)
//     robotDriveTrainSubsystem.chassis.moveToPoint(-48, -48,5000,
//     {.maxSpeed=80});

//     robotDriveTrainSubsystem.chassis.moveToPoint(-66, -48,
//     5000,{.maxSpeed=60}); pros::delay(400);//lowermaybe

//     // back up
//     robotDriveTrainSubsystem.chassis.moveToPoint(-52, -42,
//     5000,{.forwards=false,.maxSpeed=80});

//     //get the last ring
//     robotDriveTrainSubsystem.chassis.turnToHeading(180, 600);//testing
//     timeout shenanigans robotDriveTrainSubsystem.chassis.moveToPoint(-48,
//     -62, 5000, {.forwards = true, .maxSpeed = 80}); pros::delay(700);//DO NOT
//     CHANGE THIS TIMING OR IMA RAPE YOU

//     //back up
//     robotDriveTrainSubsystem.chassis.moveToPoint(-48, -58,
//     5000,{.forwards=false}); pros::delay(700);//DO NOT CHANGE THIS
//     EITHER//test

//     //avoid the hook from getting trapped in the mogoal
//     robotIntakeSubsystem.reverseIntake();
//     pros::delay(50);
//     robotIntakeSubsystem.turnOffIntake();

//     //shove mogoal in corner
//     robotDriveTrainSubsystem.chassis.moveToPoint(-60, -52, 2000,{.forwards =
//     false});//flipped robotClampSubsystem.ClampUp();

//       // SECTION 2

//     //move to the other side
//     robotDriveTrainSubsystem.chassis.moveToPoint(-48, 0, 8000);

//     //clamp mogo 2
//     robotDriveTrainSubsystem.chassis.moveToPoint(-48, 24, 8000,
//     {.forwards=false, .maxSpeed=60}); pros::delay(2200);//maybe lower to 600
//     robotClampSubsystem.ClampDown();
//     pros::delay(200);

//     //drive to first ring
//     robotIntakeSubsystem.turnOnIntake();
//     robotDriveTrainSubsystem.chassis.moveToPoint(-24, 24, 5000);

//     // drive to far ring and intake
//     robotDriveTrainSubsystem.chassis.moveToPoint(-24, 50, 250);
//     robotDriveTrainSubsystem.chassis.moveToPoint(24, 50, 5000, {.forwards =
//     true, .maxSpeed = 90}); pros::delay(400);
//     robotDriveTrainSubsystem.chassis.moveToPoint(24, 50, 1500, {.forwards =
//     true, .maxSpeed = 80});

//     //intake all rings in a line (3)
// <<<<<<< HEAD
//     robotDriveTrainSubsystem.chassis.moveToPoint(-58, 48, 5000, {.forwards =
//     true, .maxSpeed=100}); pros::delay(2000);

//     // back up
//     robotDriveTrainSubsystem.chassis.moveToPoint(-40, 40, 5000, {.forwards =
//     false, .maxSpeed = 127});

//     // get last ring
//     robotDriveTrainSubsystem.chassis.turnToHeading(0, 5000);
//     robotDriveTrainSubsystem.chassis.moveToPoint(-40, 64, 5000, {.forwards =
//     true, .maxSpeed = 90}); pros::delay(1500);
// =======
//     robotDriveTrainSubsystem.chassis.moveToPoint(-48,48,5000,{.maxSpeed=80});
//     robotDriveTrainSubsystem.chassis.moveToPoint(-66, 48,
//     5000,{.maxSpeed=80}); pros::delay(400);

//     // back up
//     robotDriveTrainSubsystem.chassis.moveToPoint(-52, 42, 5000, {.forwards =
//     false, .maxSpeed = 80});

//     // get last ring
//     robotDriveTrainSubsystem.chassis.turnToHeading(0, 600);
//     robotDriveTrainSubsystem.chassis.moveToPoint(-48, 62, 5000, {.forwards =
//     true, .maxSpeed = 80}); pros::delay(700);
// >>>>>>> b5bbb98 (yay)

//     //back up and align the robot to the corner
//     robotDriveTrainSubsystem.chassis.moveToPoint(-48, 58, 5000, {.forwards =
//     false}); pros::delay(700);
//     //stop hook before it gets stuck
//     robotIntakeSubsystem.turnOffIntake();

//     //place the mogoal in the corner
// <<<<<<< HEAD
//     robotDriveTrainSubsystem.chassis.moveToPoint(-48, 66, 1200,{.forwards =
//     false});
// =======
//     robotDriveTrainSubsystem.chassis.moveToPoint(-60, 52, 2000,{.forwards =
//     false});
// >>>>>>> b5bbb98 (yay)
//     robotClampSubsystem.ClampUp();

//       //SECTION 3

//     robotIntakeSubsystem.turnOnIntake();
//     robotDriveTrainSubsystem.chassis.moveToPoint(0, 48, 2000);
//     robotDriveTrainSubsystem.chassis.moveToPoint(24, 24, 5000,
//     {.forwards=true, .maxSpeed=80}); //24, 24
//     //pros::delay(600);

//     pros::delay(1400);//was 1000
//     robotIntakeSubsystem.turnOffIntake();
//     robotDriveTrainSubsystem.chassis.turnToHeading(315, 5000);

//     //mogo 3 (center mogo)
//     robotDriveTrainSubsystem.chassis.moveToPoint(48, 0, 5000,
//     {.forwards=false, .maxSpeed=60});

//     //possible +8 adjustment required
//     pros::delay(1000);
//     robotClampSubsystem.ClampDown();
//     pros::delay(200);
// <<<<<<< HEAD

//     //intake all rings in a line (2)

//     robotDriveTrainSubsystem.chassis.moveToPoint(48, 60, 5000, {.forwards =
//     true, .maxSpeed=60}); pros::delay(1000);

//     //get the retard ring
//     robotDriveTrainSubsystem.chassis.moveToPoint(40, 40, 5000, {.forwards =
//     true, .maxSpeed=90}); robotDriveTrainSubsystem.chassis.moveToPoint(62,
//     48, 3000, {.forwards = true, .maxSpeed=70}); pros::delay(700);
//     //hit the corner

//     robotDriveTrainSubsystem.chassis.moveToPoint(48, 48,
//     5000,{.forwards=false});
//     robotDriveTrainSubsystem.chassis.turnToHeading(45,1000);
//     robotIntakeSubsystem.turnOffIntake();
//     robotDriveTrainSubsystem.chassis.moveToPoint(58, 58, 000,{.forwards =
//     false, .maxSpeed=100}); pros::delay(800); robotClampSubsystem.ClampUp();

//         //fourth side
//         //grabs mogo intake side
//     robotDriveTrainSubsystem.chassis.moveToPoint(62, -30, 5000,
//     {.forwards=true, .maxSpeed=50});
//     robotDriveTrainSubsystem.chassis.moveToPoint(60, -60, 2000,
//     {.forwards=true});

//     // 5th section

//     robotDriveTrainSubsystem.chassis.moveToPoint(0, -40, 4000, {.forwards =
//     true, .maxSpeed=90}); robotDriveTrainSubsystem.chassis.turnToHeading(180,
//     500); robotDriveTrainSubsystem.chassis.moveToPoint(0, -60, 4000,
//     {.forwards = true, .maxSpeed=90}); pros::delay(500);
//     robotIntakeSubsystem.turnOnIntake();
//     pros::delay(700);
//     robotIntakeSubsystem.turnOffIntake();
//     robotLadyBrownSubsystem.setAngle(20);

// =======
//     robotIntakeSubsystem.turnOnIntake();

//     //moves to 2nd ring
//     robotDriveTrainSubsystem.chassis.turnToHeading(315, 5000);
//     robotDriveTrainSubsystem.chassis.moveToPoint(24, -24, 5000);

//     robotDriveTrainSubsystem.chassis.turnToHeading(135,3000);
//     robotDriveTrainSubsystem.chassis.moveToPoint(48, -48, 5000);

//     robotDriveTrainSubsystem.chassis.turnToHeading(90,3000);
//     robotDriveTrainSubsystem.chassis.moveToPoint(60, -52, 2000,{.forwards =
//     false});

//     // //intake all rings in a line (2)
//     // robotIntakeSubsystem.turnOnIntake();
//     // robotDriveTrainSubsystem.chassis.moveToPoint(48, 60, 5000, {.forwards
//     = true, .maxSpeed=80});
//     // pros::delay(400);

//     // //get the retard ring
//     // // back up
//     // robotDriveTrainSubsystem.chassis.moveToPoint(42, 52, 5000, {.forwards
//     = false, .maxSpeed = 80});

//     // // get last ring
//     // robotDriveTrainSubsystem.chassis.turnToHeading(0, 600);
//     // robotDriveTrainSubsystem.chassis.moveToPoint(62, 48, 5000, {.forwards
//     = true, .maxSpeed = 80});
//     // pros::delay(400);

//     // //place the mogoal in the corner
//     // robotDriveTrainSubsystem.chassis.moveToPoint(52, 60, 1000,{.forwards =
//     false});
//     // robotClampSubsystem.ClampUp();

//     // //fourth side
//     // //grabs mogo intake side
//     // robotDriveTrainSubsystem.chassis.moveToPoint(62, -30, 5000,
//     {.forwards=true, .maxSpeed=50});
//     // robotDriveTrainSubsystem.chassis.moveToPoint(60, -60, 2000,
//     {.forwards=true});

//     // // 5th section

//     // robotDriveTrainSubsystem.chassis.moveToPoint(0, -40, 4000, {.forwards
//     = true, .maxSpeed=90});
//     // robotDriveTrainSubsystem.chassis.turnToHeading(180, 500);
//     // robotDriveTrainSubsystem.chassis.moveToPoint(0, -60, 4000, {.forwards
//     = true, .maxSpeed=90});
//     // pros::delay(500);
//     // robotIntakeSubsystem.turnOnIntake();
//     // pros::delay(700);
//     // robotIntakeSubsystem.turnOffIntake();
//     // robotLadyBrownSubsystem.setAngle(20);

// >>>>>>> b5bbb98 (yay)

//       //ram
//       // robotDriveTrainSubsystem.chassis.moveToPoint(60, 50,
//       5000,{.forwards=false});
//       // pros::delay(500);
//       // robotDriveTrainSubsystem.chassis.moveToPoint(60, 56,5000);
//       // pros::delay(500);

//       // //if time add alliance stake or add more rings to mogo (24,48)()
//       //   robotDriveTrainSubsystem.chassis.moveToPoint(48, -24,
//       5000,{.forwards=false});
//       //   robotDriveTrainSubsystem.chassis.moveToPoint(48,
//       -68,5000,{.maxSpeed=70});
//       //   pros::delay(800);
//       //   robotDriveTrainSubsystem.chassis.moveToPoint(52, -52,
//       5000,{.forwards=false});
//       //   robotDriveTrainSubsystem.chassis.turnToHeading(315, 5000);
//       // //place last mogo in corner
//       // robotDriveTrainSubsystem.chassis.moveToPoint(60,-60,
//       5000,{.forwards=false});

//     //OPTION2

//     // robotDriveTrainSubsystem.chassis.moveToPoint(0, -46, 5000);
//     // robotLadyBrownSubsystem.setAngle(3.5);//prime ladybrown
//     // pros::delay(500);
//     // robotDriveTrainSubsystem.chassis.turnToHeading(180,5000);
//     // robotDriveTrainSubsystem.chassis.moveToPoint(0, -64, 5000);

//     // //ladybrown
//     // //robotDriveTrainSubsystem.chassis.moveToPoint(0, -63, 6000,
//     //   //{.forwards=true, .maxSpeed=50});
//     // pros::delay(1000);

//     //       //scores
//     // robotIntakeSubsystem.reverseIntake();
//     //     pros::delay(100);
//     //     robotIntakeSubsystem.turnOffIntake();
//     //     pros::delay(70);
//     //     robotLadyBrownSubsystem.setAngle(16);
//     //     pros::delay(1000);
//     // robotDriveTrainSubsystem.chassis.moveToPoint(0, -58, 5000,
//     //    {.forwards = false, .maxSpeed = 50}); // moves back
//     //   //  pros::delay(100);
//     //   //  robotDriveTrainSubsystem.chassis.moveToPoint(0, -63, 5000);
//     //    pros::delay(100);
//     //    robotLadyBrownSubsystem.setAngle(0);

// }
// void skillsAuton(){
//   robotClampSubsystem.ClampUp();
//       //setpose
//       robotDriveTrainSubsystem.chassis.setPose(-59, 0, 90);
//       //alliance wall
//       robotIntakeSubsystem.turnOnIntake();
//       pros::delay(600);
//       robotIntakeSubsystem.turnOffIntake();

//       //move forward
//       robotDriveTrainSubsystem.chassis.moveToPoint(-48, 0, 5000);

//       //move to mogo and clamp
//       robotDriveTrainSubsystem.chassis.turnToHeading(0,1000);
//       robotDriveTrainSubsystem.chassis.moveToPoint(-48, -24, 5000,
//       {.forwards=false, .maxSpeed=50}); pros::delay(900);//testing value
//       robotClampSubsystem.ClampDown();
//       pros::delay(200);

//       //drive to ring??
//       robotDriveTrainSubsystem.chassis.moveToPoint(-20, -24, 5000, {.forwards
//       = true, .maxSpeed=80}); robotIntakeSubsystem.turnOnIntake();

//       //keep intake on drive to lb ring nigga
//       robotDriveTrainSubsystem.chassis.moveToPoint(2, -62, 5000, {.forwards =
//       true}); robotDriveTrainSubsystem.chassis.moveToPoint(0, -52, 5000,
//       {.forwards = false, .maxSpeed=100});

//     //intake all rings in a line (3)

//     robotDriveTrainSubsystem.chassis.turnToHeading(180,5000);
//       robotDriveTrainSubsystem.chassis.moveToPoint(-60, -50, 5000, {.forwards
//       = true, .maxSpeed=60}); pros::delay(1000);

//       //get the retard ring
//       robotDriveTrainSubsystem.chassis.moveToPoint(-40, -40, 5000, {.forwards
//       = true, .maxSpeed=80});
//       robotDriveTrainSubsystem.chassis.moveToPoint(-48, -64, 3000, {.forwards
//       = true, .maxSpeed=90}); pros::delay(500);//testing value
//     //hit the corner

//     robotDriveTrainSubsystem.chassis.moveToPoint(-48, -48,
//     5000,{.forwards=false});
//     robotDriveTrainSubsystem.chassis.turnToHeading(45,1000);
//     robotIntakeSubsystem.turnOffIntake();
//       robotDriveTrainSubsystem.chassis.moveToPoint(-58, -58, 5000,{.forwards
//       = false, .maxSpeed=80}); pros::delay(600);//testing value
//       robotIntakeSubsystem.reverseIntake();
//       robotClampSubsystem.ClampUp();

//       //second side
//       //move to mogo and clamp
//       robotDriveTrainSubsystem.chassis.turnToHeading(180,4000);
//       robotDriveTrainSubsystem.chassis.moveToPoint(-48, -4,
//       5000,{.forwards=false,.maxSpeed=90});

//       robotDriveTrainSubsystem.chassis.moveToPoint(-40, 28, 5000,
//       {.forwards=false, .maxSpeed=50});
//       //possible +8 adjustment required
//       pros::delay(900);
//       robotClampSubsystem.ClampDown();
//       pros::delay(200);

//       //drive to ring??
//       robotDriveTrainSubsystem.chassis.moveToPoint(-20, 24, 5000, {.forwards
//       = true, .maxSpeed=80}); robotIntakeSubsystem.turnOnIntake();

//       //keep intake on drive to lb ring nigga
//       robotDriveTrainSubsystem.chassis.moveToPoint(-0, 60, 5000, {.forwards =
//       true}); robotDriveTrainSubsystem.chassis.moveToPoint(-0,52, 5000,
//       {.forwards = false, .maxSpeed=100});

//     //intake all rings in a line (3)

//       robotDriveTrainSubsystem.chassis.moveToPoint(-60, 48, 5000, {.forwards
//       = true, .maxSpeed=60}); pros::delay(1000);

//       //get the retard ring
//       robotDriveTrainSubsystem.chassis.moveToPoint(-40, 40, 5000, {.forwards
//       = true, .maxSpeed=80});
//       robotDriveTrainSubsystem.chassis.moveToPoint(-48, 62, 3000, {.forwards
//       = true, .maxSpeed=70}); pros::delay(700);
//     //hit the corner

//     robotDriveTrainSubsystem.chassis.moveToPoint(-48, 48,
//     5000,{.forwards=false});
//     robotDriveTrainSubsystem.chassis.turnToHeading(45,1000);
//     robotIntakeSubsystem.turnOffIntake();
//       robotDriveTrainSubsystem.chassis.moveToPoint(-58, 58, 5000,{.forwards =
//       false, .maxSpeed=80}); pros::delay(800); robotClampSubsystem.ClampUp();

//           /////////////////////////
//   //Third Side
// //

//   //drive to ring?? run short intake btw
//   robotDriveTrainSubsystem.chassis.moveToPoint(30, 24, 5000, {.forwards =
//   true, .maxSpeed=110}); robotIntakeSubsystem.turnOnIntake();
//   pros::delay(50);
//   robotIntakeSubsystem.turnOffIntake();

//       //grabs gay ass slutring
//       robotDriveTrainSubsystem.chassis.moveToPoint(29, 19,
//       5000,{.forwards=false});

//       robotDriveTrainSubsystem.chassis.moveToPoint(54, -6, 5000,
//       {.forwards=false, .maxSpeed=80});
//       //possible +8 adjustment required

//       robotClampSubsystem.ClampDown();
//       pros::delay(200);

//     //intake all rings in a line (2)

//       robotDriveTrainSubsystem.chassis.moveToPoint(48, 60, 5000, {.forwards =
//       true, .maxSpeed=60}); pros::delay(1000);

//       //get the retard ring
//       robotDriveTrainSubsystem.chassis.moveToPoint(40, 40, 5000, {.forwards =
//       true, .maxSpeed=90}); robotDriveTrainSubsystem.chassis.moveToPoint(62,
//       48, 3000, {.forwards = true, .maxSpeed=70}); pros::delay(700);
//     //hit the corner

//     robotDriveTrainSubsystem.chassis.moveToPoint(48, 48,
//     5000,{.forwards=false});

//     robotIntakeSubsystem.turnOffIntake();
//       robotDriveTrainSubsystem.chassis.moveToPoint(58, 58, 000,{.forwards =
//       false, .maxSpeed=100}); pros::delay(800);
//       robotClampSubsystem.ClampUp();

//      //fourth side
//      //grabs mogo intake side
//       robotDriveTrainSubsystem.chassis.moveToPoint(62, -30, 5000,
//       {.forwards=true, .maxSpeed=50});

//     //hit the corner

//     robotIntakeSubsystem.turnOffIntake();
//       robotDriveTrainSubsystem.chassis.moveToPoint(60, -60, 4000,{.forwards =
//       true, .maxSpeed=80}); pros::delay(800); robotClampSubsystem.ClampUp();

// }
// void s(){

//       //////////////////////////////////
//       robotDriveTrainSubsystem.chassis.moveToPoint(0, 36,20000);

//       //grab ring
//       robotIntakeSubsystem.turnOnIntake();
//       robotDriveTrainSubsystem.chassis.moveToPoint(24,
//       24,2000,{.maxSpeed=80}); pros::delay(200);
//       robotIntakeSubsystem.turnOffIntake();

//       //move to mogo
//       robotDriveTrainSubsystem.chassis.moveToPoint(42,
//       6,2000,{.forwards=false});
//       robotDriveTrainSubsystem.chassis.moveToPoint(48,
//       0,2000,{.forwards=false,.maxSpeed=60}); pros::delay(1200);
//       robotClampSubsystem.ClampDown();
//       pros::delay(400);
//       robotIntakeSubsystem.turnOnIntake();

//       //intake two stacked rings (mogo one and keep one for alliance)
//       robotDriveTrainSubsystem.chassis.moveToPoint(48, 38,2000);
//       robotDriveTrainSubsystem.chassis.moveToPoint(48,
//       44,2000,{.maxSpeed=60});
//               //pros::delay(200); //if double stack dont work
//               //robotIntakeSubsystem.turnOffIntake();
//       pros::delay(400);
//       robotDriveTrainSubsystem.chassis.moveToPoint(48,
//       60,2000,{.maxSpeed=60}); pros::delay(200);
//       robotIntakeSubsystem.turnOffIntake();

//       //drop mogo
//       robotDriveTrainSubsystem.chassis.moveToPoint(48,
//       54,2000,{.forwards=false});
//       robotDriveTrainSubsystem.chassis.moveToPoint(60,
//       60,2000,{.forwards=false}); pros::delay(100);
//       robotClampSubsystem.ClampUp();

//       //Alliance stake

//       robotDriveTrainSubsystem.chassis.moveToPoint(52, 0,2000);
//       robotDriveTrainSubsystem.chassis.turnToHeading(90, 1000);
//       robotDriveTrainSubsystem.chassis.moveToPoint(58,
//       0,2000,{.forwards=false});

//       robotIntakeSubsystem.turnOnIntake();
//       pros::delay(1000);
//       robotIntakeSubsystem.turnOffIntake();

//       robotDriveTrainSubsystem.chassis.moveToPoint(48, 0,2000);

//       //push blue mogo into corner

//       robotDriveTrainSubsystem.chassis.moveToPoint(60, -24,2000);
//       robotDriveTrainSubsystem.chassis.moveToPoint(60, -60,2000);

// }
// void gameAutonRed(){
// /** */

// //Alliance Stake + 1 (Mogo) w/ corner clear & ladder, RED NEG CORNER

// robotDriveTrainSubsystem.chassis.setPose(-54, 13, 220);

//   robotDriveTrainSubsystem.chassis.moveToPoint(-60, 4, 4000);

//   robotLadyBrownSubsystem.setAngle(20);//ladybrown alliance stake
//   pros::delay(1000);
//   robotLadyBrownSubsystem.setAngle(0);
//   pros::delay(200);

//  //alliance ring
//   //robotDriveTrainSubsystem.chassis.moveToPoint(-48,12, 4000,{.forwards =
//   false});

//   //robotIntakeSubsystem.liftIntakePiston();
//   //robotIntakeSubsystem.turnOnIntake();
//   //robotDriveTrainSubsystem.chassis.turnToHeading(180,1000); //////
//   //robotDriveTrainSubsystem.chassis.moveToPoint(-48,4, 4000,{.maxSpeed =
//   60});
//   //pros::delay(150);
//   //robotIntakeSubsystem.turnOffIntake();

// //mogo1
//   robotClampSubsystem.ClampUp();
//   robotDriveTrainSubsystem.chassis.moveToPoint(-48,12, 4000,{.forwards =
//   false});

//   robotDriveTrainSubsystem.chassis.moveToPoint(-20,24, 4000,{.forwards =
//   false,.maxSpeed = 60}); pros::delay(1200); robotClampSubsystem.ClampDown();
//   pros::delay(200);

//   //mogo intake
//   robotIntakeSubsystem.turnOnIntake();

//   //robotDriveTrainSubsystem.chassis.moveToPoint(-12, 44,5000);//ring one,
//   pluss 44 to make it more straight to the ring
//   robotDriveTrainSubsystem.chassis.moveToPoint(0, 42,5000, {.maxSpeed =
//   60});//ring one pros::delay(100);
//   robotDriveTrainSubsystem.chassis.moveToPoint(-16, 30,2000,{.forwards =
//   false});
//   //pros::delay(100);

//   robotDriveTrainSubsystem.chassis.moveToPoint(-22, 52,2000, {.maxSpeed =
//   60});//ring two
//   //pros::delay(100);

//   robotDriveTrainSubsystem.chassis.turnToHeading(80, 500);

//   robotDriveTrainSubsystem.chassis.moveToPoint(0, 56,5000, {.maxSpeed =
//   60});//ring three

//   pros::delay(300);

//   //goes to ladder
//   robotDriveTrainSubsystem.chassis.moveToPoint(-24, 8,2000);
//   robotLadyBrownSubsystem.setAngle(14);

// }

void gameAutonBlue() {
  // 11pt solo awp
  robotDriveTrainSubsystem.chassis.setPose(54, -13, 40);

  robotDriveTrainSubsystem.chassis.moveToPoint(60, -4, 4000);

  // robotLadyBrownSubsystem.setAngle(20); // ladybrown alliance stake
  // pros::delay(1000);
  // robotLadyBrownSubsystem.setAngle(0);
  // pros::delay(200);

  // moves back to starting position
  robotDriveTrainSubsystem.chassis.moveToPoint(54, -13, 5000,
                                               {.forwards = false});
  robotDriveTrainSubsystem.chassis.turnToHeading(180, 500);

  // mogo1
  // robotClampSubsystem.ClampUp();
  robotDriveTrainSubsystem.chassis.moveToPoint(48, -12, 4000,
                                               {.forwards = false});

  robotDriveTrainSubsystem.chassis.moveToPoint(
      24, 24, 4000, {.forwards = false, .maxSpeed = 60});
  pros::delay(1200);
  // robotClampSubsystem.ClampDown();
  // pros::delay(200);

  // mogo intake
  // robotIntakeSubsystem.turnOnIntake();

  // robotDriveTrainSubsystem.chassis.moveToPoint(-12, 44,5000);//ring one,
  // pluss 44 to make it more straight to the ring
  robotDriveTrainSubsystem.chassis.moveToPoint(2, 44, 5000,
                                               {.maxSpeed = 60}); // ring one
  pros::delay(100);
  robotDriveTrainSubsystem.chassis.moveToPoint(16, 30, 2000,
                                               {.forwards = false});
  // pros::delay(100);

  robotDriveTrainSubsystem.chassis.moveToPoint(22, 52, 2000,
                                               {.maxSpeed = 60}); // ring two
  // pros::delay(100);

  robotDriveTrainSubsystem.chassis.turnToHeading(280, 500);

  robotDriveTrainSubsystem.chassis.moveToPoint(2, 56, 5000,
                                               {.maxSpeed = 60}); // ring three
  robotDriveTrainSubsystem.chassis.moveToPoint(24, 56, 5000,
                                               {.forwards = false});

  pros::delay(300);
  // go to ladder
  robotDriveTrainSubsystem.chassis.moveToPoint(24, 8, 2000);
  // robotLadyBrownSubsystem.setAngle(16);
}

void autonomous() {
  // gameAutonRed();
  gameAutonBlue();
  // skillsAuton();
}

/**
 * Runs the operator control code. This function will be started in its own
 * task with the default priority and stack size whenever the robot is enabled
 * via the Field Management System or the VEX Competition Switch in the
 * operator control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart
 * the task, not resume it from where it left off.
 */
void opcontrol() {
  while (true) {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      robotDriveTrainSubsystem.chassis.setPose(0, 0, 0);
      robotDriveTrainSubsystem.chassis.turnToHeading(90, 2000);
    }

    // get joystick positions
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    robotDriveTrainSubsystem.drive(leftY, rightX);

    // if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
    //   robotClampSubsystem.ClampDown();
    // if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
    //   robotClampSubsystem.ClampUp();

    // // Execute Intake Commands
    // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    //   robotIntakeSubsystem.turnOnIntake();
    // else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
    //   robotIntakeSubsystem.reverseIntake();
    // else
    //   robotIntakeSubsystem.turnOffIntake();

    // // Execute Intake Piston Commands
    // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    //   robotIntakeSubsystem.liftIntakePiston();
    // else
    //   robotIntakeSubsystem.lowerIntakePiston();

    // // Execute Lady Brown Commands
    // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
    //   robotLadyBrownSubsystem.setAngle(0);
    // else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
    //   robotIntakeSubsystem.reverseIntake();
    //   pros::delay(100);
    //   robotIntakeSubsystem.turnOffIntake();
    //   robotLadyBrownSubsystem.setAngle(8);

    // }
    // else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
    //   robotLadyBrownSubsystem.setAngle(3.75);

    // } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    //   robotIntakeSubsystem.reverseIntake();
    //   pros::delay(100);
    //   robotIntakeSubsystem.turnOffIntake();
    //   robotLadyBrownSubsystem.setAngle(18);
    // }

    //  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
    //    robotDriveTrainSubsystem.chassis.turnToHeading(90, 1000);

    // else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
    //   robotDriveTrainSubsystem.chassis.turnToHeading(0, 1000);

    // }
    // else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
    //   robotDriveTrainSubsystem.chassis.moveToPoint(
    //       -60,
    //       10, 2000);

    // } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    //   robotDriveTrainSubsystem.chassis.moveToPoint(
    //       60,
    //       60, 2000);
    // }

    // // Execute Doinker Commands
    // if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    //   robotIntakeSubsystem.liftDoinker();
    // if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
    //   robotIntakeSubsystem.dropDoinker();

    // move the chassis with curvature drive
    // chassis.arcade(leftY, rightX, false, 0.55);
    // delay to save resources
    pros::delay(10);
  }
}