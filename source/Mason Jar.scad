module PCBled() {
    color("lightgrey") translate([0,0,-1/2]) intersection() {
        cylinder(d=9.5, h=1, $fn=50, center=true);
        cube([9.0,8.99,2], center=true);
    }
    color("brown") for (x=[-3.5,3.5]) translate([x,0,1/4]) cube([1.5,3,0.5], center=true);

    color("white") translate([0,0,0.9/2]) cube([5,5,0.9], center=true);
}

module NodeMCU() {
    color("#444") hull() for (x=[-25+5,25-5],y=[-25/2+5,25/2-5]) translate([x,y,0]) cylinder(d=10, h=1, $fn=50, center=true);
        
   %cube([50-5,25-5,5],center=true);
   color("lightgrey") translate([-22.5,0,-1.5]) cube([5,7,2],center=true);
    
}

// Panneau de LEDs
d = 360/14;
*for (y=[-4:3], a=[0:13]) rotate([0,0,a*d]) translate([0,-24.5,y*9.25]) rotate([90,0,0])PCBled();

// Bloc cylindrique externe
difference() {
    union() {
// Cylindre vertical
        cylinder(d=50, h=90, center=true, $fn=75);
// Cone somital
        translate([0,0,80/2]) cylinder(d1=50, d2=70, h=10, center=true, $fn=75);
    }
// Evidement cylindrique central
    cylinder(d=44, h=95, center=true, $fn=75);
// Evidement conique haut
    translate([0,0,80/2-2*sqrt(2)]) cylinder(d1=28, d2=68, h=20, center=true, $fn=75);
    
    d = 360/14;
    for(a=[0:13]) rotate([0,0,a*d]) {
// Rainures de guidage des LEDs
        translate([0,50/2-1,-5]) cube([10,2,75], center=true);
// trous passage fils leds du bas
        translate([0,50/2-2.5,-37.5]) rotate([90,0,0]) cylinder(d=7, h=3, $fn=50, center=true);
    }
}

// Module NodeMCU
*translate([17,0,10]) rotate([0,90,0]) NodeMCU();

// Support NodeMCU
intersection() {
    translate([16,0,10-2.5]) difference() {
        cube([4,30,50], center=true);
        translate([2,0,2.5]) cube([4,26,51], center=true);
        translate([-1,0,2.5]) cube([4,22,51], center=true);
    }
    cylinder(d=50-4.5,h=70,$fn=75,center=true);
}



// Carte charge/décharge
*translate([-20,0,18]) color("green") cube([1,15,23], center=true);

// Support carte charge/décharge
intersection() {
    difference() {
        translate([-20.5,0,18]) cube([3,17,25], center=true);
        translate([-20.5,0,18]) cube([4,16,24], center=true);
    }
    cylinder(d=50-4.5,h=70,$fn=75,center=true);
}

// Batterie 18650
*cylinder(d=18,h=65,center=true);

// Cylindre guidant la batterie
difference() {
    cylinder(d=20,h=66,center=true);
    cylinder(d=19,h=67,center=true);
}

// Supports latéraux de la batterie
for(a=[-1,0,1,2,4,5,6,7]) rotate([0,0,a*30]) translate([0,16,0]) cube([1.5,13,60],center=true);

