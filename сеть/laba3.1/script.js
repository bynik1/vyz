m1 =document.getElementById("m1");
let flag = true;
let timer1;
let timer2;
let timer3;
let timer11;
let timer21;
let timer31;
function Mover1(elem){
    if(!flag){
        flag=true;
        clearTimeout(timer1);
    }
    elem.style.display = "block";
}

function Mout1(elem){
    if(flag){
        flag="false";
        m1=elem;
        timer1=setTimeout("m1.style.display='none'", 2000);
    }
}

function Mover2(elem){
    if(!flag){
        flag=true;
        clearTimeout(timer2);
    }
    elem.style.display = "block";
}

function Mout2(elem){
    if(flag){
        flag="false";
        m2=elem;
        timer2=setTimeout("m2.style.display='none'", 2000);
    }
}

function Mover3(elem){
    if(!flag){
        flag=true;
        clearTimeout(timer3);
    }
    elem.style.display = "block";
}

function Mout3(elem){
    if(flag){
        flag="false";
        m3=elem;
        timer3=setTimeout("m3.style.display='none'", 2000);
    }
}


function Mover11(elem){
    if(!flag){
        flag=true;
        clearTimeout(timer11);
    }
    elem.style.display = "block";
}

function Mout11(elem){
    if(flag){
        flag="false";
        m1=elem;
        timer11=setTimeout("m1.style.display='none'", 2000);
    }
}

function Mover21(elem){
    if(!flag){
        flag=true;
        clearTimeout(timer21);
    }
    elem.style.display = "block";
}

function Mout21(elem){
    if(flag){
        flag="false";
        m2=elem;
        timer21=setTimeout("m2.style.display='none'", 2000);
    }
}

function Mover31(elem){
    if(!flag){
        flag=true;
        clearTimeout(timer31);
    }
    elem.style.display = "block";
}

function Mout31(elem){
    if(flag){
        flag="false";
        m3=elem;
        timer31=setTimeout("m3.style.display='none'", 2000);
    }
}

