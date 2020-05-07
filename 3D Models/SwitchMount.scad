// Switch Mount, to mount the switch on the safe
// The switch used is a SPDT momentary limit switch with a roller
// M2 bolts are used to fasten the switch to this block

mountW = 30; // width of part coming in front edge, and the rest of the design
inFromEdge = 50; // distance in from edge of safe to the middle of the switch
inFromEdgeT = 6; // thickness of part that comes in from the edge

boltD = 2; // no nut used, this will be tight though
boltSpace = 10; // distance between centers of bolts

switchH = 33; // distance from safe to bottom of switch
switchW = 20; // width of switch
switchL = 10; // length of switch (parallel to leads)

bumpYPos = (mountW - switchL/2) * 0.55; // position of highest part of bump underneath this thing
bumpH = 4; // height of the bump underneath

$fa = 0.1;
$fs = 0.3;

MakeSwitchMount();

module MakeSwitchMount() {
    difference() {
        union() {
            // Make part coming in from the side
            translate([0, -switchL/2, 0]) cube([inFromEdge+switchW/2, mountW, inFromEdgeT]);
            
            
            // Make part to mount switch on
            translate([0, -switchL/2, 0]) cube([switchW, switchL, switchH]);
            
        }
        
        // Remove switch holes
        for(i = [2, -2]) translate([switchW/2 + boltSpace/i, 0, 0]) {
            cylinder(d=boltD, h=1000, center=true);
        }
        
        // Remove the goofy bump
        hull() { // looking in the positive x direction...
            translate([0, -switchL/2, 0]) rotate([0, 90, 0]) cylinder(d=0.1, h=1000); // BR corner
            translate([0, bumpYPos, bumpH]) rotate([0, 90, 0]) cylinder(d=0.1, h=1000); // top
            translate([0, mountW-switchL/2, 0]) rotate([0, 90, 0]) cylinder(d=0.1, h=1000); // BL
        }
        
    }
}