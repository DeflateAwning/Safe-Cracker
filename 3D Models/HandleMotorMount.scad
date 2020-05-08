// Handle Motor Mount for NEMA17 motor onto edge of safe

motorThickness = 33;
safeThickness = 15;
safeDepth = 9.4;

motorW = 42 + 0.5;

motorHoleSpace = 31;
motorHoleD = 3.2; // screw holes

motorBigHoleD = 25;

totalT = motorThickness + safeThickness + 0.3; // gap between bottom of safe panel and top of motor

t = 5;

$fa = 0.3;
$fs = 0.3;

MakeHandleMotorMount();

module MakeHandleMotorMount() {
    difference() {
        translate([-motorW/2, -t, 0]) cube([motorW, t+motorW, t*2 + totalT]);
        
        // Remove space for motor
        translate([-500, 0, t]) cube([1000, 1000, totalT]);
        
        // Remove the safe door part
        translate([-500, safeDepth, -1]) cube([1000, 1000, 20]);
        
        // Remove motor screw holes
        for (x=[1, -1]) for (y=[1, -1]) translate([motorHoleSpace*x/2, motorW/2 + motorHoleSpace*y/2, 30]) {
            cylinder(d=motorHoleD, h=1000);
        }
        
        // Remove big middle hole
        translate([0, motorW/2, 20]) cylinder(d=motorBigHoleD, h=100);
        
        
    }
}