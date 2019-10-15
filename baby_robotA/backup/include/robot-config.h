using namespace vex;

vex::brain Brain;

vex::controller Controller1 = vex::controller();

vex::motor front_right     (vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::motor front_left    (vex::PORT20, vex::gearSetting::ratio18_1, false);
vex::motor back_right    (vex::PORT1, vex::gearSetting::ratio18_1, true);
vex::motor back_left    (vex::PORT10, vex::gearSetting::ratio18_1, false);