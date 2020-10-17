// Shaft Bushing
// Bushing for inside 8mm coupler, to a 6.35mm motor shaft

motorOD = 6.35;
motorMargin = 0.15;
couplerID = 8.0;
couplerMargin = 0.15;
h = 30;


slitW = 1;


$fn = 40;

difference() {
    cylinder(d=couplerID-couplerMargin, h=h);
    
    cylinder(d=motorOD+motorMargin, h=1000, center=true);
    
    // Remove slit
    translate([-slitW/2, 0, -1]) cube([slitW, 1000, 1000]);
}