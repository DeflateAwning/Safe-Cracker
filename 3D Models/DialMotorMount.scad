// Dial Motor Mount for NEMA17 motor onto top of safe, affixed with glue to metal surface


safeThickness = 15; // thickness of edge part
safeDepth = 9.4; // depth of edge part

// Motor Config
//motorW = 42 + 0.5; // real width
motorW = 38; // width of middle part, for savings
motorHoleSpace = 31;
motorHoleD = 3.2; // screw holes
motorBigHoleD = 25;

topT = 4;

baseToMotor = 92; // distance from safe top to motor plate

legD = 28;

footD = 35;
footH = 3;
footEnable = false; // enabling makes it not printable oops

// X and Y coords of each leg
legLocs = [[85 * cos(45), 85 * sin(45)], [-85 * cos(45), 85 * sin(45)], // side away from handle
    [90, -50], [-90, -50]];

t = 5;

$fa = 0.75;
$fs = 0.75;

MakeHandleMotorMount();

module MakeHandleMotorMount() {
    difference() {
        union() {
            // Add four cylinder legs
            drawLegs();
            
            // Add top plate
            intersection() {
                for (i = [0,1,2,3]) hull() {
                    // Each leg
                    translate(legLocs[i]) cylinder(d=legD, h=1000, $fn=20);
                    
                    // Middle part for motor
                    cube([motorW, motorW, 400], center=true);
                }
                
                // Keep only part at top plane
                translate([-1000, -1000, baseToMotor-topT]) cube([2000, 2000, topT]);
            }
            
        }
        
        
        
        // Remove motor screw holes
        for (x=[1, -1]) for (y=[1, -1]) translate([motorHoleSpace*x/2, motorHoleSpace*y/2, 0]) {
            cylinder(d=motorHoleD, h=1000);
        }
        
        // Remove big middle hole
        cylinder(d=motorBigHoleD, h=1000);
        
        
    }
}

module drawLegs() {
    for (i = [0,1,2,3]) {
        translate(legLocs[i]) {
            // draw main leg
            cylinder(d=legD, h=baseToMotor);
            
            // draw foot
            if (footEnable) cylinder(d=footD, h=footH);
        }
    }
}