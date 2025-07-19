#version 330 core

out vec4 ocolor;

uniform vec4 color;

void main(){
    //color = fragColor;
    ocolor = color;
}