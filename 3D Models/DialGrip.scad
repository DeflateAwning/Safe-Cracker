dialOD = 79+0.5;
dialH = 12; // CHECK

pointerL = 10;
pointerW = 5;
pointerT = 10;

notchCount = 12;

notchDBig = 3.5;
notchDSmall = 2.5;

wallT = 2.5; // thickness of walls
botT = 3;

holeD = 5; // NEMA17 shaft diameter=5mm
nutW = 8;
nutSink = botT/2;

$fa = 0.5;
$fs = 0.5;

MakeDialGrip();

module MakeDialGrip() {
    difference() {
        union() {
            // Main Grip
            cylinder(d = dialOD + 2*wallT, h=botT + dialH);
            
            // Make dial pointer
            translate([0, dialOD/2-1, 0]) linear_extrude(pointerT) polygon([[0, pointerL], [-pointerW/2, 0], [pointerW/2, 0]]);
            
        }
        
        // Remove where the dial goes
        translate([0, 0, botT]) cylinder(d=dialOD, h=100);
        
        // Remove hole through middle
        cylinder(d=holeD, h=100, center=true);
        // Remove nut
        translate([0, 0, botT-nutSink]) cylinder(r=nutW/sqrt(3), h=100, $fn=6);
        
    }
    
    // Add back the grabber notches
    for (rot = [0:360/notchCount:360]) {
        rotate([0, 0, rot]) translate([dialOD/2, 0, 0]) cylinder(d1=notchDBig, d2=notchDSmall, h=botT+dialH);
    }
    
}