side=document.getElementById("side");
square=document.getElementById("square");

function load(){
    square.value = side.value*side.value;
}

function volume(){
    square.value = side.value*side.value*side.value;
}

function clear(){
    square.value = 0;
    side.value = 0;
}