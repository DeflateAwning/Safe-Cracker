dialOD = 79+0.5;
dialH = 12;

pointerL = 10;
pointerW = 5;
pointerT = 10;

notchCount = 12;

notchDBig = 3.5;
notchDSmall = 2.8; // v1: 2.5

wallT = 2.5; // thickness of walls
botT = 6; // v1: 3mm, v2: 5.5+1.2, v3: 

holeD = 5.1; // NEMA17 shaft diameter=5mm
nutW = 8.1; // v1: 8 (for M5 bolt), v2: 10, v3: 8.1
nutSink = 4; // v1: boT-1.5mm, v2: botT-1.2, v3: 4 (M5 head thickness)


$fa = 0.5;
$fs = 0.5;

MakeDialGrip();

module MakeDialGrip() {
    difference() {
        union() {
            // Main Grip
            cylinder(d = dialOD + 2*wallT, h=botT + dialH);
            
            // Make dial pointer (doesn't necessarily align with 0 though)
            rotate([0, 0, 180/notchCount])
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