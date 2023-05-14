#include <stdint.h>
#include <stdio.h>
#include <math.h>


typedef struct {
    double h;
    double s;
    double v;
} hsv;

typedef struct {
    double r;
    double g;
    double b;
} rgb;

float to_quality(float val, float good, float bad){
    if (good < bad)
    {
        float span = bad-good;
        val = ((val - good) / span) * 100;
        if (val < 0) val = 0;
        if (val > 100) val = 100;
        return val;
    }
    else {
        return 999;
    }
}


rgb hsv2rgb(hsv in) {
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}

Color green_to_red(double ratio) {
    hsv start_color = {120.0, 1.0, 1.0};  // green
    hsv end_color = {0.0, 1.0, 1.0};      // red

    hsv color;
    color.h = end_color.h - (end_color.h - start_color.h) * ratio;
    color.s = end_color.s - (end_color.s - start_color.s) * ratio;
    color.v = end_color.v - (end_color.v - start_color.v) * ratio;

    rgb rgb = hsv2rgb(color);
    return Color(rgb.r*255, rgb.g*255, rgb.b*255);
}