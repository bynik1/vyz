let side=document.getElementById("side").value;
let squre= document.getElementById("evaluate");
let res;

squre.onclick() = function(){
    res = Number(side)*Number(side);
    document.getElementById("square").value=res;
}